#include "../include/Huffman.h"

void Huffman::decodifica(string file)
{
    unsigned char nome,num_bit,byte_read=0;
    int index_table=-1;
    char bit_da_analizzare=-1;
    unsigned int size_file,parola_codice=0,size_table=0;
    ofstream f_out;
    ifstream f_in;
    f_in.open(file.c_str(),ios::in|ios::binary);
    f=new Table_code();
    if(f_in)
    {
        f_in.read((char*)&size_table,sizeof(int));
        f_in.read((char*)&size_file,sizeof(int));
        char estensione[4]="";
        f_in.read((char*)&estensione,4);
        size_f=size_file;
        file.resize(file.find_last_of("."));
        file+=estensione;
        f_out.open(file.c_str(),ios::out|ios::binary);
        if(f_out)
        {

            for(unsigned int i=0;i<size_table;i++)
            {
                unsigned int codice;
                f_in.read((char*)&nome,sizeof(char));
                f_in.read((char*)&codice,sizeof(int));
                f_in.read((char*)&num_bit,sizeof(char));
                f->insert(nome,codice,num_bit);
            }
            num_bit=0;

            while(size_file>1)///  in questo modo si evita di leggere pi� bit del dovuto nell ultimo ciclo
            {
                if(bit_da_analizzare<0)
                {
                    f_in.read((char*)&byte_read,sizeof(char));
                    bit_da_analizzare=7;
                }
                while(index_table==-1&&bit_da_analizzare>=0)
                {
                    parola_codice<<=1;
                    parola_codice=parola_codice|((byte_read>>bit_da_analizzare)&1);
                    bit_da_analizzare--;num_bit++;
                    index_table=f->find(parola_codice,num_bit);
                }
                if(index_table>=0)
                {
                    nome=f->get_elemento(index_table)->get_nome();
                    f_out.write((char*)&nome,sizeof(char));
                    size_file--;
                    parola_codice=0;num_bit=0;index_table=-1;
                }
            }
            f_out.close();
            cout<<"Decodifica completata!"<<endl;
        }
        else
            cout<<"impossibile Decodificare";
    }
    else
    	cout<<"Errore nell'apertura del file da decodificare!"<<endl;
    f_in.close();
}





void Huffman::codifica(string file)///save_num_bit se ci sono problemi
{
    unsigned char index_table,byte_read=0,byte_write=0,numero_bit=0,bit_residui=8,save_numero_bit=0;
    unsigned int code,fine_file,size_out=0;
    string estensione;
    ofstream f_out;
    ifstream f_in;
    set_name(file.c_str());
    set_head(albero_huffman());///costruisce l'albero di huffman contando le frequenze dei caratteri
    f=new Table_code(get_head());///costruisce la tabella dei codici
    fine_file=size_f;
    estensione=file;
    estensione=estensione.substr(file.size()-4,file.size());
    file.resize(file.find_last_of(".")); ///rinominare il file di output con lo stesso nome, ma con estensione propietaria cancellando la vecchia estensione
    file+=".huff\0";

    f_in.open(get_name().c_str(),ios::in|ios::binary);
    if(f_in)
    {
        f_out.open(file.c_str(),ios::out|ios::binary);
        if(f_out)
        {
            {///Header del file
                unsigned char nome,n_bit;
                unsigned int size_table=f->size(),codice;
                f_out.write((char*)&size_table,sizeof(int));
                f_out.write((char*)&fine_file,sizeof(int));
                f_out.write((char*)estensione.c_str(),sizeof(4));
                size_out+=12;
                ///inserisco la tabella nel file
                for(unsigned int i=0;i<size_table;i++)
                {
                    nome=f->get_elemento(i)->get_nome();n_bit=f->get_elemento(i)->get_num_bit();
                    codice=f->get_elemento(i)->get_cod();
                    f_out.write((char*)&nome,sizeof(char));
                    f_out.write((char*)&codice,sizeof(int));
                    f_out.write((char*)&n_bit,sizeof(char));
                    size_out+=6;
                }
            }
            while(f_in.tellg()!=-1)
            {
                if(numero_bit==0)
                {
                    f_in.read((char*)&byte_read,sizeof(char));
                    fine_file--;
                    ///trovo il carattere nella mia tabella in modo da sapere il codice e il numero di bit utilizzati
                    index_table=f->find(byte_read);
                    numero_bit=f->get_elemento(index_table)->get_num_bit();
                    code=f->get_elemento(index_table)->get_cod();
                }
                if(bit_residui>=numero_bit)///se ci sono abbastanza bit per memorizzare il codice del byte letto
                {
                    byte_write<<=numero_bit;
                    byte_write=byte_write|code;
                    bit_residui-=numero_bit;
                    numero_bit=0;
                }
                else///nel caso non ci sia spazio nel buffer
                {
                    byte_write<<=bit_residui;
                    unsigned int app=code<<(32-numero_bit);
                    app>>=(32-numero_bit);
                    byte_write=byte_write|(app>>(numero_bit-bit_residui));
                    ///libero byte_write
                    save_numero_bit=numero_bit;
                    numero_bit-=bit_residui;

                    f_out.write((char*)&byte_write,sizeof(char));size_out+=1;
                    bit_residui=8;
                    ///azzero i bit scritti
                    byte_write=0;
                }
                if(bit_residui==0)
                {
                    f_out.write((char*)&byte_write,sizeof(char));size_out+=1;
                    byte_write=0;
                    numero_bit=0;
                    bit_residui=8;
                }
            }
            if(bit_residui!=8)
            {

                byte_write<<=8-save_numero_bit;

                f_out.write((char*)&byte_write,sizeof(char));size_out+=1;
            }
            f_out.close();
            cout<<"Codifica completata!"<<endl;
            cout<<"Tasso di compressione: "<<tasso_compressione(size_f,size_out)<<"%"<<endl;
        }
    }
    else
    	cout<<"Errore nell'apertura del file!"<<endl;
    f_in.close();
    f_out.close();
};

Nodo *Huffman::albero_huffman()
{
    unsigned int frequenze[256]={0};
    freq(frequenze);
    Nodo *t;
    for(unsigned int i=0;i<256;i++)
    {
        if(frequenze[i]>0)
        {
            t=new Nodo(frequenze[i],string((const char*)&i));
            min_heap.insert(t);
        }
    }

    t=new Nodo(min_heap.extract_min(),min_heap.extract_min());
    min_heap.insert(t);

    while(min_heap.heap_size()>1)
    {

        t=new Nodo(min_heap.extract_min(),min_heap.extract_min());
        min_heap.insert(t);
    }
    return t;
};

void Huffman::freq(unsigned int *frequenze)
{
    unsigned char c;
	unsigned int size=0;
	ifstream file;
    file.open(get_name().c_str(),ios::in|ios::binary);
    if(file)
    {
        while(file.tellg()!=-1)
    	{
	    	file.read((char*)&c,sizeof(char));
	    	frequenze[c]++;
	    	size++;
	    }
    	cout<<endl;
        frequenze[c]--;
        this->size_f=size;
    }
    else
    	cout<<"Errore nell'apertura del file!"<<endl;
    file.close();
};

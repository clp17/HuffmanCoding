#ifndef ELEMENT_H
#define ELEMENT_H

class Element
{
public:
    Element(unsigned char c,unsigned int codice,unsigned char nbit){set_nome(c);set_cod(codice);set_num_bit(nbit);}
    void set_nome(unsigned char c){nome=c;}
    void set_cod(unsigned int codice){cod=codice;}
    void set_num_bit(unsigned char nbit){num_bit=nbit;}
    unsigned char get_nome(){return nome;}
    unsigned int get_cod(){return cod;}
    unsigned char get_num_bit(){return num_bit;}
private:
    unsigned char nome;
    unsigned int cod;
    unsigned char num_bit;
};


#endif // ELEMENT_H

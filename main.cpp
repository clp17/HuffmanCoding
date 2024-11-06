#include <iostream>
#include <stdlib.h>
#include <string>
#include "inlcude/Coda_di_min_priorita.h"
#include "inlcude/Table_code.h"
#include "inlcude/Huffman.h"
#ifdef _WIN32
#define clear "cls"
#else
#define clear "clear"
#endif
using namespace std;


int main()
{
    Huffman h;
    string nome_file;
    unsigned int scelta=0;
    while(scelta<1||scelta>3)
    {
        system(clear);
        cout<<"Scegli l'operazione: "<<endl;
        cout<<"1) Codifica"<<endl;
        cout<<"2) Decodifica"<<endl;
        cout<<"3) Esci"<<endl;
        cout<<"Scelta: ";cin>>scelta;
    }

    switch (scelta)
    {
        case(1):
            cout<<"\t\t\tCODIFICA"<<endl<<"Nome del file da codificare: ";
            cin>>nome_file;
            h.encoding(nome_file);
            break;
        case(2):
            cout<<"\t\t\tDECODIFICA"<<endl<<"Nome del file da decodificare: ";
            cin>>nome_file;
            h.decoding(nome_file);
            break;
        case(3):
            break;
    }
    cout<<endl;

    return 0;
}

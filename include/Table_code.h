#ifndef TABLE_CODE_H
#define TABLE_CODE_H
#include "Element.h"
#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <sstream>

class Table_code
{
public:
    Table_code(){};
    Table_code(Nodo*r){root=r;this->create_code(root,0,0);};
    int create_code(Nodo *r,unsigned int cod,unsigned char nbit)
    {
        if(r->get_left()==NULL)//facendo riflessioni sulla greedy choice di huffman possiamo dire che i nodi ottenuti o sono foglie o sono nodi con entrambi i figli
        {
            row.push_back(Element(r->get_key().c_str()[0],cod,nbit));//solo il primo carattere dalla stringa convertita con il metodo c_str()
            return 0;
        }
        nbit++;
        create_code(r->get_left(),cod<<1,nbit);
        create_code(r->get_right(),(cod<<1)|1,nbit);
        return 1;
    }
    void insert(unsigned char a,unsigned int b,unsigned char c){row.push_back(Element(a,b,c));}
    unsigned int size(){return row.size();}
    Element* get_elemento(unsigned char i){return &row[i];}
    int find(unsigned int codex,unsigned char numero_bit){for(unsigned int i=0;i<row.size();i++)if(row[i].get_num_bit()==numero_bit)if(row[i].get_cod()==codex)return i;return -1;};
    int find(unsigned char carattere){for(unsigned int i=0;i<row.size();i++)if(row[i].get_nome()==carattere)return i;return -1;}
private:
    vector<Element>row;
    Nodo *root;
};

#endif // TABLE_CODE_H

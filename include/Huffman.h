#ifndef HUFFMAN_H
#define HUFFMAN_H
#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include "Coda_di_min_priorita.h"
#include "Table_code.h"

class Huffman
{
public:
    Huffman(){size_f=0;};
    Huffman(string n){name_file=n;size_f=0;};
    void set_name(string a){name_file=a;};
    string get_name(){return name_file;};
    void set_head(Nodo *a){head=a;};
    Nodo *get_head(){return head;};
    void encoding(string file){codifica(file);}
    void decoding(string file){decodifica(file);}
private:
    void decodifica(string file);
    void codifica(string file);
    float tasso_compressione(unsigned int in,unsigned int out){float ci(in);float co(out);return 100-((co*100)/ci);};
    string name_file;
    Coda_di_min_priorita min_heap;
    Nodo *albero_huffman();
    void freq(unsigned int *);
    Nodo *head;
    unsigned int size_f;
    Table_code *f;
};

#endif /// HUFFMAN_H

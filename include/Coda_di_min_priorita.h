#ifndef MINHEAP_H
#define MINHEAP_H
#include "Nodo.h"
class Coda_di_min_priorita
{
public:
    Coda_di_min_priorita(){};
    ~Coda_di_min_priorita(){};
    void insert(Nodo *a){c.push_back(a);min_heapify(c.size()-1);};
    Nodo* minimum(){return c[0];};
    unsigned int heap_size(){return c.size();};
    Nodo* extract_min();///estrae il minimo e ripristina la proprietà dell'albero min heap
private:
    vector<Nodo*>c;
    void min_heapify(unsigned int i);
    void swap_nodo(unsigned int i,unsigned int j);
    unsigned int parent(unsigned int i){if (i%2==0) i--; return i/2;};
    unsigned int left(unsigned int i){unsigned int j;j=i*2+1;if (j>c.size()-1) return i;else return j;};
    unsigned int right(unsigned int i){unsigned int j;j=i*2+2;if (j>c.size()-1)return i;else return j;};
    void heapify(unsigned int i);
    unsigned int is_nodo_heap(unsigned int i){if(c[i]->get_freq()>c[right(i)]->get_freq()||c[i]->get_freq()>c[left(i)]->get_freq())return 0;else return 1;}/// controlla se è un nodo heap
    ///minore o uguale perchè right e left se non trovano figli restituiscono l'indice di cui si vogliono sapere i figli e quindi il metodo is_nodo_heap restituirebbe sempre 0 quando non ha uno dei due figli
    };



#endif /// MINHEAP_H

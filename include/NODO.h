#ifndef NODO_H
#define NODO_H
#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <sstream>

using namespace std;
class Nodo
{
public:
    Nodo(unsigned int val,string a){set_freq(val);set_key(a);key=a;this->set_left();this->set_right();};
    ~Nodo(){};
    Nodo(){};
    Nodo(Nodo *a){this->set_freq(a->get_freq());this->set_key(a->get_key());this->set_left(a->get_left());this->set_right(a->get_right());}
    Nodo(Nodo *a,Nodo *b)
    {
        Nodo *c=new Nodo(*a);
        Nodo *d=new Nodo(*b);

        this->set_freq(a->get_freq()+b->get_freq());
        this->set_key(a->get_key()+b->get_key());
        this->set_left(c);
        this->set_right(d);
    };
    void set_left(Nodo *a){left=a;};
    void set_right(Nodo *a){right=a;};
    void set_left(){left=NULL;};
    void set_right(){right=NULL;};
    Nodo *get_left(){return left;};
    Nodo *get_right(){return right;};

    unsigned int get_freq(){return freq;};
    string get_key(){return key;};
    void copia(Nodo *a){set_freq(a->get_freq());set_key(a->get_key());set_left(a->get_left());set_right(a->get_right());};
    void set_freq(unsigned int f){freq=f;};
    void set_key(string k){key=k;};
private:
    unsigned int     freq;
    string           key;
    Nodo *left;
    Nodo *right;
};

#endif // NODO_H

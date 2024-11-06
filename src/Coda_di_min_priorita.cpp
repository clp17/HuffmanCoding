#include "../include/Coda_di_min_priorita.h"

Nodo* Coda_di_min_priorita::extract_min()
{
    Nodo *min=new Nodo(c[0]);
    unsigned int i=0,r,l;
    swap_nodo(0,c.size()-1);///scambio l'ultimo nodo della struttura con il primo in modo da poter eliminare il minimo che poi si trover� all'ultimo nodo senza creare troppi problemi
    c.pop_back();/// rimuovo l'ultimo nodo che con lo swap precedente � il nodo minimo
    while (!is_nodo_heap(i)&&i<heap_size())/// verifica che il nodo che abbiamo messo nella posizione 0(quello che dovrebbe essere minimo) verifichi che formi un heap solo con i suoi figli
    {///alla prima estrazione si entra sempre in questo ciclo tranne nel caso in cui l'albero � composto da tre nodi e il pi� piccolo � il figlio destro(quindi l'ultimo nodo della struttura che va a posizionarsi al primo elemento appena eliminato), oppure non ci sono figli oppure c'� solo il figlio sx
        r=right(i);
        l=left(i);
        if(c[r]->get_freq()>=c[l]->get_freq())///per tener traccia su che figlio applicare l'heapify(confrontiamo solo i figli perch� se entrato nel ciclo di sicuro il padre non � il minimo)
        {
            swap_nodo(i,l);///si scambia prima il nodo
            i=l;
        }
        else
        {
            swap_nodo(i,r);
            i=r;
        }
    }
    return min;
}
void Coda_di_min_priorita::swap_nodo(unsigned int i,unsigned int j)
{
    Nodo t;
    t.copia(c[i]);
    c[i]->copia(c[j]);
    c[j]->copia(&t);
};
void Coda_di_min_priorita::heapify(unsigned int i)
{
    unsigned int minimo=i;
    if(c[minimo]->get_freq()>c[left(i)]->get_freq())
        minimo=left(i);
    if(c[minimo]->get_freq()>c[right(i)]->get_freq())
        minimo=right(i);
    if(minimo!=i)
        swap_nodo(minimo,i);
};

void Coda_di_min_priorita::min_heapify(unsigned int i)
{
    while(i>1&&!is_nodo_heap(parent(i)))
    {
        i=parent(i);
        heapify(i);
    }
};

#include <iostream>
using namespace std; // Avoid using std:: ....
#include "agenEnlazado.h"
// Implemente una función que modifique un árbol general de forma que si el árbol tiene nodos con un solo hijo,
// se elimine toda la descendencia de dichos nodos.

// Contar Numero de Hijos
template <class T>
int numeroHijosAgen(Agen<T> ag, typename Agen<T>::nodo nd)
{
    int iNumeroHijos = 0;
    if (nd != Agen<T>::NODO_NULO)
    {
        iNumeroHijos++;
        nd = ag.hijoIzqdo(nd);
        while (nd != Agen<T>::NODO_NULO)
        {
            nd = ag.hermDrcho(nd);
        }
    }
    return iNumeroHijos;
}

// Podar subArbol
template <class T>
void podaDescendientesAgen(Agen<T> &ag, typename Agen<T>::nodo nd)
{
    while (ag.hijoIzqdo(nd) != Agen<T>::NODO_NULO)
    {
        podaDescendientesAgen(ag, ag.hijoIzqdo(nd)); // POSTORDEN
        ag.eliminarHijoIzqdo(nd);
    }
}

template <class T>
void podaSiTieneUnHijoRec(Agen<T> &ag, typename Agen<T>::nodo nd)
{
    if (nd != Agen<T>::NODO_NULO)
    {
        nd = ag.hijoIzqdo(nd);
        while (nd != Agen<T>::NODO_NULO)
        {
            podaSiTieneUnHijoRec(ag, nd);
            nd = ag.hermDrcho(nd);
        }
        if (numeroHijosAgen(ag, nd) == 1)
        {
        }
    }
}

int main()
{
    return 0;
}
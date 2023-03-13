#include <iostream>
#include "arbolbinenla.h"
using namespace std; // Avoid using std:: ....

// Contar numero de nodos del arbol que tienen exactamente 3 nietos

template <class T>
int contarDescendientesDirectos(typename Abin<T>::nodo nd, Abin<T> &abArbol)
{
    if (nd == Abin<T>::NODO_NULO)
    {
        return 0;
    }
    else
    {
        int iNumeroDescendientes = 0;
        if (abArbol.hijoDrcho(nd) != Abin<T>::NODO_NULO)
        {
            iNumeroDescendientes++;
        }

        if (abArbol.hijoIzqdo(nd) != Abin<T>::NODO_NULO)
            iNumeroDescendientes++;

        return iNumeroDescendientes;
    }
}

template <class T>
bool tiene3nietos(typename Abin<T>::nodo nd, Abin<T> &abArbol)
{
    // hijo izq + hijo der, al ser un bin necesita los 2 hijos para obtener al menos 3 nietos
    auto ndHijoIzq = abArbol.hijoIzqdo(nd);
    auto ndHijoDer = abArbol.hijoDrcho(nd);
    if (ndHijoDer != Abin<T>::NODO_NULO && ndHijoIzq != Abin<T>::NODO_NULO)
    {
        return (contarDescendientesDirectos(ndHijoDer, abArbol) + contarDescendientesDirectos(ndHijoIzq, abArbol)) == 3;
    }
    else
        return false;
}

template <class T>
void contar3NietosRec(typename Abin<T>::nodo nd, Abin<T> &abArbol, int &iNumero3Nietos)
{
    if (nd != Abin<T>::NODO_NULO)
    {
        contar3NietosRec(abArbol.hijoIzqdo(nd), abArbol, iNumero3Nietos);

        if (tiene3nietos(nd, abArbol))
            iNumero3Nietos++;

        contar3NietosRec(abArbol.hijoDrcho(nd), abArbol, iNumero3Nietos);
    }
}

template <class T>
int contar3Nietos(Abin<T> abArbol)
{
    if (abArbol.arbolVacio())
        return 0;
    else
    {
        int iNumero3Nietos = 0;
        contar3NietosRec(abArbol.raiz(), abArbol, iNumero3Nietos);
        return iNumero3Nietos;
    }
}

int main()
{
    Abin<int> A;
    A.insertaRaiz(1);
    A.insertarhijoDrcho(A.raiz(), 3);
    A.insertarhijoIzqdo(A.raiz(), 1);
    A.insertarhijoDrcho(A.hijoDrcho(A.raiz()), 6);
    A.insertarhijoIzqdo(A.hijoIzqdo(A.raiz()), 4);
    A.insertarhijoDrcho(A.hijoIzqdo(A.raiz()), 5);

    cout << contar3Nietos(A) << endl;

    return 0;
}
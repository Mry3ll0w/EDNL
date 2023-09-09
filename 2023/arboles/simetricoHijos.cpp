#include <iostream>
#include "arbolbinenla.h"
using namespace std; // Avoid using std:: ....

/**
 * Dado dos árboles binarios, realizar un método que devuelva verdadero si ambos árboles son simétricos y la suma de los nodos hijos es mayor
    que la de su nodo padre.
 */

template <class T>
bool simetricosAbin(Abin<T> ab1, Abin<T> ab2, typename Abin<T>::nodo nd1, typename Abin<T>::nodo nd2)
{
    bool bSimetricos = true;
    if (nd1 != Abin<T>::NODO_NULO && nd2 != Abin<T>::NODO_NULO && bSimetricos)
    {
        simetricosAbin(ab1, ab2, ab1.hijoDrcho(nd1), ab2.hijoIzqdo(nd2));
        simetricosAbin(ab1, ab2, ab1.hijoIzqdo(nd1), ab2.hijoDrcho(nd2));

        bSimetricos = ab1.elemento(nd1) == ab2.elemento(nd2);
    }

    // Comprobamos porque han salido
    if (nd1 == Abin<T>::NODO_NULO && nd2 != Abin<T>::NODO_NULO || nd1 != Abin<T>::NODO_NULO && nd2 == Abin<T>::NODO_NULO)
    {
        bSimetricos = false;
    }

    return bSimetricos;
}

// Suma de descendientes
template <class T>
int sumaDescendientesAbin(Abin<T> ab, typename Abin<T>::nodo nd, const int &iValorPadre) // Hay que restarle el valor del padre
{
    int iSumaHijos = 0;
    if (nd != Abin<T>::NODO_NULO)
    {
        sumaDescendientesAbin(ab, ab.hijoIzqdo(nd));
        sumaDescendientesAbin(ab, ab.hijoDrcho(nd));
        // Sumamos Hijos
        iSumaHijos += ab.elemento(nd);
    }
    return iSumaHijos - iValorPadre;
}

// Recursiva principal

template <class T>
bool hijosSumanMasPadre(Abin<T> ab, typename Abin<T>::nodo nd)
{
    bool bCumpleCondiciones = true;
    if (nd != Abin<T>::NODO_NULO && bCumpleCondiciones)
    {
        hijosSumanMasPadre(ab, ab.hijoDrcho(nd));
        hijosSumanMasPadre(ab, ab.hijoIzqdo(nd));
        // Pillamos valor del padre
        const int iValorNodoActual = ab.elemento(nd);
        const int iSumaDescendencia = sumaDescendientesAbin(ab, nd);
        bCumpleCondiciones = iValorNodoActual < iSumaDescendencia;
    }
    return bCumpleCondiciones;
}

template <class T>
bool principal(Abin<T> ab)
{
    if (ab.arbolVacio())
    {
        return false;
    }
    else
    {
        return hijosSumanMasPadre(ab, ab.raiz()) && simetricosAbin(ab, ab.raiz());
    }
}

int main()
{

    return 0;
}
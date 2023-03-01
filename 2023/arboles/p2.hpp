#include "arbolbinenla.h"

/**
 * Dos árboles binarios son similares cuando tienen idéntica estructura de ramificación,
 * es decir, ambos son vacíos, o en caso contrario, tienen subárboles izquierdo y
 * derecho similares.
 * Implementa un subprograma que determine si dos árboles binarios son similares.
 */

template <class T>
bool nodosSimilares(Abin<T> abArbol1, Abin<T> abArbol2,
                    typename Abin<T>::nodo ndAb1, typename Abin<T>::nodo ndAb2)
{
    return (ndAb1 == Abin<T>::NODO_NULO && ndAb2 == Abin<T>::NODO_NULO) ||
           (abArbol1.hijoIzqdo(ndAb1) != Abin<T>::NODO_NULO && abArbol1.hijoIzqdo(ndAb2) != Abin<T>::NODO_NULO &&
            abArbol1.hijoDrcho(ndAb1) == Abin<T>::NODO_NULO && abArbol2.hijoDrcho(ndAb2) == Abin<T>::NODO_NULO) ||
           (abArbol1.hijoIzqdo(ndAb1) == Abin<T>::NODO_NULO && abArbol1.hijoIzqdo(ndAb2) == Abin<T>::NODO_NULO &&
            abArbol1.hijoDrcho(ndAb1) != Abin<T>::NODO_NULO && abArbol2.hijoDrcho(ndAb2) != Abin<T>::NODO_NULO) ||
           (abArbol1.hijoIzqdo(ndAb1) != Abin<T>::NODO_NULO && abArbol1.hijoIzqdo(ndAb2) != Abin<T>::NODO_NULO &&
            abArbol1.hijoDrcho(ndAb1) != Abin<T>::NODO_NULO && abArbol2.hijoIzqdo(ndAb2) != Abin<T>::NODO_NULO);
}

template <class T>
void compruebaSimilaresRec(Abin<T> abArbol1, Abin<T> abArbol2,
                           typename Abin<T>::nodo ndAb1, typename Abin<T>::nodo ndAb2, bool &bSimilares)
{
    if (ndAb1 != Abin<T>::NODO_NULO && ndAb2 != Abin<T>::NODO_NULO && bSimilares)
    {
        compruebaSimilaresRec(abArbol1, abArbol2, abArbol1.hijoDrcho(ndAb1), abArbol2.hijoDrcho(ndAb2), bSimilares);
        bSimilares = nodosSimilares(abArbol1, abArbol2, ndAb1, ndAb2);
        compruebaSimilaresRec(abArbol1, abArbol2, abArbol1.hijoIzqdo(ndAb1), abArbol2.hijoIzqdo(ndAb2), bSimilares);
    }
}

template <class T>
bool ArbolesSimilares(Abin<T> abArbol1, Abin<T> abArbol2)
{
    bool bSimilares = true;

    compruebaSimilaresRec(abArbol1, abArbol2, abArbol1.raiz(), abArbol2.raiz(), bSimilares);

    return bSimilares;
}

/**
 * Para un árbol binario B, podemos construir el árbol binario reflejado BR cambiando los subárboles
 * izquierdo y derecho en cada nodo.
 * Implementa un subprograma que devuelva el árbol binario reflejado de uno dado.
 */

template <class T>
void cronstruyeReflejo(Abin<T> abOrigen, Abin<T> &abDestino,
                       typename Abin<T>::nodo ndAbOrigen, typename Abin<T>::nodo ndAbDestino)
{
    if (ndAbOrigen != Abin<T>::NODO_NULO)
    {
        // NODOS
    }
}
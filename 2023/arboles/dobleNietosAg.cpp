#include <iostream>
#include "agenEnlazado.h"

using namespace std; // Avoid using std:: ....
// Devolver el numero de nodos que tiene el doble de nietos que bisnietos

// Profundidad Nodo
template <class T>
int profundidadAgen(Agen<T> ag, typename Agen<T>::nodo nd)
{
    if (nd == ag.raiz())
    {
        return 0;
    }
    else
    {
        return 1 + profundidadAgen(ag, ag.padre(nd));
    }
}

// Contar Nietos ==> Cuando la profundidad del nodo padre sea 2 menos que el actual
template <class T>
int numeroNietosAgen(Agen<T> ag, typename Agen<T>::nodo nd, const int &iProfundidadNodoActual)
{
    int iNumeroNietos = 0;
    if (nd != Agen<T>::NODO_NULO && std::abs(profundidadAgen(ag, nd) - iProfundidadNodoActual) <= 2)
    {
        nd = ag.hijoIzqdo(nd);
        while (nd != Agen<T>::NODO_NULO)
        {
            numeroNietosAgen(ag, nd, iProfundidadNodoActual);

            if (std::abs(profundidadAgen(ag, nd) - iProfundidadNodoActual) == 2)
            {
                iNumeroNietos++;
            }

            nd = ag.hermDrcho(nd);
        }
    }
    return iNumeroNietos;
}

// Contar Bisnietos
template <class T>
int numeroBisnietosAgen(Agen<T> ag, typename Agen<T>::nodo nd, const int &iProfundidadNodoActual)
{
    int iNumeroBisnietos = 0;
    if (nd != Agen<T>::NODO_NULO && std::abs(profundidadAgen(ag, nd) - iProfundidadNodoActual) <= 3)
    {
        nd = ag.hijoIzqdo(nd);
        while (nd != Agen<T>::NODO_NULO)
        {
            numeroBisnietosAgen(ag, nd, iProfundidadNodoActual);

            if (std::abs(profundidadAgen(ag, nd) - iProfundidadNodoActual) == 3)
            {
                iNumeroBisnietos++;
            }

            nd = ag.hermDrcho(nd);
        }
    }
    return iNumeroBisnietos;
}

// Algoritmo Recursivo Principal

template <class T>
int dobleNietosBisnietosRec(Agen<T> ag, typename Agen<T>::nodo nd)
{
    int iNodosCondicion = 0;
    if (nd != Agen<T>::NODO_NULO)
    {
        nd = ag.hijoIzqdo(nd);
        while (nd != Agen<T>::NODO_NULO)
        {
            dobleNietosBisnietosRec(ag, nd);

            // Comprobaciones en inorden
            const int iNumeroNietosActual = numeroNietosAgen(ag, nd, profundidadAgen(ag, nd));
            const int iNumeroBisnietosActual = numeroBisnietosAgen(ag, nd, profundidadAgen(ag, nd));
            if (iNumeroNietosActual * 2 == iNumeroBisnietosActual)
                iNodosCondicion++;

            nd = ag.hermDrcho(nd);
        }
    }
    return iNodosCondicion;
}

// Llamada principal
template <class T>
int dobleNietosBisnietosAgen(Agen<T> ag)
{
    if (ag.arbolVacio())
    {
        return 0;
    }
    else
    {
        return dobleNietosBisnietosRec(ag, ag.raiz());
    }
}

int main()
{

    return 0;
}
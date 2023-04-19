#include <iostream>
#include "abin_enla.h"
using namespace std; // Avoid using std:: ....

template <class T>
int sumaNodosRaiz(Abin<T> AbArbol, typename Abin<T>::nodo nd)
{
    if (nd == Abin<T>::NODO_NULO)
    {
        return 0;
    }
    else
    {
        return AbArbol.elemento(nd) + sumaNodosRaiz(AbArbol, AbArbol.hijoDrcho(nd), AbArbol.hijoIzqdo(nd));
    }
}

// Recibe el abol copiado del original
template <class T>
void createArbolSumaNodosRec(Abin<T> AbOrigen, Abin<T> &AbDestino, typename Abin<T>::nodo nd1, typename Abin<T>::nodo nd2)
{
    if (nd1 != Abin<T>::NODO_NULO && nd2 != Abin<T>::NODO_NULO)
    {
        AbDestino.elemento(nd2) = sumaNodosRaiz(AbOrigen, nd1);
        createArbolSumaNodosRec(AbOrigen, AbDestino, AbOrigen.hijoIzqdo(nd1), AbDestino.hijoIzqdo(nd2));
        createArbolSumaNodosRec(AbOrigen, AbDestino, AbOrigen.hijoDrcho(nd1), AbDestino.hijoDrcho(nd2));
    }
}

template <class T>
Abin<T> createArbolSumaNodos(const Abin<T> AbArbol)
{
    if (AbArbol.arbolVacio())
    {
        return Abin<T>();
    }
    else
    {
        Abin<T> AbSuma = AbArbol;
        createArbolSumaNodosRec(AbArbol, AbSuma, AbArbol.raiz(), AbSuma.raiz());
        return AbSuma;
    }
}

// Nunca voy a recibir nodo Nulo, se controla antes
template <class T>
bool esNodoReflejadoAbin(Abin<T> AbArbol1, Abin<T> AbArbol2, typename Abin<T>::nodo nd1, typename Abin<T>::nodo nd2)
{
    if (nd1 == Abin<T>::NODO_NULO && nd2 == Abin<T>::NODO_NULO)
    {
        return true;
    }
    else
    {
        // Compruebo que sean hojas
        if (
            (AbArbol1.hijoIzqdo(nd1) == Abin<T>::NODO_NULO && AbArbol1.hijoDrcho(nd1) == Abin<T>::NODO_NULO) &&
            (AbArbol2.hijoDrcho(nd2) == Abin<T>::NODO_NULO && AbArbol2.hijoDrcho(nd2) == Abin<T>::NODO_NULO))
        {
            return true;
        }
        else // No son hojas, compruebo ramificación e igualdad
        {
            if (
                AbArbol1.elemento(AbArbol1.hijoIzqdo(nd1)) == AbArbol2.elemento(AbArbol2.hijoDrcho(nd2)) &&
                (AbArbol1.hijoDrcho(nd1) == Abin<T>::NODO_NULO && AbArbol2.hijoIzqdo(nd2) == Abin<T>::NODO_NULO))
            {
                return true;
            }
            else if (
                AbArbol1.elemento(AbArbol1.hijoDrcho(nd1)) == AbArbol2.elemento(AbArbol2.hijoIzqdo(nd2)) &&
                (AbArbol1.hijoIzqdo(nd1) == Abin<T>::NODO_NULO && AbArbol2.hijoDrcho(nd2) == Abin<T>::NODO_NULO))
            {
                return true;
            }
            else if (
                AbArbol1.elemento(AbArbol1.hijoIzqdo(nd1)) == AbArbol2.elemento(AbArbol2.hijoDrcho(nd2)) &&
                AbArbol1.elemento(AbArbol1.hijoDrcho(nd1)) == AbArbol2.elemento(AbArbol2.hijoIzqdo(nd2)))
            { // Arbol completo, si no son los de arriba esta completo
                return true;
            }
            else
            {
                return false;
            }
        }
    }
}

template <class T>
void esReflejadoSumaRec(Abin<T> AbArbol1, Abin<T> AbArbol2, typename Abin<T>::nodo nd1, typename Abin<T>::nodo nd2, bool &bCondicion)
{
    if (nd != Abin<T>::NODO_NULO && bCondicion)
    {
        if (!esNodoReflejadoAbin(AbArbol1, AbArbol2, nd1, nd2))
        {
            bCondicion = false;
        }
        else
        {
            if (AbArbol1.elemento(AbArbol1.hijoDrcho(nd1)) != Abin<T>::NODO_NULO && AbArbol1.elemento(AbArbol1.hijoIzqdo(nd1)) != Abin<T>::NODO_NULO)
            {
                bCondicion = AbArbol1.elemento(nd) > (AbArbol1.elemento(AbArbol1.hijoDrcho(nd1)) + AbArbol1.elemento(AbArbol1.hijoIzqdo(nd1)));
            }
            else
            {
                int iSumaHijos = 0;
                if (AbArbol1.elemento(AbArbol1.hijoIzqdo(nd1)) != Abin<T>::NODO_NULO)
                {
                    iSumaHijos += AbArbol1.elemento(AbArbol1.hijoIzqdo(nd1));
                }

                if (AbArbol1.elemento(AbArbol1.hijoDrcho(nd1)) != Abin<T>::NODO_NULO)
                {
                    iSumaHijos += AbArbol1.elemento(AbArbol1.hijoDrcho(nd1));
                }
                bCondicion = AbArbol1.elemento(nd1) > iSumaHijos;
            }
        }
    }
}

template <class T>
bool esReflejadoSuma(Abin<T> AbArbol1, Abin<T> AbArbol2)
{
    if (AbArbol1.arbolVacio() != AbArbol2.arbolVacio())
    {
        return false;
    }
    else
    {
        bool bCondicion = true;
        esReflejadoSumaRec(AbArbol1, AbArbol2, AbArbol1.raiz(), AbArbol2.raiz(), bCondicion);
        return bCondicion;
    }
}

int main()
{

    return 0;
}
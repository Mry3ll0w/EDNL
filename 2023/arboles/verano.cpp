#include <iostream>
#include "arbolbinenla.h"
#include "agenEnlazado.h"
using namespace std; // Avoid using std:: ....

/**
 * Practica 1 Arboles
 * Implementa un subprograma que calcule el número de nodos de un árbol binario.
 */

template <class T>
int numNodosAbin(Abin<T> &abArbol, typename Abin<T>::nodo nd)
{
    if (nd == Abin<T>::NODO_NULO)
        return 0;

    return 1 + numNodosAbin(abArbol, abArbol.hijoDrcho(nd)) + numNodosAbin(abArbol, abArbol.hijoIzqdo(nd));
}

/**
 * Ejercicio 2:
 * Implementa un subprograma que calcule la altura de un árbol binario.
 * La altura de un arbol binario se mide por el maximo de niveles de ambos hijos
 */

template <class T>
int alturaArbolBinario(Abin<T> &abArbol, typename Abin<T>::nodo nd)
{
    if (nd == Abin<T>::NODO_NULO)
        return -1;

    return 1 +
           fmax(alturaArbolBinario(abArbol, abArbol.hijoDrcho(nd)),
                alturaArbolBinario(abArbol, abArbol.hijoIzqdo(nd)));
}

/**
 * Ejercicio 3 :
 * Implementa un subprograma que, dados un árbol binario y un nodo del mismo, determine la
 * profundidad de este nodo en dicho árbol.
 */
template <class T>
int profundidadNodoAbin(Abin<T> &abArbol, typename Abin<T>::nodo nd)
{
    if (nd == Abin<T>::NODO_NULO)
        return 0;
    return 1 + profundidadNodoAbin(abArbol, abArbol.padre(nd));
}

/**
 * Ejercicio 6
 * Implementa un subprograma que determine el nivel de desequilibrio de un árbol binario,
 * definido como el máximo desequilibrio de todos sus nodos. El desequilibrio de un nodo
 * se define como la diferencia entre las alturas de los subárboles del mismo.
 */

int diferenciaAlturas(Abin<int> abArbol, typename Abin<int>::nodo nd)
{
    return std::abs(alturaArbolBinario(abArbol, abArbol.hijoDrcho(nd)) - alturaArbolBinario(abArbol, abArbol.hijoIzqdo(nd)));
}

int desequilibrioMaximoRec(Abin<int> abArbol, typename Abin<int>::nodo nd)
{
    if (nd == Abin<int>::NODO_NULO)
    {
        return 0;
    }
    return std::fmax(
        std::fmax(desequilibrioMaximoRec(abArbol, abArbol.hijoDrcho(nd)),
                  desequilibrioMaximoRec(abArbol, abArbol.hijoIzqdo(nd))),
        diferenciaAlturas(abArbol, nd));
}

int desequilibrioAbin(Abin<int> abArbol)
{
    if (abArbol.arbolVacio())
        return 0;
    else
        return desequilibrioMaximoRec(abArbol, abArbol.raiz());
}

// ###################################################################################
/**
 * Practica 3 de Arboles Generales
 */

/**
 * Ejercicio 1: Contar los nodos en un arbol general.
 */
template <class T>
int numNodosAgen(Agen<T> &agArbol, typename Agen<T>::nodo nd)
{
    int iNumNodos = 0;
    if (nd != Agen<T>::NODO_NULO)
    {
        nd = agArbol.hijoIzqdo(nd);
        while (nd != Agen<T>::NODO_NULO)
        {
            numNodosAgen(agArbol, nd);
            iNumNodos++;
            nd = agArbol.hermDrcho(nd);
        }
    }
    return iNumNodos;
}

int main()
{
    Abin<int> ab;
    ab.insertaRaiz(1);
    ab.insertarhijoIzqdo(ab.raiz(), 2);
    ab.insertarhijoDrcho(ab.raiz(), 3);
    ab.insertarhijoIzqdo(ab.hijoDrcho(ab.raiz()), 4);

    std::cout << desequilibrioMaximoRec(ab, ab.raiz()) << std::endl;
    return 0;
}
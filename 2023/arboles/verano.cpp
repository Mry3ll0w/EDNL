#include <iostream>
#include "arbolbinenla.h"
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

template <class T>
int diferenciaAlturas(Abin<T> abArbol, typename Abin<T>::nodo nd)
{
    return std::abs(alturaArbolBinario(abArbol, abArbol.hijoDrcho(nd)) - alturaArbolBinario(abArbol, abArbol.hijoIzqdo(nd)));
}

template <class T>
int desequilibrioMaximoRec(Abin<T> abArbol, typename Abin<T>::nodo nd1)
{
    if (nd == Abin<T>::NODO_NULO)
    {
        return 0;
    }
    return std::fmax(desequilibrioMaximoRec(abArbol, nd),
                     desequilibrioMaximoRec(abArbol, abArbol.hijoDrcho(nd)), abArbol.hijoIzqdo(nd));
}

template <class T>
int desequilibrioAbin(Abin<T> abArbol)
{
    if (abArbol.arbolVacio())
        return 0;
    else
        return desequilibrioMaximoRec(abArbol, abArbol.raiz());
}

int main()
{
    Abin<int> ab;
    ab.insertaRaiz(1);
    /* ab.insertarhijoIzqdo(ab.raiz(), 2);
    ab.insertarhijoDrcho(ab.raiz(), 3);
    ab.insertarhijoIzqdo(ab.hijoDrcho(ab.raiz()), 4);
    */
    std::cout << alturaArbolBinario(ab, ab.raiz()) << std::endl;
    return 0;
}
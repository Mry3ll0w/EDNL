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

// ####################################################################################

// Practica 2 Arboles binarios
/**
 * Ejercicio 1:
 * Dos árboles binarios son similares cuando tienen idéntica estructura de ramificación,
 * es decir, ambos son vacíos, o en caso contrario, tienen subárboles izquierdo y
 * derecho similares.
 * Implementa un subprograma que determine si dos árboles binarios son similares
 */

template <class T>
bool arbolesSimilaresAbin(const Abin<T> abArbol1, const Abin<T> abArbol2,
                          typename Abin<T>::nodo nd1, typename Abin<T>::nodo nd2)
{
    if (nd1 == Abin<T>::NODO_NULO && nd2 == Abin<T>::NODO_NULO)
    {
        return true; // Si cuando sale del bucle ambos no son nulos tiene != ramificacion
    }
    else if (nd1 != Abin<T>::NODO_NULO && nd2 != Abin<T>::NODO_NULO)
    {
        return arbolesSimilaresAbin(abArbol1, abArbol2, abArbol1.hijoIzqdo(nd1), abArbol2.hijoIzqdo(nd2)) &&
               arbolesSimilaresAbin(abArbol1, abArbol2, abArbol1.hijoDrcho(nd1), abArbol2.hijoDrcho(nd2));
    }
    return false;
    // Comprobamos que pasa al salir
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
    Abin<int> ab1, ab2;
    ab1.insertaRaiz(1);
    ab1.insertarhijoIzqdo(ab1.raiz(), 2);
    ab1.insertarhijoDrcho(ab1.raiz(), 3);
    ab1.insertarhijoIzqdo(ab1.hijoDrcho(ab1.raiz()), 4);

    ab2.insertaRaiz(1);
    ab2.insertarhijoIzqdo(ab2.raiz(), 2);
    ab2.insertarhijoDrcho(ab2.raiz(), 3);
    ab2.insertarhijoIzqdo(ab2.hijoDrcho(ab2.raiz()), 4);

    std::cout << arbolesSimilaresAbin(ab1, ab2, ab1.raiz(), ab2.raiz()) << std::endl;
    return 0;
}
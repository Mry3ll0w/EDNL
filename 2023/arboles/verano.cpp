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

/**
 * Ejercicio 2
 * Para un árbol binario B, podemos construir el árbol binario reflejado BR cambiando los
 * subárboles izquierdo y derecho en cada nodo.
 * Implementa un subprograma que devuelva el árbol binario reflejado de uno dado.
 */

template <class T>
void arbolReflejadoAbin(const Abin<T> &abArbolOriginal, Abin<T> abArbolDestino, typename Abin<T>::nodo nd1,
                        typename Abin<T>::nodo nd2)
{
    if (nd1 != Abin<T>::NODO_NULO)
    {

        if (abArbolOriginal.hijoIzqdo(nd1) != Abin<T>::NODO_NULO)
        {
            abArbolDestino.insertarhijoDrcho(nd2, abArbolOriginal.elemento(abArbolOriginal.hijoIzqdo(nd1)));
            arbolReflejadoAbin(abArbolOriginal, abArbolDestino, abArbolOriginal.hijoIzqdo(nd1), abArbolDestino.hijoDrcho(nd2));
        }
        if (abArbolOriginal.hijoDrcho(nd1) != Abin<T>::NODO_NULO)
        {
            abArbolDestino.insertarhijoIzqdo(nd2, abArbolOriginal.elemento(abArbolOriginal.hijoDrcho(nd1)));
            arbolReflejadoAbin(abArbolOriginal, abArbolDestino, abArbolOriginal.hijoDrcho(nd1), abArbolDestino.hijoIzqdo(nd2));
        }
    }
}

/**Ejercicio 3
 * El TAD árbol binario puede albergar expresiones matemáticas mediante un árbol de expresión.
 * Dentro del árbol binario los nodos hojas contendrán los operandos, y el resto de los nodos
 * los operadores.
 *
 *      a) Define el tipo de los elementos del árbol para que los nodos puedan almacenar
 *          operadores y operandos.
 *
 *      b) Implementa una función que tome un árbol binario de expresión (aritmética) y
 *         devuelva el resultado de la misma. Por simplificar el problema se puede asumir
 *         que el árbol representa una expresión correcta. Los operadores binarios posibles
 *         en la expresión aritmética serán suma, resta, multiplicación y división.
 */

double procesaPostfijo(Abin<std::string> A, typename Abin<std::string>::nodo n)
{
    std::string strElemento = A.elemento(n);

    if (strElemento == "+")
    {
        return (procesaPostfijo(A, A.hijoIzqdo(n)) + procesaPostfijo(A, A.hijoDrcho(n)));
    }
    else if (strElemento == "-")
    {
        return (procesaPostfijo(A, A.hijoIzqdo(n)) + procesaPostfijo(A, A.hijoDrcho(n)));
    }
    else if (strElemento == "*")
    {
        return (procesaPostfijo(A, A.hijoIzqdo(n)) * procesaPostfijo(A, A.hijoDrcho(n)));
    }
    else if (strElemento == "/")
    {
        return (procesaPostfijo(A, A.hijoIzqdo(n)) / procesaPostfijo(A, A.hijoDrcho(n)));
    }
    else
    {
        return std::stof(strElemento);
    }
}

template <class T>
void printAbin(Abin<T> ab, typename Abin<T>::nodo nd)
{
    if (nd != Abin<T>::NODO_NULO)
    {
        printAbin(ab, ab.hijoDrcho(nd));
        std::cout << ab.elemento(nd) << ", ";
        printAbin(ab, ab.hijoIzqdo(nd));
    }
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
    Abin<int> ab1, ab2, ab3;
    ab1.insertaRaiz(1);
    ab1.insertarhijoIzqdo(ab1.raiz(), 2);
    ab1.insertarhijoDrcho(ab1.raiz(), 3);
    ab1.insertarhijoIzqdo(ab1.hijoDrcho(ab1.raiz()), 4);

    ab2.insertaRaiz(1);
    ab2.insertarhijoIzqdo(ab2.raiz(), 2);
    ab2.insertarhijoDrcho(ab2.raiz(), 3);
    ab2.insertarhijoIzqdo(ab2.hijoDrcho(ab2.raiz()), 4);
    ab3.insertaRaiz(1);
    arbolReflejadoAbin(ab1, ab3, ab1.raiz(), ab3.raiz());

    printAbin(ab1, ab1.raiz());
    std::cout << "··························" << std::endl;
    printAbin(ab3, ab3.raiz());

    return 0;
}
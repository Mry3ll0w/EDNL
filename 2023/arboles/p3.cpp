#include <iostream>
#include "agenEnlazado.h"

// Recorrido en preorden
template <typename T>
void preordenAgen(typename Agen<T>::nodo n, const Agen<T> &A,
                  void (*procesar)(typename Agen<T>::nodo, const Agen<T> &))
// Recorrido en preorden del subárbol cuya raíz es el nodo n
// perteneciente al árbol A. Cada nodo visitado se procesa mediante // la función procesar().
{
    if (n != Agen<T>::NODO_NULO)
    {
        procesar(n, A);
        n = A.hijoIzqdo(n);
        while (n != Agen<T>::NODO_NULO)
        {
            preordenAgen(n, A, procesar);
            n = A.hermDrcho(n);
        }
    }
}

template <typename T>
int numHijosSubArbolGeneral(typename Agen<T>::nodo n, const Agen<T> &A)
// Recorrido en preorden del subárbol cuya raíz es el nodo n
// perteneciente al árbol A. Cada nodo visitado se procesa mediante // la función procesar().
{
    int iNumeroHijos = 0;
    if (n != Agen<T>::NODO_NULO)
    {
        n = A.hijoIzqdo(n);
        while (n != Agen<T>::NODO_NULO)
        {
            numHijosSubArbolGeneral(n, A);
            iNumeroHijos++; // contamos el numero de hijos del nivel
            n = A.hermDrcho(n);
        }
    }
    return iNumeroHijos;
}

// Grado de un arbol general es el maximo numero de hijos de un nodo
template <class T>
int gradoArbolGeneralRec(typename Agen<T>::nodo n, Agen<T> &A)
{
    int iGradoArbol = 0;
    if (n != Agen<T>::NODO_NULO)
    {
        iGradoArbol = std::max(iGradoArbol, numHijosSubArbolGeneral(n, A));
        n = A.hijoIzqdo(n);
        while (n != Agen<T>::NODO_NULO)
        {
            gradoArbolGeneralRec(n, A);
            n = A.hermDrcho(n);
        }
    }
    return iGradoArbol;
}

template <class T>
int gradoArbolGeneral(Agen<T> &abArbol)
{
    if (abArbol.arbolVacio())
        return 0;
    else
        return gradoArbolGeneralRec(abArbol.raiz(), abArbol);
}

// Ejercicio 2
// Implementa un subprograma que dados un árbol y un nodo dentro de dicho árbol determine la profundidad de éste nodo en el árbol.
// Es exactamente la misma funcion que en los nodos binarios
template <class T>
int profundidadNodoAgen(typename Agen<T>::NODO nd, Agen<T> &agArbol)
{
    if (nd == agArbol.raiz())
    {
        return 0;
    }
    else
        return 1 + profundidadNodoAgen(agArbol.padre(nd), agArbol);
}

/**
 * Ejercicio 3
 * Se define el desequilibrio de un árbol general como la máxima diferencia entre las alturas de los subárboles más bajo y
 * más alto de cada nivel. Implementa un subprograma que calcule el grado de desequilibrio de un árbol general.
 * Para obtener el desequilibrio necesitamos:
 * 1) Altura de un nodo
 * 2) Maxima altura ==> altura del nodo raiz
 * 3) Minima altura
 */

template <class T>
int alturaNodoAgen(typename Agen<T>::nodo nd, Agen<T> &agArbol)
{
    int iAlturaNodo = -1;
    if (nd != Agen<T>::NODO_NULO)
    {
        nd = agArbol.hijoIzqdo(nd);
        while (nd != Agen<T>::NODO_NULO)
        {
            // Proceso la altura en inorden
            iAlturaNodo = std::max(iAlturaNodo, alturaNodoAgen(nd, agArbol)); // Hundimiento en recursividad
            nd = agArbol.hermDrcho(nd);
        }
    }
    return 1 + iAlturaNodo; // Hacemos 1 + puesto que cada vez que pueda la funcion hundirse significa que hemos bajado de nivel ==> +1 altura
}
// Al definir el desequilibrio entre las altura maxima y minima simplemente obtendremos la altura minima y haremos el valor absoluto de su resta
template <class T>
int minimaAlturaNodoAgen(typename Agen<T>::nodo nd, Agen<T> &agArbol)
{
    int iAlturaMinima = -1; // Por no definirlo con la clave INT_MAX, no me acuerdo de la biblioteca
    if (nd != Agen<T>::NODO_NULO)
    {

        nd = agArbol.hijoIzqdo(nd);
        while (nd != Agen<T>::NODO_NULO)
        {
            iAlturaMinima = std::min(iAlturaMinima, minimaAlturaNodoAgen(nd, agArbol));
            nd = agArbol.hermDrcho(nd);
        }
    }
    return iAlturaMinima + 1;
}

// Calcular el desequilibrio

template <class T>
int desequilibrioAgen(Agen<T> agenArbol)
{
    if (agenArbol.arbolVacio())
        return 0;
    else
    {
        return std::abs(alturaNodoAgen(agenArbol.raiz(), agenArbol) - minimaAlturaNodoAgen(agenArbol.raiz(), agenArbol));
    }
}

int main()
{
    Agen<int> A;
    A.insertaRaiz(1);
    A.insertarHijoIzqdo(A.raiz(), 2);
    A.insertarHermDrcho(A.hijoIzqdo(A.raiz()), 3);
    auto n = A.hermDrcho(A.hijoIzqdo(A.raiz()));
    A.insertarHijoIzqdo(A.hijoIzqdo(A.raiz()), 39);
    auto n2 = A.hijoIzqdo(A.hijoIzqdo(A.raiz()));

    // insertamos 4 hermanos
    for (int i = 4; i < 7; ++i)
        A.insertarHermDrcho(n, i);
    n = A.hermDrcho(n);

    for (int i = 9; i < 15; ++i)
        A.insertarHermDrcho(n2, i);
    n2 = A.hermDrcho(n2);
    std::cout << desequilibrioAgen(A) << std::endl;

    return 0;
}
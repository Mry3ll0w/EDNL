#include <iostream>
#include "../arboles/arbolbinenla.h"
using namespace std; // Avoid using std:: ....

// Funcion para mostrar los elementos contenidos dentro de un arbol binario
template <class T>
void printAbin(const Abin<T> &a, typename Abin<T>::nodo n)
{
    if (n != Abin<T>::NODO_NULO)
    {
        printAbin(a, a.hijoIzqdo(n));
        cout << a.elemento(n) << ", ";
        printAbin(a, a.hijoDrcho(n));
    }
    cout << endl;
}

// Cabeceras

/**
 * @brief Dos árboles binarios son similares cuando tienen idéntica estructura de ramificación,
 * es decir, ambos son vacíos, o en caso contrario, tienen subárboles izquierdo y derecho
 * similares. Implementa un subprograma que determine si dos árboles binarios son
 * similares.
 */
template <class T>
bool similaresRec(const Abin<T> &arbol1, const Abin<T> &arbol2, typename Abin<T>::nodo na, typename Abin<T>::nodo nb)
{
    if (na == Abin<T>::NODO_NULO || nb == Abin<T>::NODO_NULO)
    {
        if (na == Abin<T>::NODO_NULO && nb == Abin<T>::NODO_NULO)
            return true;
        else
            return false;
    }

    // Caso General
    if (
        (arbol1.hijoDrcho(na) != Abin<T>::NODO_NULO && arbol2.hijoDrcho(nb) != Abin<T>::NODO_NULO) ||
        (arbol1.hijoDrcho(na) == Abin<T>::NODO_NULO && arbol2.hijoDrcho(nb) == Abin<T>::NODO_NULO))
        return true && similaresRec(arbol1, arbol2, arbol1.hijoDrcho(na), arbol2.hijoDrcho(nb)) && similaresRec(arbol1, arbol2, arbol1.hijoIzqdo(na), arbol2.hijoIzqdo(nb));
    else
    {
        return false;
    }
}

template <class T>
bool similares(Abin<T> &a, Abin<T> &b)
{
    if (a.arbolVacio() && b.arbolVacio())
        return true;
    else
        return similaresRec(a, b, a.raiz(), b.raiz());
}

/**
 * @brief
 * Para un árbol binario B, podemos construir el árbol binario reflejado BR
 * cambiando los subárboles izquierdo y derecho en cada nodo.
 * Implementa un subprograma que devuelva el árbol binario reflejado de uno dado
 */
template <class T>
void arbolReflejadoRec(const Abin<T> &a, typename Abin<T>::nodo na, Abin<T> &b, typename Abin<T>::nodo nb)
{
    if (a.hijoIzqdo(na) != Abin<T>::NODO_NULO)
    {
        b.insertarhijoDrcho(nb, a.elemento(a.hijoIzqdo(na)));
        arbolReflejadoRec(a, a.hijoIzqdo(na), b, b.hijoDrcho(nb));
    }
    if (a.hijoDrcho(na) != Abin<T>::NODO_NULO)
    {
        b.insertarhijoIzqdo(nb, a.elemento(a.hijoDrcho(na)));
        arbolReflejadoRec(a, a.hijoDrcho(na), b, b.hijoIzqdo(nb));
    }
}

template <class T>
Abin<T> arbolReflejado(const Abin<T> a)
{
    if (a.arbolVacio())
        return Abin<T>();
    else
    {
        Abin<T> b;
        b.insertaRaiz(a.elemento(a.raiz()));
        reflejo_arbol_rec(a.raiz(), b.raiz(), a, b);
        return b;
    }
}

int main()
{
    Abin<int> a, b;
    a.insertaRaiz(1);
    a.insertarhijoDrcho(a.raiz(), 2);
    a.insertarhijoIzqdo(a.raiz(), 3);
    a.insertarhijoIzqdo(a.hijoIzqdo(a.raiz()), 4);
    a.insertarhijoDrcho(a.hijoDrcho(a.raiz()), 5);

    Abin<int> reflejo;
    reflejo.insertaRaiz(a.elemento(a.raiz()));
    arbolReflejadoRec(a, a.raiz(), reflejo, reflejo.raiz());
    cout << "ARBOL ORIGINAL" << endl;
    printAbin(a, a.raiz());
    cout << "Arbol reflejado" << endl;
    printAbin(reflejo, reflejo.raiz());

    return 0;
}
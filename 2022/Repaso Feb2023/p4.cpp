#include <iostream>
#include <vector>
#include "abb.h"
using namespace std; // Avoid using std:: ....

template <class T>
void mostrarArbol(Abb<T> A)
{
    if (!A.vacio())
    {
        mostrarArbol(A.izqdo());
        cout << A.elemento() << ", ";
        mostrarArbol(A.drcho());
    }
    cout << endl;
}

template <class T>
Abb<T> podaSubArbol(const T &elto, Abb<T> A)
{
    Abb<T> subArbol = A.buscar(elto);
    if (!A.vacio() && !subArbol.vacio())
    {
        A.buscar(elto).~Abb();
        // Cuando llamamos al destructor devuelto por la operacion de busqueda
        // al ser este un abb, si llamamos a su destructor se autoelimina el subarbol.
    }
    return A;
}

/**
 * Un árbol binario de búsqueda se puede equilibrar realizando el recorrido en inorden
 * del  árbol  para  obtener  el  listado  ordenado  de  sus  elementos  y  a  continuación,
 * repartir equitativamente los elementos a izquierda y derecha colocando la mediana en
 * la raíz y construyendo recursivamente los subárboles izquierdo y derecho de cada nodo.
 * Implementa este algoritmo para equilibrar un ABB.
 * 1) Funcion para obtener el listado de elementos de un arbol
 * 2) Repartir Elementos de forma equitativa
 */

template <class T>
void abbToVector(Abb<T> A, vector<T> &aElements)
{
    if (!A.vacio())
    {
        abbToVector(A.izqdo(), aElements);
        aElements.push_back(A.elemento());
        abbToVector(A.drcho(), aElements);
    }
}

template <class T>
Abb<T> equilibrarAbb(Abb<T> A)
{
    if (!A.vacio())
    {
        vector<T> aElementosVector;
        abbToVector(A, aElementosVector);
        int iMediana = aElementosVector.size() / 2;
        Abb<T> abbEquilibrado;
        abbEquilibrado.insertar(aElementosVector[iMediana]);
        int i = 0;
        for (; i < iMediana; ++i)
        {
            abbEquilibrado.insertar(aElementosVector[i]);
        }
        i++; // Pasamos a la siguiente de la mediana puesto que se ha insertado
        for (; i < aElementosVector.size(); ++i)
            abbEquilibrado.insertar(aElementosVector[i]);

        return abbEquilibrado;
    }
    else
    {
        return Abb<T>();
    }
}

int main()
{
    Abb<int> A;
    A.insertar(7);
    A.insertar(5);
    A.insertar(12);
    A.insertar(9);
    A.insertar(17);
    A.insertar(8);
    A.insertar(11);
    A = equilibrarAbb(A);
    mostrarArbol(A);
    return 0;
}
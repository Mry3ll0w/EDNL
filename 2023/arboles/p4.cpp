#include <iostream>
#include <vector>
#include "abb.h"

// funcion para mostrar los elementos del subarbol
template <class T>
void mostrarSubArbol(Abb<T> abbArbol)
{
    if (!abbArbol.vacio())
    {
        mostrarSubArbol(abbArbol.izqdo());
        std::cout << abbArbol.elemento() << std::endl;
        mostrarSubArbol(abbArbol.drcho());
    }
}

/**
 * Ejercicio 1:Escribir una funcion para abb que elimine el nodo que cuelga del subarbol.
 */

template <class T>
void eliminarSubArbol(Abb<T> &abbArbol, const T &tElto)
{
    abbArbol.buscar(tElto).~Abb(); // Me cargo al el subarbol
}

/**
 *  Un árbol binario de búsqueda se puede equilibrar realizando el recorrido en inorden del árbol
 *  para obtener el listado ordenado de sus elementos y a continuación, repartir equitativamente
 *  los elementos a izquierda y derecha colocando la mediana en la raíz y construyendo recursivamente
 *  los subárboles izquierdo y derecho de cada nodo. Implementa este algoritmo para equilibrar un ABB.
 *  1) Recorrer todos los elementos del arbol en inorden y guardarlos en un vector
 *  2) Eliminar todos los elementos del arbol
 *  3) Insertar la mediana del vector en el arbol
 *  4) Insertar los elementos de la izquierda de la mediana en el arbol
 */

template <class T>
void recorrerInorden(const Abb<T> &abbArbol, std::vector<T> &vElementos)
{
    if (!abbArbol.vacio())
    {
        recorrerInorden(abbArbol.izqdo(), vElementos);
        vElementos.push_back(abbArbol.elemento());
        recorrerInorden(abbArbol.drcho(), vElementos);
    }
}

template <class T>
void equilibrar(Abb<T> &abbArbol) // Corregir se tiene que insertar en Dicotomica
{
    if (!abbArbol.vacio())
    {

        std::vector<T> vElementos;
        recorrerInorden(abbArbol, vElementos); // primero izquierdos (mas pequeños) y desp derechos (maypr tamaño)
        abbArbol = Abb<T>();                   // Igualamos el arbol a uno vacio

        abbArbol.insertar(vElementos[vElementos.size() / 2]); // Insertamos la mediana
        for (int i = 0; i < vElementos.size() / 2; i++)
        {
            abbArbol.insertar(vElementos[i]);
        }
        for (int i = vElementos.size() / 2 + 1; i < vElementos.size(); i++)
        {
            abbArbol.insertar(vElementos[i]);
        }
    }
}

/**
 * Dados dos conjuntos representados mediante árboles binarios de búsqueda, implementa
 * la operación unión de dos conjuntos que devuelva como resultado otro conjunto
 * que sea la unión de ambos, representado por un ABB equilibrado.
 * La union de dos conjuntos ==> elementos que estan en arbol1 junto con los que estan en abb2.
 */
template <class T>
Abb<T> unionAbb(Abb<T> abbArbol1, Abb<T> abbArbol2)
{
    Abb<T> abbUnion = abbArbol1;
    if (!abbArbol2.vacio())
    {
        unionAbb(abbArbol1, abbArbol2.izqdo());
        abbUnion.insertar(abbArbol2.elemento());
        unionAbb(abbArbol1, abbArbol2.drcho());
    }
    equilibrar(abbUnion);
    return abbUnion;
}

/**
 * Dados dos conjuntos representados mediante árboles binarios de búsqueda, implementa la
 * operación intersección de dos conjuntos, que devuelva como resultado otro conjunto que
 * sea la intersección de ambos. El resultado debe quedar en un árbol equilibrado.
 */
template <class T>
Abb<T> interseccionAbb(Abb<T> abbArbol1, Abb<T> abbArbol2)
{
    Abb<T> abbInterseccion;
    if (!abbArbol2.vacio())
    {
        interseccionAbb(abbArbol1, abbArbol2.izqdo());
        if (!abbArbol1.buscar(abbArbol2.elemento()).vacio())
        { // El elemento de ab2 esta en ab1
            abbInterseccion.insertar(abbArbol2.elemento());
        }
        interseccionAbb(abbArbol1, abbArbol2.drcho());
    }
    equilibrar(abbInterseccion);
    return abbInterseccion;
}

/**
 * Implementa el operador  para conjuntos definido como A  B = (A U B) - (A Int B). La implementación del operador  debe
 * realizarse utilizando obligatoriamente la operación , que nos indica si un elemento dado pertenece o no a un conjunto.
 * La representación del tipo Conjunto debe ser tal que la operación de pertenencia esté en el caso promedio en O(log n)
 */

template <class T>
bool operacionPertenencia(Abb<T> abbArbol1, const T &tElto)
{
    return !abbArbol1.buscar(tElto).vacio(); // Si el arbol no esta vacio pertenece al conjunto
}

template <class T>
Abb<T> restaAbb(Abb<T> abbArbol1, Abb<T> abbArbol2)
{
    Abb<T> abbResta = abbArbol1;
    if (!abbArbol2.vacio())
    {
        restaAbb(abbArbol1, abbArbol2.izqdo());
        if (operacionPertenencia(abbArbol1, abbArbol2.elemento()))
        {
            abbResta.eliminar(abbArbol2.elemento());
        }
        restaAbb(abbArbol1, abbArbol2.drcho());
    }
    return abbResta;
}

template <class T>
Abb<T> operadorRomboAbb(Abb<T> abbArbol1, Abb<T> abbArbol2)
{
    Abb<T> abbUnion = unionAbb(abbArbol1, abbArbol2);
    Abb<T> abbInterseccion = interseccionAbb(abbArbol1, abbArbol2);
    return restaAbb(abbUnion, abbInterseccion);
}

int main()
{
    Abb<int> abbArbol, abbArbol2;
    abbArbol2.insertar(4);
    abbArbol2.insertar(12);

    abbArbol.insertar(5);
    abbArbol.insertar(3);
    abbArbol.insertar(7);
    abbArbol.insertar(2);
    abbArbol.insertar(4);
    abbArbol.insertar(6);
    abbArbol.insertar(8);

    std::cout << "Union" << std::endl;
    mostrarSubArbol(unionAbb(abbArbol, abbArbol2));
    std::cout << "Interseccion" << std::endl;
    mostrarSubArbol(interseccionAbb(abbArbol, abbArbol2));

    std::cout << "Operacion rombo" << std::endl;
    mostrarSubArbol(operadorRomboAbb(abbArbol, abbArbol2));

    return 0;
}

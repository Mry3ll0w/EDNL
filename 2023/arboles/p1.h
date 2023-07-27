
#ifndef EDNLV2_P1_H
#define EDNLV2_P1_H
#include "arbolbinenla.h"
#include <iostream>
#include <algorithm>
// Ejercicio 1
template <typename t>
size_t node_counter(Abin<t> &a, typename Abin<t>::nodo n)
{

    if (n == Abin<t>::NODO_NULO)
    {
        return 0;
    }
    return 1 + node_counter(a, a.hijoDrcho(n)) + node_counter(a, a.hijoIzqdo(n));
}
template <typename t>
size_t ej1(Abin<t> &a)
{
    return node_counter(a, a.raiz());
}

// EJERCICIO 2==> Calcular la altura de un arbol binario
template <typename t>
int altura_rec(typename Abin<t>::nodo n, Abin<t> &Arbol)
{
    if (n == Abin<t>::NODO_NULO)
    {
        return -1; // La altura de una hoja es cero --> Altura nodo_nulo = -1 + 1 = 0
    }
    return 1 + fmax(altura_rec(Arbol.hijoIzqdo(n), Arbol), altura_rec(Arbol.hijoDrcho(n), Arbol));
}

template <class t>
size_t ej2(Abin<t> &a)
{
    return altura_rec(a.raiz(), a);
}

// EJERCICIO 3 profundidad de un nodo
template <class t>
size_t ej3(typename Abin<t>::nodo n, Abin<t> &a)
{
    if (n == a.raiz())
        return 0;
    return 1 + ej3(a.padre(n), a);
    // La profundidad sera el numero de padres que tiene el nodo
    //(hasta llegar a la raiz)
}

/* EJERCICIO 4
 * Implementa un subprograma que determine el nivel de desequilibrio de un árbol binario,
 * definido como el máximo desequilibrio de todos sus nodos.
 * El desequilibrio de un nodo se define como la diferencia entre las alturas
 * de los subárboles del mismo.
 */
template <typename t>
size_t difAltura(typename Abin<t>::nodo n, Abin<t> &a)
{
    return std::abs(altura_rec(a.hijoIzqdo(n), a) - altura_rec(a.hijoDrcho(n), a));
} // Obtenemos las alturas

template <class t>
size_t desequilibrio(typename Abin<t>::nodo n, Abin<t> &Arbol)
{
    if (n == Abin<t>::NODO_NULO)
    {
        return 0;
    }
    return fmax(difAltura(n, Arbol), fmax(desequilibrio(Arbol.hijoDrcho(n), Arbol),
                                          desequilibrio(Arbol.hijoIzqdo(n), Arbol)));
    // Grado maximo del nodo n y sus dos hijos, siendo el desequilibrio el maximo de los mismos
}

template <class t>
size_t ej_6(Abin<t> &a)
{
    return desequilibrio(a.raiz(), a); // Llamada al desequilibrio de las alturas
}

/** EJERCICIO 7
 * Implementa un subprograma que determine si un árbol binario es o no pseudocompleto.
 * En este problema entenderemos que un árbol es pseudocompleto, si en el penúltimo nivel
 * del mismo cada uno de los nodos tiene dos hijos o ninguno.
 */
template <class t>
bool pseudo_completo(typename Abin<t>::nodo n, Abin<t> &a, int iPenultimoNivel)
{
    if (n != Abin<t>::NODO_NULO)
    {
        if (altura_rec(n, a) == iPenultimoNivel and n != a.raiz())
        { // HEMOS LLEGADO AL PENULTIMO NIVEL, ya que el penultimo nivel debe tener altura 1
            auto nodo_d = a.hijoDrcho(a.padre(n));
            auto nodo_i = a.hijoIzqdo(a.padre(n));
            // Comprobamos si es pseudo completo
            if ((a.hijoIzqdo(nodo_d) != Abin<t>::NODO_NULO and a.hijoDrcho(nodo_d) != Abin<t>::NODO_NULO and
                 a.hijoIzqdo(nodo_i) == Abin<t>::NODO_NULO and a.hijoDrcho(nodo_i) == Abin<t>::NODO_NULO) or
                (a.hijoIzqdo(nodo_i) != Abin<t>::NODO_NULO and a.hijoDrcho(nodo_i) != Abin<t>::NODO_NULO and
                 a.hijoIzqdo(nodo_d) == Abin<t>::NODO_NULO and a.hijoDrcho(nodo_d) == Abin<t>::NODO_NULO) or
                (a.hijoIzqdo(nodo_d) == Abin<t>::NODO_NULO and a.hijoDrcho(nodo_d) == Abin<t>::NODO_NULO and
                 a.hijoIzqdo(nodo_i) == Abin<t>::NODO_NULO and a.hijoDrcho(nodo_i) == Abin<t>::NODO_NULO))
            {
                return true;
            }
            else
                return false;
        }
    }

    return pseudo_completo(a.hijoDrcho(n), a, iPenultimoNivel) && pseudo_completo(a.hijoIzqdo(n), a, iPenultimoNivel);
}

template <class t>
bool ej_7(Abin<t> &a)
{
    if (a.arbolVacio())
        return true;
    else
        return pseudo_completo(a.raiz(), a, altura_rec(a.raiz(), a) - 1);
}

#endif // EDNLV2_P1_H

#ifndef EDNLV2_P3_H
#define EDNLV2_P3_H
#include "arbolgenenla.h"
#include <algorithm>
#include <iostream>
/*
 * EJERCICIO 1
 * Implementa un subprograma que dado un árbol general nos calcule su grado.
 * Grado = numero de nodos de un nodo, grado maximo ==> grado del arbol
 */
template <class t>
size_t node_counter(typename Agen<t>::nodo n,Agen<t>& a){
    if (n==Agen<t>::NODO_NULO)
        return 0;
    else
        return 1 + node_counter(a.hermDrcho(n),a);
}
template <class t>
size_t node_aux_max(typename Agen<t>::nodo n,size_t cont,Agen<t>& a){
    if (n==Agen<t>::NODO_NULO){
        return cont;
    }
    cont = std::max(node_counter(a.hermDrcho(n),a),node_counter(n,a));
    node_aux_max(a.hijoIzqdo(n),cont,a);
}
template <class t>
size_t ej1(Agen<t>&a) {
    return node_aux_max(a.raiz(),0,a);
}
/**
 * EJERCICIO 2
 * Implementa un subprograma que dados un árbol y un nodo dentro de dicho árbol determine
 * la profundidad de éste nodo en el árbol.
 * Profundidad de un arbol ==> maximo de padres de un nodo
 */
template <class t>
size_t n_node_fathers(typename Agen<t>::nodo n,Agen<t>&a){
    if (n==Agen<t>::NODO_NULO)
        return 0;
    else
        return 1 + n_node_fathers(a.hermDrcho(n),a);
}

template <class t>
size_t profundidad_agen(typename Agen<t>::nodo n,size_t cont, Agen<t>&a){
    if (n==Agen<t>::NODO_NULO){
        return cont;
    }
    auto iterator = a.hermDrcho(n);

    while (iterator != Agen<t>::NODO_NULO ){
        size_t aux = n_node_fathers(iterator,a);
        if (cont <  aux){
            cont = aux;
        }
        iterator = a.hermDrcho(iterator);
    }
    profundidad_agen(a.hijoIzqdo(n),cont,a);
}
template <class t>
size_t ej2(Agen<t>&a ){
    return profundidad_agen(a.raiz(), n_node_fathers(a.hijoIzqdo(a.raiz()),a),a);
}

/*
 *  Se define el desequilibrio de un árbol general como la máxima diferencia entre las alturas
 *  de los subárboles más bajo y más alto de cada nivel. Implementa un subprograma que calcule
 *  el grado de desequilibrio de un árbol general.
 */
template <class t>
size_t altura_hijos(typename Agen<t>::nodo n,Agen<t>& a){
    size_t cont=0;
    while (n ==Agen<t>::NODO_NULO){
        ++cont;
        n = a.hijoIzqdo(n);
    }
    return cont;
}

template <class t>
size_t desequilibrio(typename Agen<t>::nodo n,size_t max,size_t& min,Agen<t>& a){

    if (n != Agen<t>::NODO_NULO){
        return max;
    }
    else{
        auto n2 = a.hijoIzqdo(n);
        size_t max_aux = altura_hijos(n,a);
        while (n2 != Agen<t>::NODO_NULO){
            //size_t aux = altura_hijos(n2,a);
            max = std::max(max,altura_hijos(n2,a));
            min = std::min(min,altura_hijos(n2,a));
            n2 = a.hermDrcho(n2);
        }
        return std::max(max,max_aux);
    }

}
template <class t>
size_t ej3(Agen<t>&a){
    size_t min=0;
    return desequilibrio(a.raiz(),0,min,a)-min;
}

/*      EJERCICIO 4 (PODA)
 *  Dado un árbol general de enteros A y un entero x, implementa un subprograma que realice
 *  la poda de A a partir de x. Se asume que no hay elementos repetidos en A.
 */
Agen<int>::nodo find_hijo(typename Agen<int>::nodo n,int v,bool encontrado, Agen<int>& a){
    if (n == Agen<int>::NODO_NULO || encontrado){
        return n;
    }
    auto n2 = n;
    while (n2 != Agen<int>::NODO_NULO && !encontrado){
        if (a.elemento(n2)==v)
            encontrado=true;
        n2 = a.hermDrcho(n2);
    }
    return find_hijo(a.hijoIzqdo(n),v,encontrado,a);
}
#endif //EDNLV2_P3_H

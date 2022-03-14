//
// Created by anton on 22/03/2021.
//

#ifndef EDNL_PRACTICA3_H
#define EDNL_PRACTICA3_H
#include "agenEnlazado.h"
#include <algorithm>
template <typename t>
int counter_hijos(typename Agen<t>::nodo n,Agen<t> tree){
    typename Agen<t>::nodo nodo_aux=tree.hijoIzqdo(n);
    int node_counter=0;
    while (nodo_aux!=Agen<t>::NODO_NULO){
        node_counter++;
        nodo_aux=tree.hermDrcho(nodo_aux);
    }
    return node_counter;
}

template<typename t>
int grado_nodo_rec(Agen<t>tree,typename Agen<t>:: nodo n){
    int aux_hijos, maxhijos=0;
    typename Agen<t>::nodo nodo_aux;
    if (n==Agen<t>::NODO_NULO){
        return maxhijos;
    }
    else{
        aux_hijos=counter_hijos(n,tree);
        nodo_aux=tree.hijoIzqdo(n);
        while (nodo_aux != Agen<t>::NODO_NULO){
            maxhijos=std::max(maxhijos,grado_nodo_rec(tree,nodo_aux));
            nodo_aux = tree.hermDrcho(nodo_aux);//recorre en profundidad
        }
        return std::max(maxhijos,aux_hijos);
    }
}

template <typename t>
int grado_arbol(Agen <t> tree ){
    return grado_nodo_rec(tree,tree.raiz());
}

template <typename t>
int profundidad_nodo(Agen<t>tree, typename Agen<t>::nodo n){
    if (n==Agen<t>::NODO_NULO){
        return -1;
    }
    else
        return profundidad_nodo(tree,tree.padre(n))+1;
}

template <typename t>
int altura_nodo(Agen<t>tree, typename Agen<t>::nodo n){
    if (tree.hijoIzqdo(n)==Agen<t>::NODO_NULO){
        return 0;
    }
    else
       return std::max((1+altura_nodo(tree,tree.hijoIzqdo(n))),1+altura_nodo(tree,tree.hermDrcho(tree.hijoIzqdo(n))))+1;
}

Agen<int>poda_rec(int cota,typename Agen<int>::nodo n,Agen<int>Arbol)
{
    if (n==Agen<int>::NODO_NULO)
    {
        return Arbol;//NO se ha encontrado el elemento
    }

    if (Arbol.elemento(n)==cota)
    {
        Agen<int>:: nodo nodo_temp;
        nodo_temp=n;
        while (nodo_temp!=Agen<int>::NODO_NULO)//Recorremos el arbol a partir del nodo con el elemento x
        {
            if ((Arbol.hijoIzqdo(nodo_temp)==Agen<int>::NODO_NULO)&&(Arbol.hermDrcho(Arbol.hijoIzqdo(nodo_temp))==Agen<int>::NODO_NULO)){
                Arbol.eliminarHijoIzqdo(nodo_temp);
                Arbol.eliminarHermDrcho(Arbol.hijoIzqdo(nodo_temp));
            }
            nodo_temp=Arbol.hermDrcho(nodo_temp);
        }
    }
    return  poda_rec(cota,Arbol.hijoIzqdo(n),Arbol);
}

Agen<int> poda(int cota,Agen<int>Arbol)
{
    return poda_rec(cota,Arbol.raiz(),Arbol);
}

#endif //EDNL_PRACTICA3_H

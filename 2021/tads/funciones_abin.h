//
// Created by anton on 09/03/2021.
//

#ifndef EDNL_FUNCIONES_ABIN_H
#define EDNL_FUNCIONES_ABIN_H
#include "arbolbinenla.h"
using namespace std;


template <typename t>
void preorden(Abin<t>& a,typename Abin<t>::nodo n){
    if(n!=Abin<t>::NODO_NULO){
        cout<<a.elemento(n)<<endl;//Se procesa antes de recorrer
        preorden(a,a.hijoIzqdoB(n));
        preorden(a,a.hijoDrchoB(n));
    }
}

template <typename t>
void inorden_abin(Abin<t>& a,typename Abin<t>::nodo  n){
    if (n!=Abin<t>::NODO_NULO){
        inorden_abin(a,a.hijoIzqdoB(n));
        cout<<a.elemento(n)<<endl;
        inorden_abin(a,a.hijoDrchoB(n));
    }
}

template <typename t>
void postorden_abin(Abin<t>& a, typename Abin<t>::nodo n){
    if (n!=Abin<t>::NODO_NULO){
        postorden_abin(a,a.hijoIzqdoB(n));
        postorden_abin(a,a.hijoDrchoB(n));
        cout<<a.elemento(n)<<endl;
    }
}


#endif //EDNL_FUNCIONES_ABIN_H

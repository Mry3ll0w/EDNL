#include <iostream>
#include <cassert>
#include "arbolbinenla.h"
#include "crea_arbol_bin.hpp"

int main (){

    Abin<int> a;

    a.insertarRaizB(1);
    a.insertarHijoDrchoB(a.raizB(),3);
    a.insertarHijoIzqdoB(a.raizB(),2);
    a.insertarHijoDrchoB(a.hijoDrchoB(a.raizB()),4);

   
    return 0;
}


/* ------------------------------- EJERCICIO 1 ------------------------------ */
/*
Calcular el numero de nodos de un arbol
*/
template <class t>
int cuenta_nodos(const Abin<t>&a,const typename Abin<t>::nodo n){

    if(n == Abin<t>::nodo_nulo ){
        return 0;
    }
return cuenta_nodos(a,a.hijoDrchoB(n))+1;
return cuenta_nodos(a,a.hijoIzqdoB(n))+1;
}
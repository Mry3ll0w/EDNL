#include <iostream>
#include <cassert>
#include "arbolbinenla.h"
#include <algorithm>

template <class t>
int cuenta_nodos(const Abin<t>&a,const typename Abin<t>::nodo n);

template <class t>
int altura_nodo(const Abin<t>&a, typename Abin<t>::nodo n);

template <class t>
int altura_arbol(const Abin<t>& a);

template <class t>
size_t desequilibrio(typename Abin<t>::nodo n, Abin<t> &Arbol);

int main (){

    Abin<int> a;

    a.insertarRaizB(1);
    a.insertarHijoDrchoB(a.raizB(),3);
    a.insertarHijoIzqdoB(a.raizB(),2);
    a.insertarHijoDrchoB(a.hijoDrchoB(a.raizB()),4);

    std::cout << "Altura arbol==> "<<desequilibrio(a.raizB(),a)<<std::endl;
   
    return 0;
}


/* ------------------------------- EJERCICIO 1 ------------------------------ */
/*
*Calcular el numero de nodos de un arbol
*/
template <class t>
int cuenta_nodos(const Abin<t>&a,typename Abin<t>::nodo n){

    if(n == a.NODO_NULO ){
        return 0;
    }

return cuenta_nodos(a,a.hijoDrchoB(n)) + cuenta_nodos(a,a.hijoIzqdoB(n)) + 1;

}

/* -------------------------------- EJERCIO 2 ------------------------------- */
//Cuenta la altura de un nodo, esta se calcula como el maximo de la altura de los hijos del nodo
template <class t>
int altura_nodo(const Abin<t>&a, typename Abin<t>::nodo n){

    if(n == a.NODO_NULO ){
        return -1;
    }

    return 1 + std::max(altura_nodo(a,a.hijoDrchoB(n)),altura_nodo(a,a.hijoIzqdoB(n))); 

}

//Calcula la altura de un nodo
template <class t>
int altura_arbol(const Abin<t>& a){
    return altura_nodo(a,a.raizB());
}

/* ------------------------------- EJERCICIO 3 ------------------------------ */
//Cuenta la profundiad de un nodo, numero de veces que puede tener pader
template<class t>
int profundidad_nodo(const Abin<t>&a, typename Abin<t>::nodo n){

    if(n == a.raizB())
        return 0;

    return profundidad_nodo(a,a.padreB(n));
}

/* ------------------------------- EJERCICIO 4 ------------------------------ */
/*
*Calcula la profundidad de un arbol, profundidad maxima
*/
template <class t>
int profundidad_arbol(Abin<t>&a){

    return altura_arbol(a)-1;

}

/* ------------------------------- EJERCICIO 5 ------------------------------ */
//Hecho previamente con enlazados

/* -------------------------------------------------------------------------- */
/*                                 EJERCICIO 6                                */
/* -------------------------------------------------------------------------- */

//Implemente un algoritmo que calcule el grado de desequilibrio de un arbol, la diferencia
//entre las alturas de los subarboles
template <typename t>
size_t difAltura(typename Abin<t>::nodo n, Abin<t>& a){
    return std::abs(altura_nodo(a,a.hijoIzqdoB(n))-altura_nodo(a,a.hijoDrchoB(n)));
}//Obtenemos las alturas

template <class t>
size_t desequilibrio(typename Abin<t>::nodo n, Abin<t> &Arbol)
{
    if (n == Abin<t>::NODO_NULO)
    {
        return 0;
    }
    return fmax(difAltura(n, Arbol), fmax(desequilibrio(Arbol.hijoDrchoB(n), Arbol), desequilibrio(Arbol.hijoIzqdoB(n), Arbol)));
    //Grado maximo del nodo n y sus dos hijos, siendo el desequilibrio el maximo de los mismos
}
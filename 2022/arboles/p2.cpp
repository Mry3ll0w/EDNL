#include <iostream>
#include "arbolbinenla.h"

//Sobrecarga para imprimir arboles
template <class t>
void imprime_arbol(const Abin<t>&A, typename Abin<t>::nodo n){

    if (n != Abin<t>::NODO_NULO)
    {
        std::cout << A.elemento(n)<<", ";
        imprime_arbol(A,A.hijoIzqdoB(n));
        imprime_arbol(A,A.hijoDrchoB(n));
    }
}


/* -------------------------------------------------------------------------- */
/*                                  CABECERAS                                 */
/* -------------------------------------------------------------------------- */
template <class t>
bool arboles_similares(const Abin<t>&A, const Abin<t>&B );

template <class t>
Abin<t> reflejo_arbol(Abin<t>&A,Abin<t>&B);

/* ---------------------------- IMPLEMENTACIONES ---------------------------- */

int main(){
    
    Abin<int> a,b;
    a.insertarRaizB(1);
    a.insertarHijoDrchoB(a.raizB(),3);
    a.insertarHijoIzqdoB(a.raizB(),2);
    a.insertarHijoDrchoB(a.hijoDrchoB(a.raizB()),4);


    reflejo_arbol(a,b);
    imprime_arbol(b,b.raizB());
    std::cout<<"-----------------------------------------------------------"<<std::endl;
    imprime_arbol(a,a.raizB());

    return 0;
}

/* -------------------------------------------------------------------------- */
/*                                 EJERCICIO 1                                */
/* -------------------------------------------------------------------------- */
/*
*  Dos árboles binarios son similares cuando tienen idéntica estructura de ramificación,
*  es decir, ambos son vacíos, o en caso contrario, tienen subárboles izquierdo y derecho
*  similares. Implementa un subprograma que determine si dos árboles binarios son similares.
*  RECORRIDO EN PREORDEN, nos interesa procesar la raiz en primer lugar.
*/

template <class t>
bool arboles_similares_rec(typename Abin<t>::nodo na, typename Abin<t>::nodo nb, const Abin<t>& A, const Abin<t>& B){
    
    //Caso general 
    if (na == Abin<t>::NODO_NULO && nb == Abin<t>::NODO_NULO)
        return true;
    //Procesamiento de la respuesta
    if(
        (na == Abin<t>::NODO_NULO && nb != Abin<t>::NODO_NULO)
        ||
        (nb == Abin<t>::NODO_NULO && na != Abin<t>::NODO_NULO)
    )
        return false;

    return arboles_similares_rec(A.hijoIzqdoB(na),B.hijoIzqdoB(nb),A,B)&&arboles_similares_rec(A.hijoDrchoB(na),B.hijoDrchoB(nb),A,B);

}

template <class t>
bool arboles_similares(const Abin<t>&A, const Abin<t>&B ){

    return arboles_similares_rec(A.raizB(),B.raizB(),A,B);
    
}

/* -------------------------------------------------------------------------- */
/*                                 EJERCICIO 2                                */
/* -------------------------------------------------------------------------- */
/*
* Para un árbol binario B, podemos construir el árbol binario reflejado BR
* cambiando los subárboles izquierdo y derecho en cada nodo. 
* Implementa un subprograma que devuelva el árbol binario reflejado de uno dado.
*/

template <class t>
void reflejo_arbol_rec(typename Abin<t>::nodo na, typename Abin<t>::nodo nb, Abin<t>&A, Abin<t>&B ){

    if (na != Abin<t>::NODO_NULO && nb != Abin<t>::NODO_NULO)
    {
        //std::cout<< B.elemento(nb) << std::endl;
        B.elemento(nb) = A.elemento(na);
        //std::cout<< B.elemento(nb) << std::endl;

        reflejo_arbol_rec(A.hijoIzqdoB(na),B.hijoDrchoB(nb),A,B);
        reflejo_arbol_rec(A.hijoDrchoB(na),B.hijoIzqdoB(nb),A,B);
    }
    
}

template <class t>
Abin<t> reflejo_arbol(Abin<t>&A,Abin<t>&B){
    
    //Abin<t> B(A);
    
    reflejo_arbol_rec(A.raizB(),B.raizB(),A,B);
    
    return B;

}



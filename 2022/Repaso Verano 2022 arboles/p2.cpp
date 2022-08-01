#include <iostream>
#include "abin_enla.h"



int main(){
    return 0;
}

/*
* Dos arboles son similares si ambos tienen similar estructura/ramificación.
*/

template<class t>
bool iguales_rec(Abin<t>& A, Abin<t>& B, typename Abin<t>::nodo na, typename Abin<t>::nodo nb){
    typedef Abin<t>::NODO_NULO NODO_NULO;

    if( na == Abin<t>::NODO_NULO || nb == Abin<t>::NODO_NULO){
        return true;
    }

    if(
        A.hijoDrchoB(na) != Abin<t>::NODO_NULO && B.hijoDrchoB(nb) != Abin<t>::NODO_NULO
        ||
        A.hijoDrchoB(na) == Abin<t>::NODO_NULO && B.hijoDrchoB(nb) == Abin<t>::NODO_NULO
        ||
        A.hijoIzqdoB(na) != Abin<t>::NODO_NULO && B.hijoIzqdoB(nb) != Abin<t>::NODO_NULO
        ||
        A.hijoIzqdoB(na) == Abin<t>::NODO_NULO && B.hijoIzqdoB(nb) == Abin<t>::NODO_NULO
        ||
        //Casos de cada hijo (izq y der )
        (
            A.hijoDrchoB(na) == NODO_NULO && A.hijoIzqdoB(na) != NODO_NULO && 
            B.hijoDrchoB(nb) == NODO_NULO && B.hijoIzqdoB(nb) != NODO_NULO
        )
        ||
        (
            A.hijoDrchoB(na) != NODO_NULO && A.hijoIzqdoB(na) == NODO_NULO && 
            B.hijoDrchoB(nb) != NODO_NULO && B.hijoIzqdoB(nb) == NODO_NULO
        )
    )
        return true;
    else
        return false;
    
    return iguales_rec(A,B, A.hijoIzqdoB(na), B.hijoIzqdoB(nb) && iguales_rec(A,B,A.hijoDrchoB(na), B.hijoDrchoB(nb));

}



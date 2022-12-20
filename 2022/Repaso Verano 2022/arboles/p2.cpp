#include <iostream>
#include "abin_enla.h"
#include <string>

using namespace std;

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
        A.hijoDrcho(na) != Abin<t>::NODO_NULO && B.hijoDrcho(nb) != Abin<t>::NODO_NULO
        ||
        A.hijoDrcho(na) == Abin<t>::NODO_NULO && B.hijoDrcho(nb) == Abin<t>::NODO_NULO
        ||
        A.hijoIzqdo(na) != Abin<t>::NODO_NULO && B.hijoIzqdo(nb) != Abin<t>::NODO_NULO
        ||
        A.hijoIzqdo(na) == Abin<t>::NODO_NULO && B.hijoIzqdo(nb) == Abin<t>::NODO_NULO
        ||
        //Casos de cada hijo (izq y der )
        (
            A.hijoDrcho(na) == NODO_NULO && A.hijoIzqdo(na) != NODO_NULO && 
            B.hijoDrcho(nb) == NODO_NULO && B.hijoIzqdo(nb) != NODO_NULO
        )
        ||
        (
            A.hijoDrcho(na) != NODO_NULO && A.hijoIzqdo(na) == NODO_NULO && 
            B.hijoDrcho(nb) != NODO_NULO && B.hijoIzqdo(nb) == NODO_NULO
        )
    )
        return true;
    else
        return false;
    
    return iguales_rec(A,B, A.hijoIzqdo(na), B.hijoIzqdo(nb) && iguales_rec(A,B,A.hijoDrcho(na), B.hijoDrcho(nb));

}

template <class T>
bool similares(Abin<T> A, Abin<T> B){
    return iguales_rec(A,B,A.raiz(), B.raiz());
}

//Ejercicio 2 => Crear arbol reflejado

//Recibe inicialmente el arbol A (origen), referencia B(destino) ambos reciben su raiz na y nb
template <class T>
void reflejo_rec(Abin<T> A, Abin<T>& B, typename Abin<T>::nodo na, typename Abin<T>::nodo nb){
    
    typedef Abin<T>::NODO_NULO NODO_NULO;

    if(na != NODO_NULO){

        //Copiamos nodo izquierdo
        if(A.hijoIzqdo(na) != NODO_NULO){ 
            B.insertarhijoDrcho(A.elemento(A.hijoIzqdo(na)), nb);
            reflejo_rec(A,B, A.hijoIzqdo(na), B.hijoIzqdo(nb));
        }

        if(A.hijoDrcho(na) != NODO_NULO){
            B.insertarhijoIzqdo(A.elemeto(A.hijoDrcho(na)), nb);
            reflejo_rec(A,B,A.hijoDrcho(na), B.hijoIzqdo(nb));
        } 
    }

}

template <class T>
Abin<T> reflejo_arbol(const Abin<T>& A){

    Abin<T> B;
    if(!A.arbolVacio()){

        B.insertarraiz(A.elemento(A.raiz()));
        reflejo_rec(A,B,A.raiz(), B.raiz());
    
    }
    
    return B;
}

//Ejercicio 3 => PostFijo

float post_fijo_rec(typename Abin<string>::nodo n, const Abin<string> &A){
    
    if(A.hijoDrcho(n) != Abin<std::string>::NODO_NULO && A.hijoIzqdo(n)!=Abin<std::string>::NODO_NULO){
        
        if (A.elemento(n) == "+")
        {
            return post_fijo_rec(A.hijoDrcho(n), A) + post_fijo_rec(A.hijoIzqdo(n), A);
        }
        else if (A.elemento(n) == "-"){
            return post_fijo_rec(A.hijoIzqdo(n), A) - post_fijo_rec(A.hijoDrcho(n), A);
        }
        else if (A.elemento(n) == "*"){
            return post_fijo_rec(A.hijoIzqdo(n), A) * post_fijo_rec(A.hijoDrcho(n), A);
        }
        else if (A.elemento(n) == "/"){
            return post_fijo_rec(A.hijoIzqdo(n), A) / post_fijo_rec(A.hijoDrcho(n), A);
        }
        else {
            return stof(A.elemento(n));
        }
        

    }
    else {
        return 0;
    }

}

float postfijo(Abin<string> A) {
    return post_fijo_rec(A.raiz(),A);
}
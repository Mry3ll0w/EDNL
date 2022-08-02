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

template <class T>
bool similares(Abin<T> A, Abin<T> B){
    return iguales_rec(A,B,A.raizB(), B.raizB());
}

//Ejercicio 2 => Crear arbol reflejado

//Recibe inicialmente el arbol A (origen), referencia B(destino) ambos reciben su raiz na y nb
template <class T>
void reflejo_rec(Abin<T> A, Abin<T>& B, typename Abin<T>::nodo na, typename Abin<T>::nodo nb){
    
    typedef Abin<T>::NODO_NULO NODO_NULO;

    if(na != NODO_NULO){

        //Copiamos nodo izquierdo
        if(A.hijoIzqdoB(na) != NODO_NULO){ 
            B.insertarHijoDrchoB(A.elemento(A.hijoIzqdoB(na)), nb);
            reflejo_rec(A,B, A.hijoIzqdoB(na), B.hijoIzqdoB(nb));
        }

        if(A.hijoDrchoB(na) != NODO_NULO){
            B.insertarHijoIzqdoB(A.elemeto(A.hijoDrchoB(na)), nb);
            reflejo_rec(A,B,A.hijoDrchoB(na), B.hijoIzqdoB(nb));
        } 
    }

}

template <class T>
Abin<T> reflejo_arbol(const Abin<T>& A){

    Abin<T> B;
    if(!A.arbolVacioB()){

        B.insertarRaizB(A.elemento(A.raizB()));
        reflejo_rec(A,B,A.raizB(), B.raizB());
    
    }
    
    return B;
}

//Ejercicio 3 => PostFijo

float post_fijo_rec(typename Abin<string>::nodo n, const Abin<string> &A){
    
    if(A.hijoDrchoB(n) != Abin<std::string>::NODO_NULO && A.hijoIzqdoB(n)!=Abin<std::string>::NODO_NULO){
        
        if (A.elemento(n) == "+")
        {
            return post_fijo_rec(A.hijoDrchoB(n), A) + post_fijo_rec(A.hijoIzqdoB(n), A);
        }
        else if (A.elemento(n) == "-"){
            return post_fijo_rec(A.hijoIzqdoB(n), A) - post_fijo_rec(A.hijoDrchoB(n), A);
        }
        else if (A.elemento(n) == "*"){
            return post_fijo_rec(A.hijoIzqdoB(n), A) * post_fijo_rec(A.hijoDrchoB(n), A);
        }
        else if (A.elemento(n) == "/"){
            return post_fijo_rec(A.hijoIzqdoB(n), A) / post_fijo_rec(A.hijoDrchoB(n), A);
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
    return post_fijo_rec(A.raizB(),A);
}
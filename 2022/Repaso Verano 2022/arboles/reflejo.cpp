#include <iostream>
#include "abin_enla.h"

using namespace std;//Avoid using std:: ....

template <class T>
int reflejado(const Abin<T> & A);

int main(){
    
return 0;
}

/*
Dado un arbol generico de tipo t calcular el numero de nodos que siendo hermanos entre si, 
son reflejados.
*/
template <class T>
int reflejado_rec(const Abin<T>& A, typename Abin<T>::nodo ni, typename Abin<T>::nodo nd){
    
    if(
        A.hijoIzqdo(na) == Abin<T>::NODO_NULO
        && 
        A.hijoDrcho(na) == Abin<T>::NODO_NULO
    ){
        return -2;
    }
    //Caso General
    if(
        A.elemento(A.hijoDrcho(ni))== A.elemento(A.hijoIzqdo(nd))
        ||
        A.elemento(A.hijoIzqdo(ni)) == A.elemento(A.hijoDrcho(nd))
    ){
        return 2 + reflejado_rec(A, A.hijoDrcho(ni),A.hijoIzqdo(nd)) +
            reflejado_rec(A, A.hijoIzqdo(ni), A.hijoDrcho(nd));
    }
    else{
        //No se cumple el reflejo, llamamos al hundimiento en el árbol
        return 0 + reflejado_rec(A, A.hijoDrcho(ni),A.hijoIzqdo(nd)) +
            reflejado_rec(A, A.hijoIzqdo(ni), A.hijoDrcho(nd));
    }    

}


template <class T>
int reflejado(const Abin<T> & A){

    //Inicialmente le pasamos al nodo izq y nodo der, para tratar los 
    //subarboles de forma independiente
    if(
        A.hijoDrcho(A.raiz()) != Abin<T>::NODO_NULO 
        &&
        A.hijoDrcho(A.raiz()) != Abin<T>::NODO_NULO
        &&
        !A.arbolVacio()
    ){
        return reflejado_rec(A, A.raiz(), A.raiz());
    }
    else
        return 0;
    

}
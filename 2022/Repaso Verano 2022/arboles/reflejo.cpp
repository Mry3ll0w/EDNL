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
        A.hijoIzqdoB(na) == Abin<T>::NODO_NULO
        && 
        A.hijoDrchoB(na) == Abin<T>::NODO_NULO
    ){
        return -2;
    }
    //Caso General
    if(
        A.elemento(A.hijoDrchoB(ni))== A.elemento(A.hijoIzqdoB(nd))
        ||
        A.elemento(A.hijoIzqdoB(ni)) == A.elemento(A.hijoDrchoB(nd))
    ){
        return 2 + reflejado_rec(A, A.hijoDrchoB(ni),A.hijoIzqdoB(nd)) +
            reflejado_rec(A, A.hijoIzqdoB(ni), A.hijoDrchoB(nd));
    }
    else{
        //No se cumple el reflejo, llamamos al hundimiento en el árbol
        return 0 + reflejado_rec(A, A.hijoDrchoB(ni),A.hijoIzqdoB(nd)) +
            reflejado_rec(A, A.hijoIzqdoB(ni), A.hijoDrchoB(nd));
    }    

}


template <class T>
int reflejado(const Abin<T> & A){

    //Inicialmente le pasamos al nodo izq y nodo der, para tratar los 
    //subarboles de forma independiente
    if(
        A.hijoDrchoB(A.raizB()) != Abin<T>::NODO_NULO 
        &&
        A.hijoDrchoB(A.raizB()) != Abin<T>::NODO_NULO
        &&
        !A.arbolVacioB()
    ){
        return reflejado_rec(A, A.raizB(), A.raizB());
    }
    else
        return 0;
    

}
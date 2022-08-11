#include <iostream>
#include "abin_enla.h"
#include "Agen.h"

using namespace std;//Avoid using std:: ....


template <class T>
bool ternario_rec(typename Agen<T>::nodo n, Agen<T>A){
    if(n != Agen<T>::NODO_NULO){
        
        auto h_izq = A.hijoIzqdo(n);
        int cont = 0;

        //Contamos los nodos
        while (h_izq != Agen<T>::NODO_NULO){
            cont ++ ;
            h_izq = A.hermDrcho(h_izq);
        }

        if(cont != 3)
            return false;

        n = A.hijoIzqdo(n);
    }
    return ternario_rec(A.hijoIzqdo(n), A);
}


int main(){
    Agen<int> A;
    A.insertarRaiz(1);
    A.insertarHijoIzqdo(A.raiz(), 2);
    A.insertarHermDrcho(A.hijoIzqdo(A.raiz()),3);
    A.insertarHermDrcho(A.hijoIzqdo(A.raiz()),4);
    
    
return 0;
}



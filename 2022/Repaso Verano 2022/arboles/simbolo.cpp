#include <iostream>
#include <string>
#include "abin_enla.h"
using namespace std;
bool valor_verdad(const Abin<string>& A);

int main(){
    return 0;
}

//El examen consiste en utilizar un arbol binario para el calculo de valores de verdad
//Suponemos que los elementos que puede recibir : 
// AND OR ¬(NOT) True o False
bool valor_verdad_rec(const Abin<string>& A, typename Abin<string>::nodo n){

    if(
        A.hijoIzqdo(n) != Abin<string>::NODO_NULO
    )
    {

        if (A.elemento(n) == "¬"){
            return !A.hijoIzqdo(n);
        }
        else if (A.elemento(n) == "AND"){
            return valor_verdad_rec(A, A.hijoIzqdo(n)) && valor_verdad_rec(A, A.hijoDrcho(n));
        }
        else if(A.elemento(n) == "OR"){
            return 
                valor_verdad_rec(A, A.hijoDrcho(n)) || valor_verdad_rec(A, A.hijoIzqdo(n));
        }
        else if(A.elemento(n) == "True"){
            return true;
        }
        else if(A.elemento(n) == "False"){
            return false;
        }

    }
    else {
        return false;
    }

}

bool valor_verdad(const Abin<string>& A){
    return valor_verdad_rec(A, A.raiz());
}
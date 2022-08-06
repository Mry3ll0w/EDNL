#include <iostream>
#include "Agen.h"
using namespace std;//Avoid using std:: ....

//Dado un arbol general que nos calcule su grado

template <class t>
int cuenta_hermanos_rec(typename Agen<t>::nodo n, Agen<t>&A)
{

    if (n != Agen<t>::NODO_NULO)
    {
        return 1+ cuenta_hermanos_rec(A.hermDrcho(n),A);
    }
    else
        return 0;

}

//El grado del árbol se define como el numero maximo de hijos que tiene un nodo del arbol
template<class t>
int grado_arbol_rec(typename Agen<t>::nodo n, Agen<t>&A)
{
    //Comenzamos por el hijo izquierdo de la raiz
    unsigned grado = cuenta_hermanos_rec(n,A);
    
    if (n != Agen<t>::NODO_NULO)
    {
        
        while(n != Agen<t>::NODO_NULO){

            //Iteramos los hermanos derechos
            auto n_der = A.hermDrcho(n);
            while(n_der != Agen<t>::NODO_NULO){
                auto g_act = cuenta_hermanos_rec(A.hijoIzqdo(n_der), A);

                if(grado < g_act)
                    grado = g_act;

                n_der = A.hermDrcho(n_der);
            }

            n = A.hijoIzqdo(n);
        }

    }
    
return grado;    
}


int main(){
    Agen<int> A;
    A.insertarRaiz(1);
    A.insertarHijoIzqdo(A.raiz(), 2);
    A.insertarHermDrcho(A.hijoIzqdo(A.raiz()), 3);
    A.insertarHijoIzqdo(A.hermDrcho(A.hijoIzqdo(A.raiz())), 4);
    
    for(size_t i = 0; i < 4 ; i++ ){
        A.insertarHermDrcho(A.hijoIzqdo(A.hermDrcho(A.hijoIzqdo(A.raiz()))), 5 + i);
    }

    cout<< grado_arbol_rec(A.raiz(), A)<<endl;
return 0;
}
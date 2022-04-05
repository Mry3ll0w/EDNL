#include <iostream>
#include "agenEnlazado.h"
using namespace std;//Avoid using std:: ....

/* -------------------------------------------------------------------------- */
/*                            CABECERAS DE FUNCION                            */
/* -------------------------------------------------------------------------- */
template<class t>
int grado_arbol(Agen<t>&A);


int main(){
    
    Agen<int>A;
    A.insertarRaiz(1);
    A.insertarHijoIzqdo(A.raiz(),2);
    A.insertarHermDrcho(A.hijoIzqdo(A.raiz()),3);
    auto n=A.hermDrcho(A.hijoIzqdo(A.raiz()));
    A.insertarHijoIzqdo(A.hijoIzqdo(A.raiz()),39);
    auto n2=A.hijoIzqdo(A.hijoIzqdo(A.raiz()));

    //insertamos 4 hermanos 
    for(int i=4;i<7;++i)
        A.insertarHermDrcho(n,i);n=A.hermDrcho(n);

    for(int i=9;i<15;++i)
        A.insertarHermDrcho(n2,i);n2=A.hermDrcho(n2);

    std::cout<<grado_arbol(A)<<std::endl;

return 0;
}

/* ------------------------------- EJERCICIO 1 ------------------------------ */
/**
 * Calcular el grado maximo de un arbol general
 * 
 */ 

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
    unsigned grado = 0;
    
    if (n != Agen<t>::NODO_NULO)
    {
        
        while (n != Agen<t>::NODO_NULO)
        {
            int grado_actual = cuenta_hermanos_rec(n,A);
            if (grado < grado_actual)
            {
                grado = grado_actual;
            }
            n = A.hijoIzqdo(n);
        }

    }
    
return grado;    
}

template<class t>
int grado_arbol(Agen<t>&A){
    return grado_arbol_rec(A.raiz(),A);
}

/* ------------------------------- EJERCICIO 2 ------------------------------ */
//Calcular la profundidad de un nodo en el arbol, epico
template<class t>
unsigned profundidad_nodo(typename Agen<t>::nodo n,Agen<t>&A)
{
    if(n != Agen<t>::NODO_NULO)
        return 1 + profundidad_rec(A.padre(n),A);
}

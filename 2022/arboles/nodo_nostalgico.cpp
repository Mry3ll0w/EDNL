#include <iostream>
#include "arbolbinenla.h"
using namespace std;//Avoid using std:: ....




template<class t>
int nodos_nostalgicos(const Abin<t>&A);

int main(){
    
return 0;
}

//Un nodo nostalgico es aquel que tiene mas pasado que futuro, es decir el número de descendientes es menor que 
//el número de antecedentes.

//Función para contar el numero de nodos del subarbol
template<class t>
int num_nodos(typename Abin<t>::nodo n, const Abin<t>&A)
{
    if(n != Abin<t>::NODO_NULO){
        return 1 + num_nodos(A.hijoIzqdo(n),A) + num_nodos(A.hijoDrcho(n),A);
    }

}

//Obtenemos el numero de nodos que le preceden, numero de antecesores
template<class t>
int antecesores (typename Abin<t>::nodo n , const Abin<t>&A)
{
    if (n == Abin<t>::NODO_NULO){
        return -1 ;
    }
    
    return 1 + antecesores(A.padre(n),A);
}


template <class t>
int nostalgicos_rec(typename Abin<t>::nodo n , const Abin<t>&A)
{
    if (n == Abin<t>::NODO_NULO)//Caso base nodo nulo
    {
        return 0; 

    }
    else//Caso general
    {
        int pasado = antecesores(n,A);
        int futuro = num_nodos(n,A) -1 ;//ya que debemos eliminar la raiz, para solo tener en cuenta los descendientes

        if ( pasado > futuro )
        {
            return 1 + nostalgicos_rec(A.hijoIzqdo(n),A) + nostalgicos_rec(A.hijoDrcho(n),A);
        }
        else
        {
            //El 0 es redundante pero deja más claro que no aumentamos el número de nodos nostalgicos
            return 0 + nostalgicos_rec(A.hijoIzqdo(n),A) + nostalgicos_rec(A.hijoDrcho(n),A);
        }
    }
    
    
    
}

//Calcula el numero de nodos nostalgicos que existen en un árbol binario dado
template<class t>
int nodos_nostalgicos(const Abin<t>&A)
{

    return nostalgicos_rec(A.raiz(),A);

}
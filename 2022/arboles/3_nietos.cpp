#include <iostream>
#include "arbolbinenla.h"
using namespace std;//Avoid using std:: ....

template<class t>
typename Abin<t>::NODO_NULO NULO;


int main(){
    
return 0;
}

//Función para contar hijos de un árbol
template <class t>
int cuenta_nietos(typename Abin<t>::nodo n, const Abin<t>&A){
    if(n != Abin<t>::NODO_NULO)
        return 1 + cuenta_nietos(A.hijoIzqdoB(n),A)+cuenta_nietos(A.hijoDrchoB(n),A);
    else
        return 0;
}

//Función para contar hijos del árbol
template<class t>
int cuenta_hijos(typename Abin<t>::nodo n, const Abin<t>&A)
{
    return cuenta_nietos(n,A)-1;
}



//simplemente recorremos el arbol que nos den, para asi comprobar cualquier nodo dado
template<class t>
int cuenta_3_nietos_rec(typename Abin<t>::nodo n,const Abin<t>&A)
{

    if ( n == NULO )//Base 
    {
    
        return 0;

    }
    else//general
    {

        if (cuenta_hijos(n,A)==3)
        {
            return 1 + cuenta_3_nietos(A.hijoIzqdoB(n),A) + cuenta_3_nietos(A.hijoDrchoB(n),A);
        }
        else
            return cuenta_3_nietos(A.hijoIzqdoB(n),A) + cuenta_3_nietos(A.hijoDrchoB(n),A);
        
    }
    

}


template <class t> 
int numero_3_nietos(const Abin<t>&A)
{
    return cuenta_3_nietos_rec(A.raizB(),A);
}
#include <iostream>
#include <cassert>
#include "arbolbinenla.h"
#include <algorithm>

template <class t>
int cuenta_nodos(const Abin<t>&a,const typename Abin<t>::nodo n);

template <class t>
int altura_nodo(const Abin<t>&a, typename Abin<t>::nodo n);

template <class t>
int altura_arbol(const Abin<t>& a);

template <class t>
unsigned int desequilibrio(typename Abin<t>::nodo n, Abin<t> &Arbol);

template<class t>
bool pseudocompleto(Abin<t>&a);

template <class t>
int profundidad_nodo_iterativa(typename Abin<t>::nodo n,const Abin<t>& a);

template <class t>
unsigned int desequilibrio_arbol(typename Abin<t>::nodo n, const Abin<t> &A);

int main (){

    Abin<int> a;
    a.insertarRaizB(1);
    a.insertarHijoDrchoB(a.raizB(),3);
    //a.insertarHijoIzqdoB(a.raizB(),2);
    a.insertarHijoDrchoB(a.hijoDrchoB(a.raizB()),4);
    std::cout << altura_arbol(a) << std::endl;
    std::cout<<"-----------------------------------------------------------"<<std::endl;
    std::cout << "Pseudo completo: "<< pseudocompleto(a)<<std::endl;
   
    return 0;
}


/* ------------------------------- EJERCICIO 1 ------------------------------ */
/*
*Calcular el número de nodos de un arbol
*/
template <class t>
int cuenta_nodos(const Abin<t>&a,typename Abin<t>::nodo n){

    if(n == Abin<t>::NODO_NULO ){
        return 0;
    }
    std::cout<<a.elemento(n)<<std::endl;

return 1 + cuenta_nodos(a,a.hijoDrchoB(n)) + cuenta_nodos(a,a.hijoIzqdoB(n));

}

template<class t>
int nodos_arbol(const Abin<t>& a){

    return cuenta_nodos(a,a.raizB());

}

/* -------------------------------- EJERCIO 2 ------------------------------- */
//Cuenta la altura de un nodo, esta se calcula como el maximo de la altura de los hijos del nodo
template <class t>
int altura_nodo(const Abin<t>&a, typename Abin<t>::nodo n){

    if ( n == Abin<t>::NODO_NULO ){
        
        return -1;//Por convenio

    }

    return 1 + std::max(altura_nodo(a,a.hijoDrchoB(n)),altura_nodo(a,a.hijoIzqdoB(n))); 

}

//Calcula la altura de un nodo
template <class t>
int altura_arbol(const Abin<t>& a){
    return altura_nodo(a,a.raizB());
}

/* ------------------------------- EJERCICIO 3 ------------------------------ */
/*
* Cuenta la profundidad de un nodo, numero de veces que puede tener pader
*/
template<class t>
int profundidad_nodo(const Abin<t>&a, typename Abin<t>::nodo n){

    if(n == a.raizB())
        return 0;

    return 1 + profundidad_nodo(a,a.padreB(n));
}

//PROFUNDIDAD IMPLEMENTACION ITERATIVA
template <class t>
int profundidad_nodo_iterativa(typename Abin<t>::nodo n,const Abin<t>& a){

    int profundidad = 0;

    while (n != a.raizB())
    {
        profundidad ++;
        n = a.padreB(n);    
    }
    
return profundidad;
}

/* ------------------------------- EJERCICIO 4 ------------------------------ */
/*
* Calcula la profundidad de un arbol, profundidad maxima, NO ESTA DEFINIDO ya que se usa altura como tal.
* Ya implementado.
*/

/* ------------------------------- EJERCICIO 5 ------------------------------ */
//Hecho previamente con enlazados

/* -------------------------------------------------------------------------- */
/*                                 EJERCICIO 6                                */
/* -------------------------------------------------------------------------- */

//Implemente un algoritmo que calcule el grado de desequilibrio de un arbol, la diferencia
//entre las alturas de los subarboles del mismo.

//Obtiene las diferencias de altura
template <typename t>
unsigned int difAltura(typename Abin<t>::nodo n, Abin<t>& A){
    
    return std::abs( altura_nodo(A,A.hijoIzqdoB(n)) - altura_nodo(A,A.hijoDrchoB(n) ) );

}//Obtenemos las alturas

template <class t>
unsigned int desequilibrio(typename Abin<t>::nodo n, Abin<t> &Arbol)
{
    if (n == Abin<t>::NODO_NULO)
    {
        return 0;// ya que al tener z
    }
    return fmax( difAltura (n, Arbol), fmax( desequilibrio (Arbol.hijoDrchoB(n), Arbol), 
                desequilibrio (Arbol.hijoIzqdoB(n), Arbol) ) );
    //Grado maximo del nodo n y sus dos hijos, siendo el desequilibrio el maximo de los mismos
}

template <class t>
unsigned int desequilibrio_arbol(const Abin<t> &A){

    return desequilibrio(A.raizB(),A);
    //NO es el desequilibrio del nodo raiz, si no de sus nodos, es decir no tiene pq coincidir con el
    //desequilibrio del nodo raiz.

}


/* -------------------------------------------------------------------------- */
/*                                 EJERCICIO 7                                */
/* -------------------------------------------------------------------------- */

template <class t>
bool pseudocompleto_rec(typename Abin<t>::nodo n, Abin<t> &A)
{
    if (1 == altura_nodo(n,A))//Si la altura llega a 1 estamos en el penultimo nivel
    {
        return A.hijoDrchoB(n) != Abin<t>::NODO_NULO && A.hijoIzqdoB(n) != Abin<t>::NODO_NULO;
    }
    else
    {
        if (altura_nodo(A.hijoIzqdoB(n),A) > altura_nodo(A.hijoDrchoB(n),A))
        {
            return pseudocompleto_rec(A.hijoIzqdoB(n),A);
        }
        else if(altura_nodo(A.hijoIzqdoB(n),A) < altura_nodo(A.hijoDrchoB(n),A))
        {
            return pseudocompleto_rec(A.hijoDrchoB(n),A);
        }   
        else{
            return pseudocompleto_rec(A.hijoIzqdoB(n),A) && pseudocompleto_rec(A.hijoDrchoB(n),A);
        }
        
    }
    
}

template<class t>
bool pseudocompleto(Abin<t>&A){
    if (A.arbolVacioB())
    {
        return true;
    }
    
    return pseudocompleto_rec(A.raizB(),A);
}
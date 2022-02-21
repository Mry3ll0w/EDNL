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
size_t desequilibrio(typename Abin<t>::nodo n, Abin<t> &Arbol);

template <class t>
bool pseudo_completo(Abin<t> &a, typename Abin<t>::nodo n);

int main (){

    Abin<int> a;

    a.insertarRaizB(1);
    a.insertarHijoDrchoB(a.raizB(),3);
    a.insertarHijoIzqdoB(a.raizB(),2);
    a.insertarHijoDrchoB(a.hijoDrchoB(a.raizB()),4);

    std::cout << "Pseudo completo: "<< pseudo_completo(a,a.raizB())<<std::endl;
   
    return 0;
}


/* ------------------------------- EJERCICIO 1 ------------------------------ */
/*
*Calcular el numero de nodos de un arbol
*/
template <class t>
int cuenta_nodos(const Abin<t>&a,typename Abin<t>::nodo n){

    if(n == a.NODO_NULO ){
        return 0;
    }

return cuenta_nodos(a,a.hijoDrchoB(n)) + cuenta_nodos(a,a.hijoIzqdoB(n)) + 1;

}

/* -------------------------------- EJERCIO 2 ------------------------------- */
//Cuenta la altura de un nodo, esta se calcula como el maximo de la altura de los hijos del nodo
template <class t>
int altura_nodo(const Abin<t>&a, typename Abin<t>::nodo n){

    if(n == a.NODO_NULO ){
        return -1;
    }

    return 1 + std::max(altura_nodo(a,a.hijoDrchoB(n)),altura_nodo(a,a.hijoIzqdoB(n))); 

}

//Calcula la altura de un nodo
template <class t>
int altura_arbol(const Abin<t>& a){
    return altura_nodo(a,a.raizB());
}

/* ------------------------------- EJERCICIO 3 ------------------------------ */
//Cuenta la profundiad de un nodo, numero de veces que puede tener pader
template<class t>
int profundidad_nodo(const Abin<t>&a, typename Abin<t>::nodo n){

    if(n == a.raizB())
        return 0;

    return profundidad_nodo(a,a.padreB(n));
}

/* ------------------------------- EJERCICIO 4 ------------------------------ */
/*
*Calcula la profundidad de un arbol, profundidad maxima
*/
template <class t>
int profundidad_arbol(Abin<t>&a){

    return altura_arbol(a)-1;

}

/* ------------------------------- EJERCICIO 5 ------------------------------ */
//Hecho previamente con enlazados

/* -------------------------------------------------------------------------- */
/*                                 EJERCICIO 6                                */
/* -------------------------------------------------------------------------- */

//Implemente un algoritmo que calcule el grado de desequilibrio de un arbol, la diferencia
//entre las alturas de los subarboles
template <typename t>
size_t difAltura(typename Abin<t>::nodo n, Abin<t>& a){
    return std::abs(altura_nodo(a,a.hijoIzqdoB(n))-altura_nodo(a,a.hijoDrchoB(n)));
}//Obtenemos las alturas

template <class t>
size_t desequilibrio(typename Abin<t>::nodo n, Abin<t> &Arbol)
{
    if (n == Abin<t>::NODO_NULO)
    {
        return 0;
    }
    return fmax(difAltura(n, Arbol), fmax(desequilibrio(Arbol.hijoDrchoB(n), Arbol), desequilibrio(Arbol.hijoIzqdoB(n), Arbol)));
    //Grado maximo del nodo n y sus dos hijos, siendo el desequilibrio el maximo de los mismos
}


/* -------------------------------------------------------------------------- */
/*                                 EJERCICIO 7                                */
/* -------------------------------------------------------------------------- */

//Operador auxiliar que comprueba el numero de hijos del nodo
template<class t>
bool comprueba_penultimo(Abin<t>& a,const size_t altura, typename Abin<t>::nodo n,size_t nivel){

    //Primero bajamos hasta el penultimo nivel
    if (nivel == altura -1)
    {
        if (
            a.hijoDrchoB(n)==Abin<t>::NODO_NULO && a.hijoIzqdoB(n)==Abin<t>::NODO_NULO
            ||
            a.hijoDrchoB(n)!=Abin<t>::NODO_NULO && a.hijoIzqdoB(n)!=Abin<t>::NODO_NULO
            )
        {
            return true;
        }
        else
            return false;
        
    }
    
    return comprueba_penultimo(a,altura,a.hijoDrchoB(n),nivel+1)||comprueba_penultimo(a,altura,a.hijoIzqdoB(n),nivel+1);
}

/*
* Calcular si un arbol es pseudocompleto, sera pseudocompleto cuando el mismo tenga dos hijos o ninguno.
* Procedimiento:
*   1) LLegar al penultimo nivel
*   2) Si no tiene hijos o existen al menos 2 hijos
*/
template <class t>
bool pseudo_completo(Abin<t> &a, typename Abin<t>::nodo n){
    
    //Inicializacion de variables
    bool pseudo ;
    size_t altura ;
    
    //Obtenemos la altura, ya que el penultimo nivel del arbol estara localizado en la altura - 1
    altura = altura_arbol(a);
    pseudo = true;

    if(altura < 1){//No sera un pseudo completo, ya que no existe un penultimo nivel
        pseudo = false;
    }

    //Llamamos a la funcion comprueba_penultimo
    pseudo = comprueba_penultimo(a,altura,a.raizB(),0);
    

return pseudo;
}
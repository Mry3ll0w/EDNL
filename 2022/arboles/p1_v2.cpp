#include <iostream>
#include <algorithm>
#include "arbolbinenla.h"
using namespace std;//Avoid using std:: ....

/* -------------------------------- CABECERAS ------------------------------- */
template <class t>
int altura_rec(typename Abin<t>::nodo n, Abin<t>&A);

template <class t>
unsigned int desequilibrio_arbol(Abin<t> &A);

template<class t>
bool pseudo_completo(Abin<t>&A);


int main(){
    Abin<int> a;
    a.insertarRaizB(1);
    a.insertarHijoDrchoB(a.raizB(),3);
    a.insertarHijoIzqdoB(a.raizB(),2);
    //a.insertarHijoDrchoB(a.hijoDrchoB(a.raizB()),4);
    std::cout<<"-----------------------------------------------------------"<<std::endl;
    std::cout << "Pseudo completo: "<< pseudo_completo(a)<<std::endl;
   
return 0;
}

//1 Numnodos no se hace le se
//2 Calcular la altura de un arbol, por definición la altura de un árbol será la rama más alta de
//entre todos sus hijos.
template <class t>
int altura_rec(typename Abin<t>::nodo n, Abin<t>&A)
{
    if (n == Abin<t>::NODO_NULO)
    {
        return -1; // Ya que el arbol nulo no tiene altura
    }
    
    return 1 + std::max(altura_rec(A.hijoIzqdoB(n),A),altura_rec(A.hijoDrchoB(n),A));
    //El uno sirve para incrementar la altura, se debe de hacer en su exterior para que se incremente con 
    //su llamada, de forma independiente al maximo.
}

template<class t>
unsigned int altura_arbol(Abin<t>&A){
    return altura_rec(A.raizB(),A);
}

//Ejercicio 3 La profundidad de un nodo dado, ya que por definición no existe la profundidad de un nodo
//para eso usamos la altura y ya .
template <class t>
int profundidad_rec(typename Abin<t>::nodo n, Abin<t>&A){
    if (n != Abin<t>::NODO_NULO)
        return 0;
    return 1 + profundidad_rec(A.padreB(n),A);
}

//Ejercicio 6 desequilibrio

//Obtiene las diferencias de altura
template <typename t>
unsigned int difAltura(typename Abin<t>::nodo n, Abin<t>& A){
    
    return std::abs( altura_rec(A.hijoIzqdoB(n),A) - altura_rec(A.hijoDrchoB(n),A ) );

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
unsigned int desequilibrio_arbol(Abin<t> &A){

    return desequilibrio(A.raizB(),A);
    //NO es el desequilibrio del nodo raiz, si no de sus nodos, es decir no tiene pq coincidir con el
    //desequilibrio del nodo raiz.

}

/* -------------------------------------------------------------------------- */
/*                                 EJERCICIO 7                                */
/* -------------------------------------------------------------------------- */
/*
* 1) Detectar que nodo esta en el penultimo nivel
*/


//Esta función determina que un nodo este en el último nivel
template<class t>
bool pseudo_completo_rec(typename Abin<t>::nodo n, Abin<t>&A, unsigned int nivel)
{
    
    if (altura_arbol(A) - 1 == nivel)
    {
        
        if(
            (A.hijoDrchoB(n)!= Abin<t>::NODO_NULO && A.hijoIzqdoB(n) != Abin<t>::NODO_NULO)
            ||
            (A.hijoDrchoB(n)== Abin<t>::NODO_NULO && A.hijoIzqdoB(n) == Abin<t>::NODO_NULO)
        )
        {
            return true;
        }
        else{
            return false;
        }
    }
    return pseudo_completo_rec(A.hijoDrchoB(n),A,nivel+1)&&pseudo_completo_rec(A.hijoIzqdoB(n),A,nivel+1);
}

template<class t>
bool pseudo_completo(Abin<t>&A){

    if (A.arbolVacioB())
    {
        return true;//ya que un arbol vacio es siempre pseudocompleto
    }
    else
        return pseudo_completo_rec(A.raizB(),A,0);
    

}
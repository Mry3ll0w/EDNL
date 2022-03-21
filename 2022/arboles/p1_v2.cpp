#include <iostream>
#include <algorithm>
#include "arbolbinenla.h"
using namespace std;//Avoid using std:: ....

/* -------------------------------- CABECERAS ------------------------------- */
template <class t>
int altura_rec(typename Abin<t>::nodo n, const Abin<t>&A);




int main(){
    Abin<int> a;
    a.insertarRaizB(1);
    a.insertarHijoDrchoB(a.raizB(),3);
    //a.insertarHijoIzqdoB(a.raizB(),2);
    a.insertarHijoDrchoB(a.hijoDrchoB(a.raizB()),4);
    std::cout<<altura_rec(a.raizB(),a)<< std::endl;
return 0;
}

//1 Numnodos no se hace le se
//2 Calcular la altura de un arbol, por definición la altura de un árbol será la rama más alta de
//entre todos sus hijos.
template <class t>
int altura_rec(typename Abin<t>::nodo n, const Abin<t>&A)
{
    if (n == Abin<t>::NODO_NULO)
    {
        return -1; // Ya que el arbol nulo no tiene altura
    }
    
    return 1 + std::max(altura_rec(A.hijoIzqdoB(n),A),altura_rec(A.hijoDrchoB(n),A));
    //El uno sirve para incrementar la altura, se debe de hacer en su exterior para que se incremente con 
    //su llamada, de forma independiente al maximo.
}

//Ejercicio 3 La profundidad de un nodo dado, ya que por definición no existe la profundidad de un nodo
//para eso usamos la altura y ya .
template <class t>
int profundidad_rec(typename Abin<t>::nodo n, const Abin<t>&A){
    if (n != Abin<t>::NODO_NULO)
        return 0;
    return 1 + profundidad_rec(A.padreB(n),A);
}

//Ejercicio 6 desequilibrio

template <class t>
int dif_altura (typename Abin<t>::nodo n, const Abin<t>&A){

    return std::abs(altura_rec(A.hijoIzqdoB(n),A)-altura_rec(A.hijoDrchoB(n),A));

}

template<class t>
int desequilibrio_rec(typename Abin<t>::nodo n, const Abin<t>&A){

    if (n != Abin<t>::NODO_NULO){

        return std::max(dif_altura(n,A),dif_altura(a.hijoIzqdoB(n),A),dif_altura(a.hijoDrchoB(n),A));
        //LA diferencia de alturas de EL MISMO y su subarboles.
    }

}
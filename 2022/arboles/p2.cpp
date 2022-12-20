#include <iostream>
#include <string>
#include <algorithm>
#include <vector>
#include <stdlib.h>
#include <cmath>
#include <cassert>
#include "arbolbinenla.h"
#include "abin_rel.hpp"

//Sobrecarga para imprimir arboles
template <class t>
void imprime_arbol(const Abin<t>&A, typename Abin<t>::nodo n){

    if (n != Abin<t>::NODO_NULO)
    {
        std::cout << A.elemento(n)<<", ";
        imprime_arbol(A,A.hijoIzqdo(n));
        imprime_arbol(A,A.hijoDrcho(n));
    }
}


/* -------------------------------------------------------------------------- */
/*                                  CABECERAS                                 */
/* -------------------------------------------------------------------------- */
template <class t>
bool arboles_similares(const Abin<t>&A, const Abin<t>&B );

template <class t>
Abin<t> reflejo_arbol(Abin<t>&A);

float post_fijo(Abin<std::string>&A);


/* ---------------------------- IMPLEMENTACIONES ---------------------------- */

int main(){
   
    Abin<char>a;
    
    a.insertarraiz('a');
    a.insertarhijoIzqdo(a.raiz(),'b');
    //a.insertarhijoDrcho(a.hijoDrcho(a.raiz()),4);

    imprime_arbol(a,a.raiz());
    std::cout<<std::endl<<"-----------------------------------------------------------"<<std::endl;
    Abin<char>b(reflejo_arbol(a));
    imprime_arbol(b,b.raiz());

    return 0;
}

/* -------------------------------------------------------------------------- */
/*                                 EJERCICIO 1                                */
/* -------------------------------------------------------------------------- */
/*
*  Dos árboles binarios son similares cuando tienen idéntica estructura de ramificación,
*  es decir, ambos son vacíos, o en caso contrario, tienen subárboles izquierdo y derecho
*  similares. Implementa un subprograma que determine si dos árboles binarios son similares.
*  RECORRIDO EN PREORDEN, nos interesa procesar la raiz en primer lugar.
*  Falla en caso de no tener los nodos ambos nulos , no se modifica la estructura
*/

template <class t>
bool arboles_similares_rec(typename Abin<t>::nodo na, typename Abin<t>::nodo nb, const Abin<t>& A, const Abin<t>& B){
    
    //Caso general 
    if (na == Abin<t>::NODO_NULO && nb == Abin<t>::NODO_NULO)
        return true;

    //Procesamiento del arbol
    else if(
        (na == Abin<t>::NODO_NULO && nb != Abin<t>::NODO_NULO)
        ||
        (nb == Abin<t>::NODO_NULO && na != Abin<t>::NODO_NULO)
    )
        return false;

    return 
        arboles_similares_rec(A.hijoIzqdo(na),B.hijoIzqdo(nb),A,B) 
        &&
        arboles_similares_rec(A.hijoDrcho(na),B.hijoDrcho(nb),A,B);

}

template <class t>
bool arboles_similares(const Abin<t>&A, const Abin<t>&B ){

    return arboles_similares_rec(A.raiz(),B.raiz(),A,B);
    
}

/* -------------------------------------------------------------------------- */
/*                                 EJERCICIO 2                                */
/* -------------------------------------------------------------------------- */
/*
* Para un árbol binario B, podemos construir el árbol binario reflejado BR
* cambiando los subárboles izquierdo y derecho en cada nodo. 
* Implementa un subprograma que devuelva el árbol binario reflejado de uno dado.
*/

template <class t>
void reflejo_arbol_rec(typename Abin<t>::nodo na, typename Abin<t>::nodo nb ,Abin<t>&A ,Abin<t>&B ){

    if (A.hijoIzqdo(na) != Abin<t>::NODO_NULO)//Insertamos los hijos izquierdos en los derechos
    {
        B.insertarhijoDrcho(nb,A.elemento(A.hijoIzqdo(na)));

        reflejo_arbol_rec(A.hijoIzqdo(na),B.hijoDrcho(nb),A,B);
    }
    
    if (A.hijoDrcho(na) != Abin<t>::NODO_NULO)
    {
        B.insertarhijoIzqdo(nb,A.elemento(A.hijoDrcho(na)));
        
        reflejo_arbol_rec(A.hijoDrcho(na),B.hijoIzqdo(nb),A,B);
    }
    
    
}

template <class t>
Abin<t> reflejo_arbol(Abin<t>&A){
    
    Abin<t> B;
    
    if (!A.arbolVacio()){

        B.insertarraiz(A.elemento(A.raiz()));
        reflejo_arbol_rec(A.raiz(),B.raiz(),A,B);
    
    }

    
    return B;

}

/* -------------------------------------------------------------------------- */
/*                                 EJERCICIO 3                                */
/* -------------------------------------------------------------------------- */

/*
* El TAD árbol binario puede albergar expresiones matemáticas mediante un árbol de 
* expresión. Dentro del árbol binario los nodos hojas contendrán los operandos, y el resto 
* de los nodos los operadores.
* a) Define el tipo de los elementos del árbol para que los nodos puedan almacenar 
* operadores y operandos.
* b) Implementa una función que tome un árbol binario de expresión (aritmética) y 
* devuelva el resultado de la misma. Por simplificar el problema se puede asumir que el 
* árbol representa una expresión correcta. Los operadores binarios posibles en la expresión 
* aritmética serán suma, resta, multiplicación y división.

* Plantear el ejercicio mediante el uso de una estructura 

*/

float procesa_arbol(typename Abin<std::string>::nodo n, Abin<std::string>&A){

    //Debemos controlar que en todo momento se procesen operaciones entre arboles equilibrados
    //Si no la operacion entre los mismos no será correcta, ya que se opera numero con nodo nulo
    //No tiene pq tener la doble comprobación, solo necesitamos el hijo izquierdo, ya que la expresion
    //tiene que tener o ambos hijos vacios o ambos no vacios, en otro caso será incorrecta la expresión
    if (A.hijoDrcho(n) != Abin<std::string>::NODO_NULO && A.hijoIzqdo(n)!=Abin<std::string>::NODO_NULO)
    {
        
        //Procesar el caracter que toque, no deja switch asi que usaremos if else ..
        //Simplemente iremos llamando a la operacion que toque de forma recursiva
        if (A.elemento(n)=="+")
        {
            return procesa_arbol(A.hijoIzqdo(n),A) + procesa_arbol(A.hijoDrcho(n),A);
        }
        else if (A.elemento(n)=="-"){
            
            procesa_arbol(A.hijoIzqdo(n),A) - procesa_arbol(A.hijoDrcho(n),A);

        }
        else if (A.elemento(n)=="*"){
        
            procesa_arbol(A.hijoIzqdo(n),A) * procesa_arbol(A.hijoDrcho(n),A);
        
        }
        else if(A.elemento(n)=="/"){

            procesa_arbol(A.hijoIzqdo(n),A) / procesa_arbol(A.hijoDrcho(n),A);
        
        }


    }
    else {//Caso de que no sea un operador si no un numero
        return std::stof(A.elemento(n));
    }
    


}


float post_fijo(Abin<std::string>&A){
    return procesa_arbol(A.raiz(),A);
}



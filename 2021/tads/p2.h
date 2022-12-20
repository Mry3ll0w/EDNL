//@by MrY3ll0w
#ifndef EDNLV2_P2_H
#define EDNLV2_P2_H
#include <string>
#include <iostream>
#include "arbolbinenla.h"
//Funcion generica para realizar la impresion de los elementos de un arbol binario
template <class t>
void print_a(typename Abin<t>::nodo n,Abin<t>&a){
    if(n!=Abin<t>::NODO_NULO){
        print_a(a.hijoIzqdo(n),a);
        std::cout<<"Elementos= "<<a.elemento(n)<<std::endl;
        print_a(a.hijoDrcho(n),a);
    }

}


/*
 * EJERCICIO 1
 * Dos árboles binarios son similares cuando tienen idéntica estructura de ramificación,
 * es decir, ambos son vacíos, o en caso contrario, tienen subárboles izquierdo y derecho
 * similares. Implementa un subprograma que determine si dos árboles binarios son
 * similares.
 */
template <class t>
bool simil_rec(typename Abin<t>::nodo na, typename Abin<t>::nodo nb, const Abin<t>& a, const Abin<t>& b){
    //Recorrido en postorden
    //Caso Base
    if (na == Abin<t>::NODO_NULO && nb == Abin<t>::NODO_NULO){
        return true;
    }

    //Caso general
    if (na == Abin<t>::NODO_NULO || nb == Abin<t>::NODO_NULO) {
        return false;
    }
    return simil_rec(a.hijoDrcho(na),b.hijoDrcho(nb),a,b)&&simil_rec(a.hijoIzqdo(na),b.hijoIzqdo(nb),a,b);
    //FALLABA YA QUE SIEMPRE DA TRUE AL FINAL, SE NECESITA COMPROBAR TODOS LOS CASOS
}

template <class t>
bool ej1(const Abin<t>& a, const Abin<t>&b){
    return simil_rec(a.raiz(),b.raiz(),a,b);
}

/**EJERCICIO 2
 * Para un árbol binario B, podemos construir el árbol binario reflejado B
 * R cambiando los subárboles izquierdo y derecho en cada nodo. Implementa un
 * subprograma que devuelva el árbol binario reflejado de uno dado
 */
template <class t>
void reflejo_arbol(typename Abin<t>::nodo n1,typename Abin<t>::nodo n2,Abin<t>& a,Abin<t>&b){
    if (n1 != Abin<t>::NODO_NULO && n2 !=Abin<t>::NODO_NULO){//Cuando se recorra el arbol se acaba la ejecucion
        //Inversion de los lados ya que n1 primero tiene lado izquierdo de a y lado derecho de b
        reflejo_arbol(a.hijoIzqdo(n1),b.hijoDrcho(n2),a,b);
        b.elemento(n2)=a.elemento(n1);
        reflejo_arbol(a.hijoDrcho(n1),b.hijoIzqdo(n2),a,b);
    }
}

template <class t>
Abin<t> ej2(Abin<t>&a){
    Abin<t>b(a);
    reflejo_arbol(a.raiz(),b.raiz(),a,b);
    print_a(a.raiz(),a);
    std::cout<<"Segundo arbol"<<std::endl<<std::endl;
    print_a(b.raiz(),b);
    return b;
}

/*
 * EJERCICIO 3
 * El TAD árbol binario puede albergar expresiones matemáticas mediante un árbol de
 * expresión. Dentro del árbol binario los nodos hojas contendrán los operandos, y el resto
 * de los nodos los operadores.
 * a) Define el tipo de los elementos del árbol para que los nodos puedan almacenar
 * operadores y operandos.
 * EL tipo de dato mas proclive para esto es un tipo string
 *
 * b) Implementa una función que tome un árbol binario de expresión (aritmética) y
 * devuelva el resultado de la misma. Por simplificar el problema se puede asumir que el
 * árbol representa una expresión correcta. Los operadores binarios posibles en la expresión
 * aritmética serán suma, resta, multiplicación y división.
 */
double procesar_arbol(typename Abin<std::string>::nodo n,Abin<std::string>&a){
    if(a.hijoIzqdo(n)==Abin<std::string>::NODO_NULO && a.hijoDrcho(n)==Abin<std::string>::NODO_NULO){//FALLABA al no comprobar que es Hoja
        return std::stof(a.elemento(n)); //Si ha recorrido el arbol devuelve 0
    }
    else{
        if (a.elemento(n)=="+"){
            return (procesar_arbol(a.hijoIzqdo(n),a) + procesar_arbol(a.hijoDrcho(n),a) );
        }
        else if(a.elemento(n)=="-"){
            return (procesar_arbol(a.hijoIzqdo(n),a) - procesar_arbol(a.hijoDrcho(n),a) );
        }
        else if (a.elemento(n)=="*"){
            return (procesar_arbol(a.hijoIzqdo(n),a) * procesar_arbol(a.hijoDrcho(n),a) );
        }
        else if (a.elemento(n)=="/"){
            return (procesar_arbol(a.hijoIzqdo(n),a) / procesar_arbol(a.hijoDrcho(n),a) );
        }
    }
}

double ej3(Abin<std::string>&a){
    return procesar_arbol(a.raiz(),a);
}

/*
 * EJERCICIO 4
 * preguntar a Dani xdd
 */
#endif //EDNLV2_P2_H

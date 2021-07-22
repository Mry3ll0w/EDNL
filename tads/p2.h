//@by MrY3ll0w
#ifndef EDNLV2_P2_H
#define EDNLV2_P2_H
#include <iostream>
#include "arbolbinenla.h"
template <class t>
void print_a(typename Abin<t>::nodo n,Abin<t>&a){
    if(n!=Abin<t>::NODO_NULO){
        print_a(a.hijoIzqdoB(n),a);
        std::cout<<"Elementos= "<<a.elemento(n)<<std::endl;
        print_a(a.hijoDrchoB(n),a);
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
    return simil_rec(a.hijoDrchoB(na),b.hijoDrchoB(nb),a,b)&&simil_rec(a.hijoIzqdoB(na),b.hijoIzqdoB(nb),a,b);
    //FALLABA YA QUE SIEMPRE DA TRUE AL FINAL, SE NECESITA COMPROBAR TODOS LOS CASOS
}

template <class t>
bool ej1(const Abin<t>& a, const Abin<t>&b){
    return simil_rec(a.raizB(),b.raizB(),a,b);
}

/**
 * Para un árbol binario B, podemos construir el árbol binario reflejado B
 * R cambiando los subárboles izquierdo y derecho en cada nodo. Implementa un
 * subprograma que devuelva el árbol binario reflejado de uno dado
 */
template <class t>
void reflejo_arbol(typename Abin<t>::nodo n1,typename Abin<t>::nodo n2,Abin<t>& a,Abin<t>&b){
    if (n1 != Abin<t>::NODO_NULO && n2 !=Abin<t>::NODO_NULO){//Cuando se recorra el arbol se acaba la ejecucion
        //Inversion de los lados ya que n1 primero tiene lado izquierdo de a y lado derecho de b
        reflejo_arbol(a.hijoIzqdoB(n1),b.hijoDrchoB(n2),a,b);
        b.elemento(n2)=a.elemento(n1);
        reflejo_arbol(a.hijoDrchoB(n1),b.hijoIzqdoB(n2),a,b);
    }
}

template <class t>
Abin<t> ej2(Abin<t>&a){
    Abin<t>b(a);
    reflejo_arbol(a.raizB(),b.raizB(),a,b);
    print_a(a.raizB(),a);
    std::cout<<"Segundo arbol"<<std::endl<<std::endl;
    print_a(b.raizB(),b);
    return b;
}

#endif //EDNLV2_P2_H

// Created by anton on 01/08/2021.
#ifndef EDNLV2_P4_H
#define EDNLV2_P4_H
#include <iostream>
#include <vector>
#include "abb.h"
/*
 * COMO RECORRER ELEMENTOS DE UN ARBOL VACIO
 */
template <class t>
void show_abb(const Abb<t>&a){
    if (!a.vacio()){
        show_abb(a.izqdo());
        std::cout <<a.elemento()<<", ";
        show_abb(a.drcho());
    }

}

/**
 * Implementa una nueva operación del TAD Abb que tomando un elemento del mismo
 * elimine al completo el subárbol que cuelga de él
 */
template <class t>
void poda_rec_abb(int buscado , Abb<t>& a){

    Abb<int>temp_arbol=a.buscar(buscado);//Le asignamos a un arbol temporal el nodo con el elemento buscado
    int elemento_aux;
    while (!temp_arbol.vacio())
    {
        elemento_aux=temp_arbol.elemento();//guardamos en el temporal los subarboles para su eliminacion
        temp_arbol.eliminar(elemento_aux);//Eliminamos del temp el elemento a
        a.eliminar(elemento_aux);//Eliminamos el nodo con el elemento del temp_arbol para ir borrando en el original
    }
}
template <class t>
void ej1(t buscado,Abb<t>& a){
    poda_rec_abb(buscado,a);
}

/*
 * Un árbol binario de búsqueda se puede equilibrar:
 * 1)realizando el recorrido en inorden del árbol para obtener el listado ordenado de sus elementos ,
 * 2)repartir equitativamente los elementos a izquierda y derecha colocando la mediana en la raíz y
 * construyendo recursivamente los subárboles izquierdo y derecho de cada nodo.
 * Implementa este algoritmo para equilibrar un ABB.
 */
template <class t>
void abb_a_vector(const Abb<t>&a,std::vector<t>&v){
    if (!a.vacio()){
        abb_a_vector(a.izqdo(),v);
        v.push_back(a.elemento());
        abb_a_vector(a.drcho(),v);
    }
}
//Hecho con anterioridad por mi, basicamente iteracion mediante busqueda dicotomica
template <class t>
void equilibrar_abb( Abb<t>&a, std::vector<t>&v,int inicio, int fin ){
    if(fin>=inicio)
    {
        int centro=inicio+(fin-inicio)/2;//Insertamos el elemento en la posicion central mediante la busca dicotomica
        // partiendo de la mitad inicial
        //y vamos iterando entre la mitad de los lados del centro-1 y centro+1
        a.insertar(v[centro]);//Insercion elemento
        equilibrar_abb(a,v,inicio, centro-1);//Vamos iterando el inicio y centro -1
        equilibrar_abb(a,v,centro+1,fin);//Vamos iterando el inicio y centro +1
    }
}
//LLamada completa al equilibrio
template<typename T>
Abb<T> ej2(const Abb<T>& origen) //Funcion llamada
{
    Abb<T>destino;
    std::vector<T> v;
    abb_a_vector(origen, v); //Ordena todos los elementos del arbol en v y obtiene el vector para procesarlo en equilibrio
    equilibrar_abb(destino, v, 0, v.size()-1);//Inicio a 0 y fin en el tamaño -1
    return destino;
}

/**
 * 3. Dados dos conjuntos representados mediante árboles binarios de búsqueda,
 * implementa la operación unión de dos conjuntos que devuelva como resultado otro
 * conjunto que sea la unión de ambos, representado por un ABB equilibrado.
 */
 template <class T>
 Abb<T> union_abb(const Abb<T>&a, const Abb<T>&b){
     Abb<T>final;
     std::vector<T> elementos_a,elementos_b,destino;
     abb_a_vector(a,elementos_a);
     abb_a_vector(b,elementos_b);
     //Primero pasamos los elementos de los distintos arboles a vectores
     //Metemos los elementos de a en el destino
     for(auto i:elementos_a){
         destino.push_back(i);
     }
     //Metemos los elementos de de b ya que por definicion el abb no permite repetecion cumpliendo la union
     for(auto i:elementos_b){
         destino.push_back(i);
     }
     //Ordenamos los elementos del vector destino
     destino.sort(destino.begin(), destino.end());
     //Llamammos al equilibrar_abb
     equilibrar_abb(final,destino,0,destino.size()-1);
     return final;
 }
 /**
  * Dados dos conjuntos representados mediante árboles binarios de búsqueda,
  * implementa la operación intersección de dos conjuntos, que devuelva como resultado
  * otro conjunto que sea la intersección de ambos. El resultado debe quedar en un árbol
  * equilibrado.
  */
 template <class T>
 Abb<T> interseccion_abb(const Abb<T>&a, const Abb<T>&b){
             Abb<T>final;
             std::vector<T> elementos_a,elementos_b,destino;
             abb_a_vector(a,elementos_a);
             abb_a_vector(b,elementos_b);
             //Primero pasamos los elementos de los distintos arboles a vectores
             //Metemos los elementos de a y b que coinciden en el destino
             for(auto i:elementos_a){
                 for (auto j:elementos_b) {
                     if (elementos_a[i]==elementos_b[j]){
                         destino.push_back(i);
                     }
                 }
             }
             //Ordenamos los elementos del vector destino
             destino.sort(destino.begin(), destino.end());
             //Llamammos al equilibrar_abb
             equilibrar_abb(final,destino,0,destino.size()-1);
             return final;
 }

 /** EJERCICIO 5
  * A (rombo) B = (a union b) - (a intersection b)
  * Implementar operacion -
  */
  template <class t>
  Abb<t> operator - (Abb<t>&a, Abb<t>&b){
        //Arbol final resultado de la operación
        Abb<t>abb_final;
        //Pasamos a vector todos los elementos de los abb
        std::vector<t> va,vb,v_final;
        abb_a_vector(a,va);
        abb_a_vector(b,vb);
        //Hacemos la operacion - (elimina los elementos coincidentes con b del vector a)
        //Con los elementos de a
        for(auto i:va){
            for(auto j:vb){
                if (va[i]!=vb[j]){
                    v_final.push_back(va[a]);
                }
            }
        }
        //Con los elementos de b
        for(auto i:vb){
            for(auto j:v_final){
                if (vb[i]!=v_final[j]){
                    v_final.push_back(vb[i]);
                }
            }
        }
        //Metemos los elemtos del vector final en el arbol final
        for(auto i:v_final){
            abb_final.insertar(v_final[i]);
        }
        return abb_final;
  }

  template<class t>
  Abb<t> operador_rombo(Abb<t>&a,Abb<t>&b){
      return union_abb(a,b)-interseccion_abb(a,b);
  }

#endif //EDNLV2_P4_H

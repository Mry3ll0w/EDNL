#ifndef EDNLV2_PRACTICA4_H
#define EDNLV2_PRACTICA4_H

#include <vector>
#include "abb.h"
#include "arbolbinenla.h"

void eliminar_arbol(int elemento_buscado,Abb<int>Arbol)
{
    Abb<int>temp_arbol=Arbol.buscar(elemento_buscado);
    int elemento_aux;
    while (!temp_arbol.vacio())
    {
        elemento_aux=temp_arbol.elemento();
        temp_arbol.eliminar(elemento_aux);
        Arbol.eliminar(elemento_aux);
    }
}

//PRIMERO necesitamos de una funcion para la lectura de los elementos del arbol
template<typename T> void Abb2vector(const Abb<T>& a, std::vector<T>& v)
{
    if(!a.vacio())
    {
        Abb2vector(a.izqdo(),v);//Realizamos el recorrido en inorden, primero la izq
        v.push_back(a.elemento());//Introducimos en el final del vector para tenerlos ordenados de menor a mayor
        Abb2vector(a.drcho(),v);//Realizamos el recorrido en inorden, por la parte derecha
    }
}
//Llamada recursiva al equilibrio del arbol
template<typename T>
void equilibrar_rec(Abb<T>& a, const std::vector<T>& v, int inicio, int fin)
{
    if(fin>=inicio)
    {
        int centro=inicio+(fin-inicio)/2;//Insertamos el elemento en la posicion central mediante la busca dicotomica partiendo de la mitad inicial
                                        //y vamos iterando entre la mitad de los lados del centro-1 y centro+1
        a.insertar(v[centro]);//Insercion elemento
        equilibrar_rec(a,v,inicio, centro-1);//Vamos iterando el inicio y centro -1
        equilibrar_rec(a,v,centro+1,fin);//Vamos iterando el inicio y centro +1
    }
}
//LLamada completa al equilibrio
template<typename T> Abb<T>& equilibrar(Abb<T>& origen) //Funcion llamada
{
    Abb<T> *destino=new Abb<T>();
    std::vector<T> v;
    Abb2vector(origen, v); //Ordena todos los elementos del arbol en v y obtiene el vector para procesarlo en equilibrio
    equilibrar_rec(*destino, v, 0, v.size()-1);//Inicio a 0 y fin en el tamaño -1
    return *destino;
}

//UNION//////////////////////////////////////////////////////
template<typename t>
void copia_rec(Abb<t>&origen,Abb<t>&destino){
    if(!origen.vacio())
    {
        Abb2vector(origen.izqdo(),destino);//Realizamos el recorrido en inorden, primero la izq
        destino.insertar(origen.elemento());
        Abb2vector(origen.drcho(),destino);//Realizamos el recorrido en inorden, por la parte derecha
    }
}

template<typename t>
Abb<t>& union_arbol(Abb<t>& a1, Abb<t>a2){
    Abb<t>temp;
    temp = a1;
    copia_rec(a2,temp);
    equilibrar(temp);
    return temp;
}

///////////////////////////////////////////////////////////INTERSECCION///////////////////////////////////////////////////////////////
template<typename t>
void iters_copy(Abb<t>&origen,Abb<t>&destino,Abb<t>&temp){
    if(!origen.vacio())
    {
        Abb2vector(origen.izqdo(),destino,temp);//Realizamos el recorrido en inorden, primero la izq
        Abb<t>abb_check=destino.buscar(origen.elemento());
        if (!abb_check.vacio()){//SI el arbol check es vacio significa que el elemento no esta en el destino por tanto no se inserta
            temp.insertar(origen.elemento());
        }
        Abb2vector(origen.drcho(),destino,temp);//Realizamos el recorrido en inorden, por la parte derecha
    }
}

template<typename t>
Abb<t> interseccion_arbol(Abb<t>& a1, Abb<t>& a2){
    Abb<t> temp;
    inters_copy(a2,a1,temp);//Comprueba si son iguales y va insertando
    return temp;
}

template<typename t>
void operador_resta(Abb<t>&a1,std::vector<t>parser_vec,typename std::vector<t>::iterator i,Abb<t>& res){
    if ((!a1.vacio())||(i!=parser_vec.size())){
        operador_resta(a1.izqdo(),parser_vec,i);
        res.insertar(a1.elemento()-*i);
        ++i;
        operador_resta(a1.drcho(),parser_vec,i);
    }
}

template<typename t>
Abb<t>operador_rombo(Abb<t>&a1, Abb<t>& a2){
    Abb<t>inter_abb,union_abb,res;
    inter_abb = interseccion_arbol(a1,a2);
    union_abb=union_arbol(a1,a2);
    res = operador_resta(inter_abb,union_abb);
    return res;
}

#endif //EDNLV2_PRACTICA4_H

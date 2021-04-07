#ifndef EDNLV2_PRACTICA4_H
#define EDNLV2_PRACTICA4_H
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
//Mediana comienza en 0
int recorre_arbol_med(Abb<int>Arbol, int cont){
    if (Arbol.vacio())//Si esta vacio
        return cont;
    else
        recorre_arbol_med(Arbol.izqdo(), cont);
        cont++;
        recorre_arbol_med(Arbol.drcho(),cont);
}
void mediana(Abb<int>Arbol,int v[],int iter){
    if (!Arbol.vacio())//Si esta vacio
        mediana(Arbol.izqdo(), v,iter++);
        v[iter]=Arbol.elemento();
        mediana(Arbol.drcho(),v,iter++);
}


void equilibrar_arbol(Abb<int>Arbol){
    Abb<int>temp;
    int n_elementos =recorre_arbol_med(Arbol,0);
    int v[n_elementos];
    mediana(Arbol,v,0);
    temp.insertar(n_elementos/2);//LA mediana esta en n_elementos / 2
    for (const size_t i:v) {
        temp.insertar(v[i]);
    }
    Arbol= temp;
}

#endif //EDNLV2_PRACTICA4_H

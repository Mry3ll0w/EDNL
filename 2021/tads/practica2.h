//
// Created by anton on 09/03/2021.
//
#ifndef EDNL_PRACTICA2_H
#define EDNL_PRACTICA2_H
#include <iostream>
using namespace std;
#include "arbolbinenla.h"
/*
 * 1. Dos árboles binarios son similares cuando tienen idéntica estructura de ramificación,
 * es decir, ambos son vacíos, o en caso contrario, tienen subárboles izquierdo y derecho
 * similares. Implementa un subprograma que determine si dos árboles binarios son
 * similares.*/
template <typename t>
bool similares(Abin<t> &a, Abin<t> &b, typename Abin<t>::nodo n1, typename Abin<t>::nodo n2){
    if (n1!=Abin<t>::NODO_NULO && n2!=Abin<t>::NODO_NULO){
        similares(a,b,a.hijoIzqdo(n1),b.hijoIzqdo(n2));
        similares(a,b,a.hijoDrcho(n1),b.hijoDrcho(n2));
    }
    if (n1==Abin<t>::NODO_NULO && n2==Abin<t>::NODO_NULO)
        return true;
    if (n1==Abin<t>::NODO_NULO || n2==Abin<t>::NODO_NULO)//Si esto se da se ha llegado al caso base
        return false;
}//fallo syntax pero bien

template <typename t>
void reflejo(Abin<t>& a,typename Abin<t>::nodo n){
    int parser_element;
    if (n!=Abin<t>::NODO_NULO){
        reflejo(a,a.hijoIzqdo(n));
        parser_element=a.elemento(a.hijoIzqdo(n));
        a.insertarhijoDrcho(a.hijoIzqdo(n),a.elemento(a.hijoDrcho(n)));
        a.insertarhijoIzqdo(a.hijoIzqdo(n),parser_element);
        reflejo(a,a.hijoDrcho(n));
    }

}

float evaluar_llamada_rec(Abin<string>a,Abin<string>::nodo n){
    if (n->hder==Abin<string>::NODO_NULO && n->hizq==Abin<string>::NODO_NULO){//ES HOJA
        return stof(a.elemento(n));
    }
    else{
        if (a.elemento(n)=="+"){
            return (evaluar_llamada_rec(a,a.hijoIzqdo(n))+evaluar_llamada_rec(a,a.hijoDrcho(n)));
        }
        else if (a.elemento(n)=="-"){
            return (evaluar_llamada_rec(a,a.hijoIzqdo(n))-evaluar_llamada_rec(a,a.hijoDrcho(n)));
        }
        else if (a.elemento(n)=="*"){
            return (evaluar_llamada_rec(a,a.hijoIzqdo(n))*evaluar_llamada_rec(a,a.hijoDrcho(n)));
        }
        else{
            return (evaluar_llamada_rec(a,a.hijoIzqdo(n))/evaluar_llamada_rec(a,a.hijoDrcho(n)));
        }
    }
}
float Evaluar_llamada(Abin<string>a){//EJERCICIO3
    if (a.arbolVacio()){
        return 0;
    }
    else
        return evaluar_llamada_rec(a,a.raiz());
}

#endif //EDNL_PRACTICA2_H

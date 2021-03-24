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
        similares(a,b,a.hijoIzqdoB(n1),b.hijoIzqdoB(n2));
        similares(a,b,a.hijoDrchoB(n1),b.hijoDrchoB(n2));
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
        reflejo(a,a.hijoIzqdoB(n));
        parser_element=a.elemento(a.hijoIzqdoB(n));
        a.insertarHijoDrchoB(a.hijoIzqdoB(n),a.elemento(a.hijoDrchoB(n)));
        a.insertarHijoIzqdoB(a.hijoIzqdoB(n),parser_element);
        reflejo(a,a.hijoDrchoB(n));
    }

}

float evaluar_llamada_rec(Abin<string>a,Abin<string>::nodo n){
    if (n->hder==Abin<string>::NODO_NULO && n->hizq==Abin<string>::NODO_NULO){//ES HOJA
        return stof(a.elemento(n));
    }
    else{
        if (a.elemento(n)=="+"){
            return (evaluar_llamada_rec(a,a.hijoIzqdoB(n))+evaluar_llamada_rec(a,a.hijoDrchoB(n)));
        }
        else if (a.elemento(n)=="-"){
            return (evaluar_llamada_rec(a,a.hijoIzqdoB(n))-evaluar_llamada_rec(a,a.hijoDrchoB(n)));
        }
        else if (a.elemento(n)=="*"){
            return (evaluar_llamada_rec(a,a.hijoIzqdoB(n))*evaluar_llamada_rec(a,a.hijoDrchoB(n)));
        }
        else{
            return (evaluar_llamada_rec(a,a.hijoIzqdoB(n))/evaluar_llamada_rec(a,a.hijoDrchoB(n)));
        }
    }
}
float Evaluar_llamada(Abin<string>a){//EJERCICIO3
    if (a.arbolVacioB()){
        return 0;
    }
    else
        return evaluar_llamada_rec(a,a.raizB());
}

#endif //EDNL_PRACTICA2_H

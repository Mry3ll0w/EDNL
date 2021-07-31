#include <iostream>
#include "tads/p3.h"

int main() {
    Agen<char>arbol;
    arbol.insertarRaiz('a');
    arbol.insertarHijoIzqdo(arbol.raiz(),'b');
    arbol.insertarHermDrcho(arbol.hijoIzqdo(arbol.raiz()),'c');
    arbol.insertarHermDrcho(arbol.hermDrcho(arbol.hijoIzqdo(arbol.raiz())),'d');
    std::cout<< ej3(arbol)<<std::endl;
    return 0;
}

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

#endif //EDNLV2_PRACTICA4_H

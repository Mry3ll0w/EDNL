#include <iostream>
#include "abb.h"
#include "Apo.h"
#include "Practicas_ABB.h"
#include "pracitcas_apo.h"
int main()
{
    Agen<int> a;
    a.insertarRaiz(1);
    a.insertarHijoIzqdo(a.raiz(), 2);
    a.insertarHermDrcho(a.hijoIzqdo(a.raiz()), 3);
    a.insertarHijoIzqdo(a.hijoIzqdo(a.raiz()), 4);
    
    std::cout << ternario_rec(a,a.raiz()) << std::endl;

    return 0;
}



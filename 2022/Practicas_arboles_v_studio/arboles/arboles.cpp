#include <iostream>
#include "practicas_agen.h"

int main()
{
    Agen<int>A;
    A.insertarRaiz(1);
    A.insertarHijoIzqdo(A.raiz(), 2);
    A.insertarHermDrcho(A.hijoIzqdo(A.raiz()), 3);
    A.insertarHermDrcho(A.hijoIzqdo(A.raiz()), 4);
    A.insertarHermDrcho(A.hijoIzqdo(A.raiz()), 5);
    
    std::cout << desequilibrio_agen(A) << std::endl;
    return 0;
}



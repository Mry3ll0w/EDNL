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

    A.insertarHijoIzqdo(A.hijoIzqdo(A.raiz()), 6);
    A.insertarHermDrcho(A.hijoIzqdo(A.hijoIzqdo(A.raiz())), 7);
    A.insertarHermDrcho(A.hijoIzqdo(A.hijoIzqdo(A.raiz())), 8);

    imprime_arbol(A, A.raiz());
    
    Agen<int>B = poda(3, A);

    imprime_arbol(B,B.raiz());

    //std::cout << desequilibrio_agen(A) << std::endl;

    return 0;
}
    


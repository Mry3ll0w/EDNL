#include <iostream>
#include "practicas_agen.h"
#include "practicas_apo.h"
int main()
{

    Agen<char> A;
    A.insertarRaiz('M');
    A.insertarHijoIzqdo(A.raiz(), 'B');
    A.insertarHermDrcho(A.hijoIzqdo(A.raiz()), 'N');
    A.insertarHermDrcho(A.hermDrcho(A.hijoIzqdo(A.raiz())), 'B');
    A.insertarHermDrcho(A.hermDrcho(A.hermDrcho(A.hijoIzqdo(A.raiz()))), 'n');
    std::cout<<volcado(A)<<std::endl;

    return 0;
}
    


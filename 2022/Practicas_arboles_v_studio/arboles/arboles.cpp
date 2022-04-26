#include <iostream>
#include "practicas_agen.h"
#include "practicas_apo.h"
int main()
{
<<<<<<< HEAD
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
=======
    Agen<char> A;
    A.insertarRaiz('M');
    A.insertarHijoIzqdo(A.raiz(), 'B');
    A.insertarHermDrcho(A.hijoIzqdo(A.raiz()), 'N');
    A.insertarHermDrcho(A.hermDrcho(A.hijoIzqdo(A.raiz())), 'B');
    A.insertarHermDrcho(A.hermDrcho(A.hermDrcho(A.hijoIzqdo(A.raiz()))), 'n');
    std::cout<<volcado(A)<<std::endl;
>>>>>>> main

    return 0;
}
    


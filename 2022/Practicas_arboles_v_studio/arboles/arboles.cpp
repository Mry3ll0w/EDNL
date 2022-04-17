#include <iostream>
#include "abb.h"
#include "Apo.h"
#include "Practicas_ABB.h"
int main()
{

    Abb<int>A,B,C,D;
    A.insertar(7);
    A.insertar(5);
    A.insertar(12);
    A.insertar(9);
    A.insertar(17);
    A.insertar(8);
    A.insertar(11);
    A.insertar(10);

    B.insertar(4);
    B.insertar(8);
    B.insertar(11);
    B.insertar(68);
    
    
    imprime_arbol(rombo(A,B));
    return 0;
}


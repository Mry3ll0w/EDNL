#include <iostream>
#include "abb.h"
#include "Apo.h"
#include "Practicas_ABB.h"
int main()
{

    Abb<int>A;
    A.insertar(7);
    A.insertar(5);
    A.insertar(12);
    A.insertar(9);
    A.insertar(17);
    A.insertar(8);
    A.insertar(11);
    A.insertar(10);

    std::list<int> l;
    l=elementos_abb(A, l);
    l.sort();
    for (auto i : l) {
        std::cout << i << ", ";
    }
    std::cout << std::endl;
    imprime_arbol(A);
    
    return 0;
}


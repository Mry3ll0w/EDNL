#include <iostream>
#include "tads/p4.h"
#include <vector>



int main() {
    Abb<int>a,it;
    a.insertar(1);
    a.insertar(2);
    a.insertar(3);
    a.insertar(5);
    a.insertar(4);
    a.insertar(0);
    show_abb(a);
    std::cout <<std::endl;

    a = ej2(a);
    show_abb(a);
    return 0;
}

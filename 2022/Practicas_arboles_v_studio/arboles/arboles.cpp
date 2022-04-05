#include <iostream>
#include "abb.h"
#include "Apo.h"
int main()
{

    Abb<int>A;
    A.insertar(6);
    A.insertar(8);
    A.insertar(1);

    std::cout << A.elemento() << std::endl;
}


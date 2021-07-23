#include <iostream>

#include "tads/p2.h"

typedef char tElto;
// fin de lectura
using namespace std;

int main() {
    Abin<char>a;
    a.insertarRaizB('a');
    a.insertarHijoDrchoB(a.raizB(),'b');
    a.insertarHijoIzqdoB(a.raizB(),'c');
    a.insertarHijoIzqdoB(a.hijoIzqdoB(a.raizB()),'d');

    Abin<string>b;
    b.insertarRaizB("+");
    b.insertarHijoDrchoB(b.raizB(),"3");
    b.insertarHijoIzqdoB(b.raizB(),"4");

    std::cout<<ej3(b)<<std::endl;

    return 0;
}

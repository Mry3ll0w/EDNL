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

    Abin<char>b;
    b.insertarRaizB('a');
    b.insertarHijoDrchoB(b.raizB(),'x');
    b.insertarHijoIzqdoB(b.raizB(),'c');
    b.insertarHijoIzqdoB(b.hijoIzqdoB(b.raizB()),'d');

    ej2(a);

    return 0;
}

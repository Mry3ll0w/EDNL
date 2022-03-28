#include <iostream>
#include "abin_rel.hpp"

struct elemento;


struct elemento{
    
    char operador;
    
    double numero;

    elemento(char c):operador(c) {}

    elemento(int i):operador(i) {}

    elemento(double f):numero(f){}

};

bool operator==(elemento e, char c){
    return e.operador == c;
}

bool operator ==(elemento e, float f){
    return e.operador == f;
}

int main(){
    
    elemento e(4),d('f');

return 0;
}


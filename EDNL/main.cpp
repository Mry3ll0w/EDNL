#include <iostream>
#include "tads/agenEnlazado.h"
#include "tads/agen_E-S.h"
#include "tads/practica3.h"
typedef char tElto;
const tElto fin = '#'; // fin de lectura

using namespace std;

int main() {
    Agen<char>A;
    ifstream fe("ej_arbol.txt"); // Abrir fichero de entrada.
    rellenarAgen(fe, A); // Desde fichero.
    fe.close();
    cout<<altura_nodo(A,A.hermDrcho(A.hermDrcho(A.hijoIzqdo(A.raiz()))))<<endl;

    return 0;
}

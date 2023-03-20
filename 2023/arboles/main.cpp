#include <iostream>
#include "p1.h"
#include "p2.hpp"
#include "p3.hpp"
#include "agenEnlazado.h"
#include <iostream>
#include "abinrel.hpp"
#include <fstream>
#include "arbolbinenla.h"
#include "abin_E-S.h"
using namespace std;
typedef char tElto;
const tElto fin = '#';

int main()
{
    Abin<tElto> A;
    // Fin de lectura.
    cout << "\n*** Lectura de árbol binario B de abin.dat ***\n";
    ifstream fe("abin.dat"); // Abrir fichero de entrada. rellenarAbin(fe, B); // Desde fichero.
    rellenarAbin(fe, A);
    fe.close();
    cout << "\n*** Mostrar árbol binario A ***\n";
    imprimirAbin(A);
}
#include <iostream>
#include "p1.h"
#include <iostream>
#include <fstream>
#include "arbolbinenla.h"
#include "abin_E-S.h"
using namespace std;
typedef char tElto;
const tElto fin = '#';
int main()
{
    Abin<tElto> A, B;
    // Fin de lectura.
    cout << "\n*** Lectura de árbol binario B de abin.dat ***\n";
    ifstream fe("abin.dat"); // Abrir fichero de entrada. rellenarAbin(fe, B); // Desde fichero.
    rellenarAbin(fe, A);
    fe.close();
    cout << "\n*** Mostrar árbol binario B ***\n";
    imprimirAbin(A);
}
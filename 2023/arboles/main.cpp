#include <iostream>
#include "p1.h"
#include "p2.hpp"
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
    Abin<std::string> abPost;
    abPost.insertaRaiz("+");
    abPost.insertarhijoDrcho(abPost.raiz(), "2");
    abPost.insertarhijoIzqdo(abPost.raiz(), "5");
    cout << procesaPostfijo(abPost, abPost.raiz()) << endl;

    AbinRel<int> abRel(3);
}
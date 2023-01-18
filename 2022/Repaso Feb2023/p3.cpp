#include <iostream>
#include "2022/arboles/agenEnlazado.h"
using namespace std; // Avoid using std:: ....

// Ejercicio 1 : Averiguar el grado de un arbol

template <class t>
size_t cuentaNodosNivel(typename Agen<t>::nodo n, Agen<t> &a)
{
    if (n == Agen<t>::NODO_NULO)
        return 0;
    else
        return 1 + cuentaNodosNivel(a.hermDrcho(n), a);
}

template <class t>
size_t gradoMaximoArbol(typename Agen<t>::nodo n, size_t cont, Agen<t> &a)
{
    if (n == Agen<t>::NODO_NULO)
    {
        return cont;
    }
    cont = std::max(cuentaNodosNivel(a.hermDrcho(n), a), cuentaNodosNivel(n, a));
    gradoMaximoArbol(a.hijoIzqdo(n), cont, a);
}

int main()
{

    return 0;
}
#include <iostream>
#include "agenEnlazado.h"
using namespace std; // Avoid using std:: ....

/**
 * El tema esta en que tenemos que repartir la herencia de un nodo dado, entre el resto de descendientes.
 * Cada nodo al cual "matamos" tiene que pasar el bool de true a false y ademas la cantidad de dinero que
 * posee pasa a ser 0.
 *
 * 1) Funcion para matar nodos.
 * 2) Comprobar si el nodo esta muerto o vivo.
 * 3) Contar el numero de descendientes vivos y repartir el dinero entre ellos.
 * 4) Funcion para dar dinero a cada nodo.
 */

struct Persona
{
    int iID;
    bool bVivo;
    double dDinero;
    Persona(bool vivo = true, double dinero = 0, int id = -1) : bVivo(vivo), dDinero(dinero), iID(id) {}
    bool operator==(const Persona &p) { return p.iID == iID; }
};

void contarNodosVivos(Agen<Persona> A, typename Agen<Persona>::nodo n, int &iNumeroNodos)
{
    if (n != Agen<Persona>::NODO_NULO)
    {

        // Procesar
        if (A.elemento(n).bVivo)
            iNumeroNodos++;

        n = A.hijoIzqdo(n);
        while (n != Agen<Persona>::NODO_NULO)
        {
            contarNodosVivos(A, n, iNumeroNodos);
            n = A.hermDrcho(n);
        }
    }
}

void repartirHerencia(Agen<Persona> A, typename Agen<Persona>::nodo n, double dinero)
{
    if (n != Agen<Persona>::NODO_NULO)
    {

        // Procesar
        if (A.elemento(n).bVivo)
            A.elemento(n).dDinero += dinero;

        n = A.hijoIzqdo(n);
        while (n != Agen<Persona>::NODO_NULO)
        {
            repartirHerencia(A, n, dinero);
            n = A.hermDrcho(n);
        }
    }
}

void Herederos(Agen<Persona> A, typename Agen<Persona>::nodo n)
{
    if (A.arbolVacio())
        throw invalid_argument("El arbol dado esta vacio, no hay nada a repartir");

    A.elemento(n).bVivo = false;
    int iDescendientes = 0;
    contarNodosVivos(A, n, iDescendientes);
    if (iDescendientes != 0)
    {
        double dHerencia = A.elemento(n).dDinero / (iDescendientes - 1);
        A.elemento(n).dDinero = -1;
        repartirHerencia(A, n, dHerencia);
    }
    else
    {
        A.elemento(n).dDinero = -1;
        cout << "Persona muerta, pero no tiene descendientes vivos a quienes dar herencia, se lo queda el estado." << endl;
    }
}

int main()
{

    Agen<int> A;

    return 0;
}
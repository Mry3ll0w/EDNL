#include <iostream>
#include "../arboles/arbolbinenla.h"
using namespace std; // Avoid using std:: ....

// Ejercicio 1: Funcion para contar todos los nodos de un arbol dado

template <class T>
int cuentaNodosAbinRec(const Abin<T> &arbol, typename Abin<T>::nodo nodo)
{
    if (nodo == Abin<T>::NODO_NULO)
        return 0;
    return 1 + cuentaNodosAbinRec(arbol, arbol.hijoIzqdo(nodo)) + cuentaNodosAbinRec(arbol, arbol.hijoDrcho(nodo));
}

template <class T>
int cuentaNodosAbin(const Abin<T> &arbol)
{
    return cuentaNodosAbinRec(arbol, arbol.raiz());
}

// Ejercicio 2: Implementa un subprograma que calcule la altura de un árbol binario, la altura de un arbol binario es
// altura maxima de todas las ramas.

template <class T>
const int alturaAbinRec(const Abin<T> &arbol, typename Abin<T>::nodo nodo)
{
    if (nodo == Abin<T>::NODO_NULO)
        return -1;

    return 1 + max(alturaAbinRec(arbol, arbol.hijoIzqdo(nodo)), alturaAbinRec(arbol, arbol.hijoDrcho(nodo)));
}

template <class T>
int alturaAbin(const Abin<T> &arbol)
{
    return alturaAbinRec(arbol, arbol.raiz());
}

// Ejercicio 3:Implementa un subprograma que, dados un árbol binario y un nodo del mismo,
// determine la profundidad de este nodo en dicho árbol.
template <class T>
const int profundidadNodo(const Abin<T> &arbol, typename Abin<T>::nodo n)
{
    if (n == Abin<T>::NODO_NULO)
        return -1;
    return 1 + profundidadNodo(arbol, arbol.padre(n));
}

// Implementa un subprograma que determine el nivel de desequilibrio de un árbol binario,
// definido como el máximo desequilibrio de todos sus nodos.
// El desequilibrio de un nodo se define como la diferencia entre las alturas de los subárboles del mismo.

template <class T>
const int diferenciaAltura(const Abin<T> &arbol, typename Abin<T>::nodo n)
{
    return abs(alturaAbinRec(arbol, arbol.hijoIzqdo(n)) - alturaAbinRec(arbol, arbol.hijoDrcho(n)));
}

template <class T>
int desequilibrioAbinRec(const Abin<T> &arbol, typename Abin<T>::nodo n)
{
    if (n == Abin<T>::NODO_NULO)
        return 0;
    return max(diferenciaAltura(arbol, n),
               max(desequilibrioAbinRec(arbol, arbol.hijoDrcho(n)), desequilibrioAbinRec(arbol, arbol.hijoIzqdo(n))));
}

template <class T>
const int desequilibrioAbin(const Abin<T> &arbol)
{
    return desequilibrioAbinRec(arbol, arbol.raiz());
}

/*
 * Implementa un subprograma que determine si un árbol binario es o no pseudocompleto.
 * En este problema entenderemos que un árbol es pseudocompleto, si en el penúltimo nivel
 * del mismo cada uno de los nodos tiene dos hijos o ninguno.
 * Pasos:
 * 	1) Saber si estamos en el penultimo nivel.
 *  2) Obtener nodos penultimo nivel
 * 	3) Comprobar si los nodos tiene dos hijos o ninguno
 */
template <class T>
const bool dosHijosNinguno(const Abin<T> &arbol, typename Abin<T>::nodo n)
{
    if (
        n != Abin<T>::NODO_NULO &&
        (arbol.hijoIzqdo(n) != Abin<T>::NODO_NULO && arbol.hijoDrcho(n) != Abin<T>::NODO_NULO ||
         arbol.hijoIzqdo(n) == Abin<T>::NODO_NULO && arbol.hijoDrcho(n) == Abin<T>::NODO_NULO))
        return true;
    else
        return false;
}

template <class T>
const bool penultimoNivel(const int &alturaArbol, const Abin<T> arbol, typename Abin<T>::nodo &n)
{
    if (n != Abin<T>::NODO_NULO && alturaArbol - profundidadNodo(arbol, n) == 1)
        return true;
    else
        return false;
}

template <class T>
bool pseudocompletoRec(const Abin<T> arbol, typename Abin<T>::nodo n)
{
    // Obtenemos la altura para ahorrar calculo
    int alturaArbol = alturaAbin(arbol);
    // Hallamos el nodo en el penultimo nivel de cada rama
    auto nodoizq = arbol.hijoIzqdo(n);
    while (nodoizq != Abin<T>::NODO_NULO && arbol.hijoIzqdo(nodoizq) != Abin<T>::NODO_NULO && !penultimoNivel(alturaArbol, arbol, nodoizq))
    {
        nodoizq = arbol.hijoIzqdo(nodoizq);
    }

    auto nodoDer = arbol.hijoDrcho(n);
    while (nodoDer != Abin<T>::NODO_NULO && arbol.hijoDrcho(nodoDer) != Abin<T>::NODO_NULO && !penultimoNivel(alturaArbol, arbol, nodoDer))
    {
        nodoDer = arbol.hijoDrcho(nodoDer);
    }
    // Tras llegar al penultimo nivel comprobamos hijos
    return dosHijosNinguno(arbol, nodoDer) && dosHijosNinguno(arbol, nodoizq);
}

template <class T>
bool pseudoCompleto(const Abin<T> arbol)
{

    if (arbol.arbolVacio())
    {
        return true;
    }
    else
        return pseudocompletoRec(arbol, arbol.raiz());
}

int main()
{
    Abin<int> a;
    a.insertarraiz(1);
    a.insertarhijoDrcho(a.raiz(), 3);
    a.insertarhijoIzqdo(a.raiz(), 2);
    a.insertarhijoDrcho(a.hijoDrcho(a.raiz()), 4);
    cout << pseudocompletoRec(a, a.raiz()) << endl;
    return 0;
}

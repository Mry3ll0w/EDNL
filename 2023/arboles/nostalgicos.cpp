#include <iostream>
#include "agenEnlazado.h"
#include "abin_enla.h"
/**
 *
 * Definimos un nodo nostálgico como aquel que tiene más pasado que futuro, es decir son
 * los nodos que tienen más antecesores propios que descendientes propios.
 * Necsitamos:
 * 0) Para contar los los decendientes necesitamos saber que altura tiene el nodo a contar
 * 1) Funcion que cuente cuantos nodos tiene el nodo dado por arriba (cuenta pasado)
 * 2) Funcion que cuente cuantos nodos tiene el nodo dado por debajo (cuenta descendientes)
 * 3) Funcion que determine si el nodo dado es nostalgico ( Pasado - Futuro > 0)
 * 4) Funcion que cuente cuantos nodos del arbol cumplen la condicion de ser nostalgicos.
 *
 * Este ejercicio se hara para la versión de Abin y para Agen
 */

// Version Abin

template <class T>
int nivelNodo(Abin<T> abArbol, typename Abin<T>::nodo n)
{
}

int main()
{

  return 0;
}

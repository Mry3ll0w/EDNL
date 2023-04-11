#include <iostream>
#include "abin_enla.h"
/**
 * Ejercicio 1
 * a)No sirve no es un apo, puesto que no existe condiciones que no impidan
 * pasar elementos que no sean un apo.
 * b) No tiene pq estar equilibrado
 * c) Usar un arbol binario
 */

/**
 * @brief Comprueba que todos los nodos que se encuentran debajo
 * @return bool
 * @param Abin<T>&
 * @param Abin<T>::nodo
 */
template <class T>
bool nodoOrdenado(Abin<T> &abArbol, typename Abin<T>::nodo nd)
{
    bool bOrdenado = true;
    if (nd != Abin<T>::NODO_NULO && bOrdenado)
    {
        nodoOrdenado(abArbol, abArbol.hijoDrcho(nd));
        bOrdenado = abArbol.elemento(nd) < abArbol.elemento(abArbol.hijoDrcho(nd)) && abArbol.elemento(nd) < abArbol.elemento(abArbol.hijoIzqdo(nd));
        nodoOrdenado(abArbol, abArbol.hijoIzqdo(nd));
    }
    return bOrdenado;
}

/**
 * @brief Encontrar elemento dentro de Abin
 * @param Abin<T>&
 * @param Abin<T>::nodo
 * @return Abin<T>::nodo
 */
template <class T>
typename Abin<T>::nodo buscaNodo(Abin<T> &abArbol, typename Abin<T>::nodo nd, const T &elto)
{
    typename Abin<T>::nodo nodoBuscado = Abin<T>::NODO_NULO;
    if (nd != Abin<T>::NODO_NULO && nodoBuscado == Abin<T>::NODO_NULO)
    {
        buscaNodo(abArbol, abArbol.hijoDrcho(nd), elto);
        if (abArbol.elemento(nd) == elto)
            nodoBuscado = nd;
        buscaNodo(abArbol, abArbol.hijoDrcho(nd), elto);
    }
}

/**
 * @brief Eliminar el elemento dentro del nodo dado, usando una implementación con std::vector
 * @return void
 *
 */
template <class T>
void eliminarElemento(Abin<T> &abArbol, typename Abin<T>::nodo nd)
{
}
#include <iostream>
#include <vector>
#include "arbolbinenla.h"
#include "agenEnlazado.h"
using namespace std; // Avoid using std:: ....

// Contar numero de nodos del arbol que tienen exactamente 3 nietos

template <class T>
int contarDescendientesDirectos(typename Abin<T>::nodo nd, Abin<T> &abArbol)
{
    if (nd == Abin<T>::NODO_NULO)
    {
        return 0;
    }
    else
    {
        int iNumeroDescendientes = 0;
        if (abArbol.hijoDrcho(nd) != Abin<T>::NODO_NULO)
        {
            iNumeroDescendientes++;
        }

        if (abArbol.hijoIzqdo(nd) != Abin<T>::NODO_NULO)
            iNumeroDescendientes++;

        return iNumeroDescendientes;
    }
}

template <class T>
bool tiene3nietos(typename Abin<T>::nodo nd, Abin<T> &abArbol)
{
    // hijo izq + hijo der, al ser un bin necesita los 2 hijos para obtener al menos 3 nietos
    auto ndHijoIzq = abArbol.hijoIzqdo(nd);
    auto ndHijoDer = abArbol.hijoDrcho(nd);
    if (ndHijoDer != Abin<T>::NODO_NULO && ndHijoIzq != Abin<T>::NODO_NULO)
    {
        return (contarDescendientesDirectos(ndHijoDer, abArbol) + contarDescendientesDirectos(ndHijoIzq, abArbol)) == 3;
    }
    else
        return false;
}

template <class T>
void contar3NietosRec(typename Abin<T>::nodo nd, Abin<T> &abArbol, int &iNumero3Nietos)
{
    if (nd != Abin<T>::NODO_NULO)
    {
        contar3NietosRec(abArbol.hijoIzqdo(nd), abArbol, iNumero3Nietos);

        if (tiene3nietos(nd, abArbol))
            iNumero3Nietos++;

        contar3NietosRec(abArbol.hijoDrcho(nd), abArbol, iNumero3Nietos);
    }
}

template <class T>
int contar3Nietos(Abin<T> abArbol)
{
    if (abArbol.arbolVacio())
        return 0;
    else
    {
        int iNumero3Nietos = 0;
        contar3NietosRec(abArbol.raiz(), abArbol, iNumero3Nietos);
        return iNumero3Nietos;
    }
}

/**
 * Dado un árbol A y un valor x, compruebe si dicho valor se encuentra o no en el árbol.
 * Si es así, devuelva el camino desde el nodo raíz hasta dicho nodo.
 * Puede suponer que no hay ningún elemento repetido en el árbol que
 * recibe como parámetro.
 */
template <class T>
bool encuentraElemento(typename Abin<T>::nodo nd, Abin<T> &abArbol, const T &elemento, bool &bFound, pair<bool, typename Abin<T>::nodo> &pairRes)
{
    if (nd != Abin<T>::NODO_NULO && !bFound)
    {
        bFound = abArbol.elemento(nd) == elemento;
        if (bFound)
        {
            pairRes.first = bFound;
            pairRes.second = nd;
        }

        return bFound || encuentraElemento(abArbol.hijoIzqdo(nd), abArbol, elemento, bFound, pairRes) || encuentraElemento(abArbol.hijoDrcho(nd), abArbol, elemento, bFound, pairRes);
    }
    else
        return false;
}

template <class T>
void construyeCamino(std::vector<T> &aTCamino, typename Abin<T>::nodo nd, Abin<T> &abArbol)
{
    if (nd != abArbol.raiz())
    {
        T tElto = abArbol.elemento(nd);
        aTCamino.emplace(aTCamino.begin(), tElto);
        construyeCamino(aTCamino, abArbol.padre(nd), abArbol);
    }
}

template <class T>
std::vector<T> caminoElemento(const T &elemento, Abin<T> &abArbol)
{
    vector<T> aCamino;
    bool bFound = false;
    pair<bool, typename Abin<T>::nodo> pairRes(bFound, abArbol.raiz());
    if (encuentraElemento(pairRes.second, abArbol, elemento, bFound, pairRes))
    {

        construyeCamino(aCamino, pairRes.second, abArbol);
    }
    return aCamino;
}

/**
 * Examen de Arboles:
 * Un árbol es estrictamente ternario si todos sus nodos son hojas o tienen tres hijos.
 * Escribe una función que, dado un árbol de grado arbitrario, nos indique si es o no
 * estrictamente ternario.
 */

/**
 * @brief Cuenta los nodos del hijo dado
 * @param Agen<T>
 * @param Agen<T>::nodo
 * @return int
 */
template <class T>
void cuentaHijosAgen(Agen<T> AgArbol, typename Agen<T>::nodo nd, int &iHijos)
{
    if (nd != Agen<T>::NODO_NULO)
    {
        nd = AgArbol.hijoIzqdo(nd);
        while (nd != Agen<T>::NODO_NULO)
        {
            cuentaHijosAgen(AgArbol, nd, iHijos);
            iHijos++;
            // cout << AgArbol.elemento(nd)<<", "<<std::endl;
            nd = AgArbol.hermDrcho(nd);
        }
    }
}

template <class T>
bool esNodoTernario(Agen<T> AgArbol, typename Agen<T>::nodo nd)
{
    if (nd == Agen<T>::NODO_NULO)
    {
        return true; // El nodo vacio es considerado como ternario ya que es hoja
    }
    else
    {
        int iHijosNodoActual = 0;
        cuentaHijosAgen(AgArbol, nd, iHijosNodoActual);
        return (AgArbol.hijoIzqdo(nd) == Agen<T>::NODO_NULO || iHijosNodoActual == 3 || iHijosNodoActual == 0);
    }
}

template <class T>
void esTernarioRec(Agen<T> AgArbol, typename Agen<T>::nodo nd, bool &bTernario)
{
    if (nd != Agen<T>::NODO_NULO && bTernario)
    {
        // Comprobamos en preorden
        bTernario = esNodoTernario(AgArbol, nd);

        nd = AgArbol.hijoIzqdo(nd);
        while (nd != Agen<T>::NODO_NULO)
        {
            esTernarioRec(AgArbol, nd, bTernario);
            nd = AgArbol.hermDrcho(nd);
        }
    }
}

template <class T>
bool esArbolTernario(Agen<T> AgArbol)
{
    if (AgArbol.arbolVacio())
        return true;
    else
    {
        bool bEsArbolTernario = true;
        esTernarioRec(AgArbol, AgArbol.raiz(), bEsArbolTernario);
        return bEsArbolTernario;
    }
}

int main()
{
    Agen<int> A;
    A.insertaRaiz(1);
    A.insertarHijoIzqdo(A.raiz(), 2);
    A.insertarHermDrcho(A.hijoIzqdo(A.raiz()), 3);
    A.insertarHermDrcho(A.hijoIzqdo(A.raiz()), 4);
    std::cout << esArbolTernario(A) << std::endl;
    return 0;
}
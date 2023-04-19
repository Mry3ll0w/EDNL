#include <iostream>
#include <vector>
#include "abb.h"
#include "arbolbinenla.h"
#include "agenEnlazado.h"
using namespace std; // Avoid using std:: ....

// Contar numero de nodos del arbol que tienen exactamente 3 nietos

template <class T>
int profundidadNodoAgen(Agen<T> AgArbol, typename Agen<T>::nodo nd)
{
    if (nd == AgArbol.raiz())
    {
        return 0;
    }
    else
    {
        return 1 + profundidadNodoAgen(AgArbol, AgArbol.padre(nd));
    }
}

template <class T>
void cuentaNietosNodoAgen(Agen<T> AgArbol, typename Agen<T>::nodo nd, int &iNietos, const int iProfundidadNodoDado)
{
    if (nd != Agen<T>::NODO_NULO && profundidadNodoAgen(AgArbol, nd) - iProfundidadNodoDado <= 2)
    {
        nd = AgArbol.hijoIzqdo(nd);

        while (nd != Agen<T>::NODO_NULO)
        {
            cuentaNietosNodoAgen(AgArbol, nd, iNietos, iProfundidadNodoDado);

            if (std::abs(profundidadNodoAgen(AgArbol, nd) - iProfundidadNodoDado) == 2)
                iNietos++;

            nd = AgArbol.hermDrcho(nd);
        }
    }
}

template <class T>
void cuentaNodosTresNietosHojasAgen(Agen<T> AgArbol, typename Agen<T>::nodo nd, int &iNodosTresNietosHojas)
{
    if (nd != Agen<T>::NODO_NULO)
    {
        nd = AgArbol.hijoIzqdo(nd);

        while (nd != Agen<T>::NODO_NULO)
        {
            cuentaNodosTresNietosHojasAgen(AgArbol, nd, iNodosTresNietosHojas);

            int iNumeroNietos = 0, iProfundidadNodoDado = profundidadNodoAgen(AgArbol, nd);

            cuentaNietosNodoAgen(AgArbol, nd, iNumeroNietos, iProfundidadNodoDado);

            if (iNumeroNietos == 3 || AgArbol.hijoIzqdo(nd) == Agen<T>::NODO_NULO) // 3 nietos u hoja
                iNodosTresNietosHojas++;

            nd = AgArbol.hermDrcho(nd);
        }
    }
}

template <class T>
int numNodos3NietosHojasAgen(Agen<T> AgArbol)
{
    if (AgArbol.arbolVacio())
        return 0;
    else
    {
        int iNodos3NietosHojas = 0;
        cuentaNodosTresNietosHojasAgen(AgArbol, AgArbol.raiz(), iNodos3NietosHojas);
        return iNodos3NietosHojas;
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

/**
 * Tener el  doble de nietos que de bisnietos.
 *
 * Sera Un nieto cuando la profundidad: sea Abs(profundidad NodoOriginal - profNd) = 2
 */

/**
 * @brief Cuenta el numero de nodos Nietos del nodo dado.
 */

template <class T>
int profundidadNodoAgen(Agen<T> AgArbol, typename Agen<T>::nodo nd)
{
    if (nd == AgArbol.raiz())
    {
        return 0;
    }
    else
        return 1 + profundidadNodoAgen(AgArbol, AgArbol.padre(nd));
}

template <class T>
void cuentaNietosYBisnietos(const Agen<T> AgArbol, typename Agen<T>::nodo nd, const int &iProfundidadOriginal, int &iNietos, int &iBisNietos)
{
    if (nd != Agen<T>::NODO_NULO)
    {
        nd = AgArbol.hijoIzqdo(nd);

        while (nd != Agen<T>::NODO_NULO)
        {
            cuentaNietosYBisnietos(AgArbol, nd, iProfundidadOriginal, iNietos, iBisNietos);

            int iDifProfundidad = std::abs(iProfundidadOriginal - profundidadNodoAgen(AgArbol, nd));

            if (iDifProfundidad == 2)
                iNietos++;

            if (iDifProfundidad == 3)
                iBisNietos++;

            nd = AgArbol.hermDrcho(AgArbol, nd, iProfundidadOriginal, iNietos);
        }
    }
}

template <class T>
bool tieneDobleNietosQueBisnietosAgen(Agen<T> AgArbol)
{
    if (AgArbol.arbolVacio())
        return false;
    else
    {
        int iNietos = 0, iBisNietos = 0;
        // He asumido que la profundidad original es la raiz pero como no se especifica lo dejo en el cuentaNietosBisnietos
        cuentaNietosYBisnietos(AgArbol, AgArbol.raiz(), 0, iNietos, iBisNietos);
        return iBisNietos * 2 == iNietos;
    }
}

/**
 * Nodos reflejos. Dos nodos son reflejos cuando, siendo hermanos entre si, son las raíces de dos árboles (subárboles si queréis)
 * que son reflejados entre sí. La definición de un árbol reflejado la conocéis de las prácticas,
 * entendemos reflejado como la imagen especular.
 */

template <class T>
void esReflejadoRec(const Abin<T> AbArbol1, const Abin<T> AbArbol2, typename Abin<T>::nodo nd1, typename Abin<T>::nodo nd2, bool &bEsReflejado)
{
    if (nd1 != Abin<T>::NODO_NULO && nd2 != Abin<T>::NODO_NULO && bEsReflejado)
    {
        esReflejadoRec(AbArbol1, AbArbol2, AbArbol1.hijoIzqdo(nd1), AbArbol2.hijoDrcho(nd2), bEsReflejado);

        // Comprobamos que sea reflejo
        bEsReflejado = AbArbol1.elemento(nd1) == AbArbol2.elemento(nd2);

        esReflejadoRec(AbArbol1, AbArbol2, AbArbol1.hijoDrcho(nd1), AbArbol2.hijoIzqdo(nd2), bEsReflejado);
    }
}
template <class T>
bool esArbolReflejado(const Abin<T> AbArbol1, const Abin<T> AbArbol2)
{

    if (AbArbol1.arbolVacio() == AbArbol2.arbolVacio() && AbArbol1.elemento(AbArbol1.raiz()) == AbArbol2.elemento(AbArbol2.raiz()))
    {
        return true; // si ambos son vacios se consideran reflejos
    }
    else if (AbArbol1.arbolVacio() != AbArbol2.arbolVacio())
    { // Si uno esta vacio y el otro no entonces no son reflejos
        return false;
    }
    else
    { // Caso general
        bool bEsReflejado = true;
        esReflejadoRec(AbArbol1, AbArbol2, AbArbol1.raiz(), AbArbol2.raiz(), bEsReflejado);
        return bEsReflejado;
    }
}

/**
 * Ser nostálgicos. Definimos un nodo nostálgico como aquel que tiene más pasado que futuro,
 * es decir son los nodos que tienen más antecesores propios que descendientes propios.
 */

template <class T>
int cuentaAntecesoresAbin(Abin<T> AbArbol, typename Abin<T>::nodo nd)
{
    if (nd != AbArbol.raiz())
    {
        return 1 + cuentaAntecesoresAbin(AbArbol, AbArbol.padre(nd));
    }
}

template <class T>
int cuentaPredecesoresAbin(Abin<T> AbArbol, typename Abin<T>::nodo nd)
{
    if (nd == Abin<T>::NODO_NULO)
    {
        return 0;
    }
    else
    {
        return 1 + cuentaPredecesoresAbin(AbArbol, AbArbol.hijoDrcho(nd)) + cuentaPredecesoresAbin(AbArbol, AbArbol.hijoIzqdo(nd));
    }
}

template <class T>
void cuentaNostalgicosRec(Abin<T> AbArbol, typename Abin<T>::nodo nd, int &iNodosNostalgicos)
{
    if (nd != Abin<T>::NODO_NULO)
    {
        int iPasado = 0, iFuturo = 1;
        iPasado = cuentaAntecesoresAbin(AbArbol, nd);
        iFuturo = cuentaPredecesoresAbin(AbArbol, nd);

        if (iPasado > iFuturo)
            iNodosNostalgicos++;

        cuentaNostalgicosRec(AbArbol, AbArbol.hijoIzqdo(nd));
        cuentaNostalgicosRec(AbArbol, AbArbol.hijoDrcho(nd));
    }
}

template <class T>
int cuentaNostalgicosAbin(Abin<T> AbArbol)
{
    if (AbArbol.arbolVacio())
        return 0;
    else
    {
        int iNostalgicos = 0;
        cuentaNostalgicosRec(AbArbol, AbArbol.raiz(), iNostalgicos);
        return iNostalgicos;
    }
}

/**
 * Examen Infimo y Supremo.
 * Infimo es el menor elemento de A <= X, siendo A el Abb
 * Supremo es el mayor elemento de A < X, siendo A el Abb
 */

int infimoAbb(Abb<int> AbbArbol, const int &iX, int &iInfimo)
{
    if (AbbArbol.elemento() == iX)
    {
        iInfimo = AbbArbol.elemento();
    }
    else
    {
        if (AbbArbol.elemento() < iX)
        {
            iInfimo = std::max(iInfimo, AbbArbol.elemento()); // Sabiendo que es menor no va a sobre pasar a x
            infimoAbb(AbbArbol.izqdo(), iX, iInfimo);
        }

        if (AbbArbol.elemento() > iX)
        {
            infimoAbb(AbbArbol.drcho(), iX, iInfimo);
        }
    }
    return iInfimo;
}

int supremoAbb(Abb<int> AbbArbol, const int &iX, int &iSupremo)
{
    if (AbbArbol.elemento() == iX)
    {
        iSupremo = AbbArbol.elemento();
    }
    else
    {
        if (AbbArbol.elemento() > iX)
        {
            iSupremo = std::min(iSupremo, AbbArbol.elemento()); // Ya que sabemos que el elemento actual supera a iX
            supremoAbb(AbbArbol.izqdo(), iX, iSupremo);
        }

        if (AbbArbol.elemento() < iX)
        {
            supremoAbb(AbbArbol.drcho(), iX, iSupremo);
        }
    }
    return iSupremo;
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
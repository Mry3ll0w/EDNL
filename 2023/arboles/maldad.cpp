#include <iostream>
#include "abin_enla.h"
#include <vector>
#include <string>
using namespace std; // Avoid using std:: ....

template <class T>
int sumaNodosRaiz(Abin<T> AbArbol, typename Abin<T>::nodo nd)
{
    if (nd == Abin<T>::NODO_NULO)
    {
        return 0;
    }
    else
    {
        return AbArbol.elemento(nd) + sumaNodosRaiz(AbArbol, AbArbol.hijoDrcho(nd), AbArbol.hijoIzqdo(nd));
    }
}

// Recibe el abol copiado del original
template <class T>
void createArbolSumaNodosRec(Abin<T> AbOrigen, Abin<T> &AbDestino, typename Abin<T>::nodo nd1, typename Abin<T>::nodo nd2)
{
    if (nd1 != Abin<T>::NODO_NULO && nd2 != Abin<T>::NODO_NULO)
    {
        AbDestino.elemento(nd2) = sumaNodosRaiz(AbOrigen, nd1);
        createArbolSumaNodosRec(AbOrigen, AbDestino, AbOrigen.hijoIzqdo(nd1), AbDestino.hijoIzqdo(nd2));
        createArbolSumaNodosRec(AbOrigen, AbDestino, AbOrigen.hijoDrcho(nd1), AbDestino.hijoDrcho(nd2));
    }
}

template <class T>
Abin<T> createArbolSumaNodos(const Abin<T> AbArbol)
{
    if (AbArbol.arbolVacio())
    {
        return Abin<T>();
    }
    else
    {
        Abin<T> AbSuma = AbArbol;
        createArbolSumaNodosRec(AbArbol, AbSuma, AbArbol.raiz(), AbSuma.raiz());
        return AbSuma;
    }
}

// Nunca voy a recibir nodo Nulo, se controla antes
template <class T>
bool esNodoReflejadoAbin(Abin<T> AbArbol1, Abin<T> AbArbol2, typename Abin<T>::nodo nd1, typename Abin<T>::nodo nd2)
{
    if (nd1 == Abin<T>::NODO_NULO && nd2 == Abin<T>::NODO_NULO)
    {
        return true;
    }
    else
    {
        // Compruebo que sean hojas
        if (
            (AbArbol1.hijoIzqdo(nd1) == Abin<T>::NODO_NULO && AbArbol1.hijoDrcho(nd1) == Abin<T>::NODO_NULO) &&
            (AbArbol2.hijoDrcho(nd2) == Abin<T>::NODO_NULO && AbArbol2.hijoDrcho(nd2) == Abin<T>::NODO_NULO))
        {
            return true;
        }
        else // No son hojas, compruebo ramificación e igualdad
        {
            if (
                AbArbol1.elemento(AbArbol1.hijoIzqdo(nd1)) == AbArbol2.elemento(AbArbol2.hijoDrcho(nd2)) &&
                (AbArbol1.hijoDrcho(nd1) == Abin<T>::NODO_NULO && AbArbol2.hijoIzqdo(nd2) == Abin<T>::NODO_NULO))
            {
                return true;
            }
            else if (
                AbArbol1.elemento(AbArbol1.hijoDrcho(nd1)) == AbArbol2.elemento(AbArbol2.hijoIzqdo(nd2)) &&
                (AbArbol1.hijoIzqdo(nd1) == Abin<T>::NODO_NULO && AbArbol2.hijoDrcho(nd2) == Abin<T>::NODO_NULO))
            {
                return true;
            }
            else if (
                AbArbol1.elemento(AbArbol1.hijoIzqdo(nd1)) == AbArbol2.elemento(AbArbol2.hijoDrcho(nd2)) &&
                AbArbol1.elemento(AbArbol1.hijoDrcho(nd1)) == AbArbol2.elemento(AbArbol2.hijoIzqdo(nd2)))
            { // Arbol completo, si no son los de arriba esta completo
                return true;
            }
            else
            {
                return false;
            }
        }
    }
}

template <class T>
void esReflejadoSumaRec(Abin<T> AbArbol1, Abin<T> AbArbol2, typename Abin<T>::nodo nd1, typename Abin<T>::nodo nd2, bool &bCondicion)
{
    if (nd != Abin<T>::NODO_NULO && bCondicion)
    {
        if (!esNodoReflejadoAbin(AbArbol1, AbArbol2, nd1, nd2))
        {
            bCondicion = false;
        }
        else
        {
            if (AbArbol1.elemento(AbArbol1.hijoDrcho(nd1)) != Abin<T>::NODO_NULO && AbArbol1.elemento(AbArbol1.hijoIzqdo(nd1)) != Abin<T>::NODO_NULO)
            {
                bCondicion = AbArbol1.elemento(nd) > (AbArbol1.elemento(AbArbol1.hijoDrcho(nd1)) + AbArbol1.elemento(AbArbol1.hijoIzqdo(nd1)));
            }
            else
            {
                int iSumaHijos = 0;
                if (AbArbol1.elemento(AbArbol1.hijoIzqdo(nd1)) != Abin<T>::NODO_NULO)
                {
                    iSumaHijos += AbArbol1.elemento(AbArbol1.hijoIzqdo(nd1));
                }

                if (AbArbol1.elemento(AbArbol1.hijoDrcho(nd1)) != Abin<T>::NODO_NULO)
                {
                    iSumaHijos += AbArbol1.elemento(AbArbol1.hijoDrcho(nd1));
                }
                bCondicion = AbArbol1.elemento(nd1) > iSumaHijos;
            }
        }
    }
}

template <class T>
bool esReflejadoSuma(Abin<T> AbArbol1, Abin<T> AbArbol2)
{
    if (AbArbol1.arbolVacio() != AbArbol2.arbolVacio())
    {
        return false;
    }
    else
    {
        bool bCondicion = true;
        esReflejadoSumaRec(AbArbol1, AbArbol2, AbArbol1.raiz(), AbArbol2.raiz(), bCondicion);
        return bCondicion;
    }
}

/**
 * Dado un Abin comprueba que se trata de un AVL.
 * 1) Un AVL es un arbol cuyo factor de desequilibrio de todos los nodos en valor absoluto no supera 1, es decir, la altura
 * de los hijos izquierdo y derecho del arbol no difiere de 1.
 * 2) Todos los nodos cumplen las caracteristicas de un Abb, para cada uno de los nodos pertenecientes al arbol
 * los elementos que componen el subArbolIzquierdo son menores que el nodo y los elementos que componen el subarbol derecho
 * son mayores que el nodo.
 */

template <class T>
bool cumpleAbinAbb(Abin<T> AbArbol, typename Abin<T>::nodo nd, bool &bEsAbb) // Probar dicha condicio con todos los nodos
{
    if (nd != Abin<T>::NODO_NULO && bEsAbb)
    {
        if (AbArbol.hijoDrcho(nd) != Abin<T>::NODO_NULO && AbArbol.hijoIzqdo(nd) != Abin<T>::NODO_NULO)
        {
            bEsAbb = AbArbol.elemento(nd) > AbArbol.elemento(AbArbol.hijoIzqdo(nd)) && AbArbol.elemento(nd) < AbArbol.elemento(AbArbol.hijoDrcho(nd));
        }
        else
        {
            if (AbArbol.hijoDrcho(nd) == Abin<T>::NODO_NULO)
            {
                bEsAbb = AbArbol.elemento(AbArbol.hijoIzqdo(nd)) < AbArbol.elemento(nd);
            }
            if (AbArbol.hijoIzqdo(nd) == Abin<T>::NODO_NULO)
                bEsAbb = AbArbol.elemento(AbArbol.hijoDrcho(nd)) > AbArbol.elemento(nd);
        }
        bEsAbb = cumpleAbinAbb(AbArbol, AbArbol.hijoIzqdo(nd), bEsAbb) && cumpleAbinAbb(AbArbol, AbArbol.hijoDrcho(nd), bEsAbb);
    }
    return bEsAbb;
}

template <class T>
int alturaNodoAbin(Abin<T> AbArbol, typename Abin<T>::nodo nd)
{
    if (nd == Abin<T>::NODO_NULO)
    {
        return -1;
    }
    else
    {
        return 1 + std::max(alturaNodoAbin(AbArbol, AbArbol.hijoIzqdo(nd)), alturaNodoAbin(AbArbol, AbArbol.hijoDrcho(nd)));
    }
}

template <class T>
bool esAbinAVLRec(Abin<T> AbArbol, typename Abin<T>::nodo nd, bool &bEsAVL)
{
    if (nd != Abin<T>::NODO_NULO && bEsAVL)
    {
        int iDifAltura = std::abs(alturaNodoAbin(AbArbol, AbArbol.hijoDrcho(nd)) - alturaNodoAbin(AbArbol, AbArbol.hijoIzqdo(nd)));
        bool bEsAbin = true;
        bEsAbin = cumpleAbinAbb(AbArbol, nd, bEsAbin);

        bEsAVL = iDifAltura <= 1 && bEsAbin;

        bEsAVL = esAbinAVLRec(AbArbol, AbArbol.hijoDrcho(nd), bEsAVL) && esAbinAVLRec(AbArbol, AbArbol.hijoIzqdo(nd), bEsAVL);
    }
    return bEsAVL;
}

template <class T>
bool esAbinAVL(Abin<T> AbArbol)
{
    if (AbArbol.arbolVacio())
    {
        return true;
    }
    else
    {
        bool esAVL = true;
        esAVL = esAbinAVLRec(AbArbol, AbArbol.raiz(), esAVL);
        return esAVL;
    }
}

/**
 * Examen expresiones logicas, definiremos el arbol como un arbol de caracteres.
 *
 * AND = ^
 * OR = |
 * NO = !
 * Tendran valor V si es true y F si es falso
 *
 * ASUMO QUE EL ARBOL DADO ESTA CORRECTAMENTE CONSTRUIDO.
 *
 */

std::string procesaSimbolo(std::string &sSimbolo)
{
    if (sSimbolo.find('S') != std::string::npos)
    {
        return std::string(sSimbolo.begin() + 1, sSimbolo.end());
    }
    else
    {
        return "NaN";
    }
}

void procesaExpresionesSimbolo(Abin<std::string> &AbArbol, typename Abin<std::string>::nodo nd, std::vector<bool> vbSimbolos)
{

    if (nd != Abin<std::string>::NODO_NULO)
    {
        std::string sElementoNodo = procesaSimbolo(AbArbol.elemento(nd));
        if (sElementoNodo != "NaN")
        {
            if (vbSimbolos[std::stoi(sElementoNodo) - 1])
            {
                AbArbol.elemento(nd) = "V";
            }
            else
            {
                AbArbol.elemento(nd) = "F";
            }
        }
        procesaExpresionesSimbolo(AbArbol, AbArbol.hijoIzqdo(nd), vbSimbolos);
        procesaExpresionesSimbolo(AbArbol, AbArbol.hijoDrcho(nd), vbSimbolos);
    }
}

bool simbolosAbinRec(Abin<std::string> AbArbol, typename Abin<std::string>::nodo nd)
{
    if (nd != Abin<std::string>::NODO_NULO)
    {
        if (AbArbol.elemento(nd) == "^")
        {
            return simbolosAbinRec(AbArbol, AbArbol.hijoIzqdo(nd)) && simbolosAbinRec(AbArbol, AbArbol.hijoDrcho(nd));
        }
        else if (AbArbol.elemento(nd) == "|")
        {
            return simbolosAbinRec(AbArbol, AbArbol.hijoIzqdo(nd)) || simbolosAbinRec(AbArbol, AbArbol.hijoDrcho(nd));
        }
        else if (AbArbol.elemento(nd) == "!")
        {
            return !simbolosAbinRec(AbArbol, AbArbol.hijoIzqdo(nd));
        }
        else if (AbArbol.elemento(nd) == "V")
        {
            return true;
        }
        else
        {
            return false;
        }
        }
}

bool simbolosAbin(Abin<std::string> AbArbol, std::vector<bool> vbSimbolos) // Siempre asumo que el arbol esta correctamente creado
{
    // 1 asigno los valores de las expresiones
    procesaExpresionesSimbolo(AbArbol, AbArbol.raiz(), vbSimbolos);
    return simbolosAbinRec(AbArbol, AbArbol.raiz());
}

int main()
{

    return 0;
}
#include <iostream>
#include "../2023/arboles/arbolbinenla.h"
using namespace std; // Avoid using std:: ....

struct Simbolo
{
    char cExpresion;
    bool bValor;
    bool bEsValor;
};

template <class T>
bool procesaSimbolos(Abin<Simbolo> abin, typename Abin<Simbolo>::nodo nd)
{
    if (nd != Abin<Simbolo>::NODO_NULO)
    {
        return true;
    }
    else
    {
        if (abin.elemento(nd).bEsValor)
        {
            return abin.elemento(nd).bValor;
        }
        else if (abin.elemento(nd).cExpresion == '!')
        {
            return procesaSimbolos(abin, abin.elemento(abin.hijoIzqdo(nd)));
        }
        else if (abin.elemento(nd).cExpresion == '&')
        {
            return procesaSimbolos(abin, abin.elemento(abin.hijoIzqdo(nd))) && procesaSimbolos(abin, abin.elemento(abin.hijoDrcho(nd)));
        }
        else if (abin.elemento(nd).cExpresion == '|')
        {
            return procesaSimbolos(abin, abin.elemento(abin.hijoIzqdo(nd))) || procesaSimbolos(abin, abin.elemento(abin.hijoDrcho(nd)));
        }
    }
}

int main()
{

    return 0;
}
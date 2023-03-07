#include <iostream>
#include <math.h>
/**
 * Requisitos de la clase
 * Tratamos de representar un arbol binario mediante un vector de posiciones
 * relativas.
 * 1) Constructor del arbol en funcion a la altura, ctor según altura
 * 2)
 */
template <class T>
class AbinRel
{
    int iAltura_;
    int iSizeVector_;
    T *aElementos;

public:
    // gestion de excepciones
    explicit AbinRel(const int &iAltura)
    {
        if (iAltura < 0)
        {
            throw std::invalid_argument("La altura tiene que ser >= 0");
        }
        iAltura_ = iAltura;
        iSizeVector_ = pow(2, iAltura + 1) - 1;
        aElementos = new T[iSizeVector_];
    }

    void insertarRaiz(const T &tElemento)
    {
        aElementos[iSizeVector_ / 2] = tElemento;
    }

    ~AbinRel()
    {
        delete[] aElementos;
    }
};

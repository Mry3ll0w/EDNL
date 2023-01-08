#include <iostream>
#include "Agen.h"

using namespace std; // Avoid using std:: ....

/**
 * Se define la densidad como : El grado maximo del árbol dividido por el numero de nodos 
 * hojas que existen en el mismo.
 * @Mry3ll0w
 */

/**
 * @brief Determina si un nodo de un arbol dado es un nodo hoja.
 * @return true
 * @param typename Agen<T>::nodo n, const Agen<T>& A
 */
template <class T>
bool es_hoja(typename Agen<T>::nodo n, const Agen<T> &A){

    if(A.hijoIzqdo(n) == Agen<T>::NODO_NULO)
        return true;
    else    
        return false;

}

/**
 * @brief Funcion para calcular cual es el numero de nodos hojas que existen en un árbol
 * general dado.
 * @param typename Agen<T>::nodo n, int& n_hojas, const Agen<T>& A
 * @return none
 */
template <class T>
void n_hojas_agen(typename Agen<T>::nodo n, int& n_hojas, const Agen<T> &A){
    if(n != Agen<T>::NODO_NULO){

        if (es_hoja(n, A))
        {
            n_hojas++;
        }
        n = A.hijoIzqdo(n);
        while(n != Agen<T>::NODO_NULO){
            n_hojas_agen(n,n_hojas,A);
            n = A.hermDrcho(n);
        }
    }
}

/**
 * @brief Cuenta hijos del nodo actual
 * @return int
 * @param typename Agen<T>::nodo n, const Agen<T> &A
 */
template <class T>
int cuenta_hijos(typename Agen<T>::nodo n, const Agen<T> &A){
    if(n == Agen<T>::NODO_NULO){
        return 0;
    }
    return 1 + cuenta_hijos(A.hermDrcho(n),A);
}

/**
 * @brief Funcion para calcular el grado del arbol general.
 * @return none
 * @param typename Agen<T>::nodo n, int& grado, const Agen<T> &A
 */
template <class T>
void grado_agen(typename Agen<T>::nodo n, int &grado, const Agen<T> &A){
    
    if(n != Agen<T>::NODO_NULO){
        cout << cuenta_hijos(A.hijoIzqdo(n),A)<<", ";
        grado = max(grado, cuenta_hijos(A.hijoIzqdo(n), A));
        
        n = A.hijoIzqdo(n);
        
        while ( n != Agen<T>::NODO_NULO){
            grado_agen(n, grado, A);
            n = A.hermDrcho(n);
        }

        
    }

}

/**
 * @brief Calcula la densidad del arbol dado.
 * @return int
 * @param const Agen<T>& A
 */
template <class T>
double& densidad(const Agen<T>& A){
    unsigned g=0, hojas=0;
    grado_agen(A.raiz(),g, A);
    n_hojas_agen(A.raiz(),hojas,A);
    return g/hojas; 
}

int main()
{
    Agen<int> A;
    A.insertaRaiz(1);
    A.insertarHijoIzqdo(A.raiz(), 2);
    A.insertarHermDrcho(A.hijoIzqdo(A.raiz()), 3);
    A.insertarHermDrcho(A.hijoIzqdo(A.raiz()), 4);
    A.insertarHijoIzqdo(A.hermDrcho(A.hijoIzqdo(A.raiz())), 5);
    A.insertarHermDrcho(A.hijoIzqdo(A.hermDrcho(A.hijoIzqdo(A.raiz()))), 6);
    A.insertarHermDrcho(A.hijoIzqdo(A.hermDrcho(A.hijoIzqdo(A.raiz()))), 7);
    A.insertarHermDrcho(A.hijoIzqdo(A.hermDrcho(A.hijoIzqdo(A.raiz()))), 8);

    int g = 0;
    grado_agen(A.raiz(),g,A);
    cout << g <<endl;
    return 0;
}

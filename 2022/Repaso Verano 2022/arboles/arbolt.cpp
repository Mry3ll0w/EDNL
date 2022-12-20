#include <iostream>
#include "abin_enla.h"

using namespace std;//Avoid using std:: ....

/**
 * Enunciado del examen:
 *
 * Considere los árboles binarios no vacíos cuyos nodos contienen números enteros. 
 * Sea 𝑇 un árbol binario de este tipo. Se dice que 𝑇 es impar si, para cualquier 
 * nodo 𝑛∈𝑇, el número de nodos que contienen números impares es idéntico en el 
 * subárbol izquierdo de 𝑛 y en el subárbol derecho de 𝑛.
 */

/**
 * @brief Cuenta el numero de nodos impares en el subarbol dado
 * @param Abin<int>::nodo n ,int & n_impares, const Abin<int> & A
 * @return none
 */
void cuenta_nodos_impares(Abin<int>::nodo n, int &n_impares, const Abin<int> &A){
    if(n != Abin<int>::NODO_NULO){

        if (A.elemento(n) % 2 != 0)
        {
            // Es impar
            n_impares++;
        }
        cuenta_nodos_impares(A.hijoIzqdo(n), n_impares, A);
        cuenta_nodos_impares(A.hijoDrcho(n), n_impares, A);
    }
}

/**
 * @brief Funcion Principal del algoritmo, para determinar si es tipo t o no lo es,
 * devuelve true si es un arbol tipo t y false si no lo es
 * @param const Abin<int>& A
 * @return bool
 */
bool es_arbol_t(const Abin<int>&A){

    if(A.arbolVacio()){
        return false;//Un arbol vacio no es un tipo T segun el enunciado
    }
    else{//No es vacio, por tanto puede ser un tipo T

        int impares_sub_derecho, impares_sub_izquierdo;
        impares_sub_derecho = impares_sub_derecho = 0;

        cuenta_nodos_impares(A.hijoDrcho(A.raiz()),impares_sub_derecho,A);
        cuenta_nodos_impares(A.hijoIzqdo(A.raiz()), impares_sub_izquierdo, A);

        return impares_sub_derecho == impares_sub_izquierdo;

    }
}


    int main()
{

    return 0;
}
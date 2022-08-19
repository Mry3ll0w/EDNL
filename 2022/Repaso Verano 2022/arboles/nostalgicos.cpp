#include <iostream>
#include "abin_enla.h"

using namespace std;//Avoid using std:: ....
// ENUNCIADO
/**
 * Se pide hallar el numero de nodos nostalgicos que existen en un árbol dado.
 * Es nodo nostálgico (comprobando que tiene mayor número de antecesores que de sucesores)
 */

/**
 * @brief Contamos los descendientes a partir del nodo dado
 * @return int
 * @param typename Abin<T>::nodo n, const Abin<T> &A
 */
template <class T>
int cuenta_hijos(typename Abin<T>::nodo n, const Abin<T> &A){

    if(n == Abin<T>::NODO_NULO){
        return -1;
    }
    else
        return 1 + cuenta_hijos(A.hijoDrchoB(n),A) + cuenta_hijos(A.hijoIzqdoB(n),A);

}

/**
 * @brief Cuenta el numero de antecesores que tiene el nodo.
 * @return int
 * @param typename Abin<T>::nodo n, const Abin<T> &A
 */
template <class T>
int cuenta_antecesores(typename Abin<T>::nodo n, const Abin<T> &A){

    if(n == A.raizB())
        return -1;
    else
        return 1 + cuenta_antecesores(A.hijoDrchoB(n),A) + cuenta_antecesores(A.hijoIzqdoB(n),A);
}

/**
 * @brief Determina si un nodo puede ser llamado como nostalgico, es decir,
 * el numero de hijos es menor al numero de predecesores.
 * @return true
 */
template <class T>
bool es_nostalgico(typename Abin<T>::nodo n, const Abin<T> &A){
    return cuenta_antecesores(n, A) > (cuenta_hijos(n,A)-1);//-1 ya que se cuenta a el mismo como tal
}

/**
 * @brief Cuenta el numero de nodos nostálgicos que existen en el árbol
 * @return none
 * @param typename Abin<T>::nodo n, const Abin<T> &A, int& n_nostalgicos
 *  
 */
template <class T>
void nostalgicos_rec(typename Abin<T>::nodo n, const Abin<T> &A, int& n_nostalgicos)
{
    if(n != Abin<T>::NODO_NULO){
        
        if(es_nostalgico(n,A))
            n_nostalgicos ++;
        
        nostalgicos_rec(A.hijoDrchoB(n),A, n_nostalgicos);
        nostalgicos_rec(A.hijoIzqdoB(n),A,n_nostalgicos);
    }

}

/**
 * @brief Llamada incial al algoritmo de nostalgicos, este recibe solo el arbol.
 * @param const Abin<T> &A
 * @return int
 */
template <class T>
int nostalgicos(const Abin<T> &A){
    
    if(A.arbolVacioB())
        return 0;
    else{
        int n = 0;
        nostalgicos_rec(A.raizB(), A,n);
        return n;
    }
}

int main()
{

    return 0;
}
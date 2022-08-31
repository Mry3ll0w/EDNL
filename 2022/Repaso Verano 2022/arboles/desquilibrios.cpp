#include <iostream>
#include "abb.h"
#include <climits>
#include "abin_enla.h"
#include "Agen.h"

using namespace std;//Avoid using std:: ....

/**
 * @brief Funcion para obtener la altura de un nodo de un árbol general
 * @param const typename Agen<T>::nodo n, const Agen<T>& A
 * @return int 
 */
template <class T>
int altura_sub_agen(const typename Agen<T>::nodo n, const Agen<T>& A){
    
    int altura = -99;
    typename Agen<T>::nodo aux;
    if(n != Agen<T>::NODO_NULO){
        aux = A.hijoIzqdo(n);
    }
    
    while(aux != Agen<T>::NODO_NULO){

        altura = max(altura, 1 + altura_agen(aux, A));

        aux = A.hermDrcho(aux); 
    }

return altura;//Devolvemos la altura una vez este calculada
}

/**
 * @brief Desequilibrio del nodo dado de un arbol general
 * @param typename Agen<T>::nodo n,const Agen<T>& A
 * @return int
 */
template <class T>
int desequilibrio_agen(typename Agen<T>::nodo n, const Agen<T> &A){

    int des = 0, rama_menor_longitud = INT_MAX;
    typename Agen<T>::nodo aux ;
    if(n != Agen<T>::NODO_NULO){
        aux = A.hijoIzqdo(n);
    }

    while(aux != Agen<T>::NODO_NULO){
        
        int altura_agen = altura_sub_agen(aux, A);

        rama_menor_longitud = min(altura_agen, rama_menor_longitud);
        
        aux = A.hermDrcho(aux);
    }

    //Calculamos el desequilibrio , rama de mayor longitud (raiz del nodo) - menor longitud
    return abs(altura_sub_agen(A.raiz(),A) - rama_menor_longitud);

}

/**
 * @brief Altura de un abin dado un nodo y un arbol binario
 * @param typename Abin<T>::nodo n, const Abin<T>& A
 * @return int
 */
template <class T>
int altura_sub_arbol_abin(typename Agen<T>::nodo n, const Agen<T> &A){

}

int main()
{

    return 0;
}
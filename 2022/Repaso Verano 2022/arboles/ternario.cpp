#include <iostream>
#include "Agen.h"
using namespace std;//Avoid using std:: ....

/**
 * @brief Cuenta el numero de nodos en el nivel dado.
 * @return int
 * @param typename Agen<T>::nodo n, const Agen<T>& A
 */
template <class T>
int cuenta_nodos_nivel(typename Agen<T>::nodo n, const Agen<T> &A){
    
    if(n == Agen<T>::NODO_NULO){
        return 0;
    }
    return 1 + cuenta_nodos_nivel(A.hermDrcho(n), A);

}

/**
 * @brief Algoritmo principal, que determina si se trata de un arbol cuya descendencia es 
 * ternaria.
 * @return none 
 * @param typename Agen<T>::nodo n, const Agen<T>& A, bool & ternario
 */
template <class T>
void es_ternario_rec(typename Agen<T>::nodo n, bool &ternario, const Agen<T> &A){

    if(n != Agen<T>::NODO_NULO){

        auto h_iz = A.hijoIzqdo(n);

        while(h_iz != Agen<T>::NODO_NULO){
            
            if(A.hijoIzqdo(h_iz) != Agen<T>::NODO_NULO){//No contamos los nodos si no hay descendientes
                es_ternario_rec(h_iz, ternario, A);
            }

            h_iz = A.hermDrcho(h_iz);
        }

        cout <<"Elemento "<<A.elemento(n)<<endl;
        size_t nivel = cuenta_nodos_nivel(A.hijoIzqdo(n), A);
        cout <<nivel<<endl;

        if (nivel != 3)
            ternario = false;
    }

}

/**
 * @brief Funcion llamada del algoritmo principal
 * @param const Agen<T> &A 
 * @return bool
 */
template <class T>
bool es_ternario(const Agen<T> &A){
    bool t = true;
    if(A.arbolVacio())
        return false;
    else{
        es_ternario_rec(A.raiz(), t, A);
        return t;
    }
}

int main()
{
    Agen<int> A;
    A.insertarRaiz(1);
    A.insertarHijoIzqdo(A.raiz(),2);
    A.insertarHermDrcho(A.hijoIzqdo(A.raiz()),3);
    A.insertarHermDrcho(A.hijoIzqdo(A.raiz()),4);
    A.insertarHijoIzqdo(A.hermDrcho(A.hijoIzqdo(A.raiz())),5);
    A.insertarHermDrcho(A.hijoIzqdo(A.hermDrcho(A.hijoIzqdo(A.raiz()))), 6);
    
    cout<<es_ternario(A)<<endl;;


    return 0;
}

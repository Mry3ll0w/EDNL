#include <iostream>
#include "Agen.h"
using namespace std;//Avoid using std:: ....

template <typename T>
void postordenAgen(typename Agen<T>::nodo n, const Agen<T>& A,
    void (*procesar)(typename Agen<T>::nodo, const Agen<T>&))
// Recorrido en postorden del subárbol cuya raíz es el nodo n
// perteneciente al árbol A. Cada nodo visitado se procesa mediante // la función procesar().
{
    if (n != Agen<T>::NODO_NULO) {

    typename Agen<T>::nodo hijo = A.hijoIzqdo(n); //Comenzamos con el hijo izq

        while (hijo != Agen<T>::NODO_NULO) {//Procesamos los hermanos derechos
            postordenAgen(hijo, A, procesar);
            hijo = A.hermDrcho(hijo);
        }
            procesar(n, A);
    }
}
//Dado un arbol general que nos calcule su grado

template <class t>
int cuenta_hermanos_rec(typename Agen<t>::nodo n, Agen<t>&A)
{

    if (n != Agen<t>::NODO_NULO)
    {
        return 1+ cuenta_hermanos_rec(A.hermDrcho(n),A);
    }
    else
        return 0;

}

//El grado del árbol se define como el numero maximo de hijos que tiene un nodo del arbol
template<class t>
int grado_arbol_rec(typename Agen<t>::nodo n, Agen<t>&A)
{
    //Comenzamos por el hijo izquierdo de la raiz
    unsigned grado = cuenta_hermanos_rec(n,A);
    
    if (n != Agen<t>::NODO_NULO)
    {
        
        while(n != Agen<t>::NODO_NULO){

            //Iteramos los hermanos derechos
            auto n_der = A.hermDrcho(n);
            while(n_der != Agen<t>::NODO_NULO){
                auto g_act = cuenta_hermanos_rec(A.hijoIzqdo(n_der), A);

                if(grado < g_act)
                    grado = g_act;

                n_der = A.hermDrcho(n_der);
            }

            n = A.hijoIzqdo(n);
        }

    }
    
return grado;    
}

/**
 * @brief Calcula la profundidad de un nodo, dado un Arbol y un nodo del mismo
 * @param typename Agen<T>::nodo n,const Agen<T>& A
 * @return profundidad(int)
 */
template <class T>
int profundidad_nodo(typename Agen<T>::nodo n, const Agen<T>& A){
    if(n == A.raiz())
        return -1;
    return 1 + profundidad_nodo(A.padre(n), A);
}



/**
 * @brief Algoritmo para calcular la altura del subarbol de un nodo concreto
 * @param typename Agen<T>::nodo n, const Agen<T>& A
 * @return int altura
 */
template <class T>
int altura_subarbol(typename Agen<T>::nodo& n, Agen<T>& A){

    
    
    int max = 0;
    typename Agen<T>::nodo aux = Agen<T>::NODO_NULO;
    
    if( n != Agen<T>::NODO_NULO )
        aux = A.hijoIzqdo(n);
    
    while( aux != Agen<T>::NODO_NULO )
    {
        max = std::max(max, 1 + altura_subarbol(aux,A));
        aux = A.hermDrcho(aux);
    }

    return max;
}

/**
 * @brief Calcula el grado de desequilibrio de un arbol dado un Arbol A y un Nodo del mismo
 * @param const typename Agen<T>::nodo& n,const Agen<T>& A
 * @return int
 */
template<typename T> 
int desequilibrioAgenRec(const Agen<T>& A,const typename Agen<T>::nodo& n)
{
    if( n == Agen<T>::NODO_NULO || A.hijoIzqdo(A.raiz()) == Agen<T>::NODO_NULO )
        return 0;
    else
    {
        int min = altura_subarbol(A.raiz(),A);//Mete el maximo como desequilibrio
        typename Agen<T>::nodo aux = A.hijoIzqdo(n);//Itera en aux primero los nodos izq

        //Recorre y hace la altura de los hermanos derechos
        while( A.hermDrcho(aux) != Agen<T>::NODO_NULO )
        {   
            min = std::min(min, altura_subarbol(aux,A));
            aux = A.hermDrcho(aux);
        }
        return std::abs(altura_subarbol(A.raiz(),A) - min);
    }
}

/**
 * @brief Busca el elemento de tipo T dentro de un arbol general, el tipo T debe tener 
 * sobrecargado el operador de comparacion.
 * @param typename Agen<T>::nodo n, const Agen<T> A, const T& e
 * @return typename Agen<T>::nodo n
 */
template <class T>
typename Agen<T>::nodo buscarEltoAgenRec(const Agen<T>& A, const T& x, const typename Agen<T>::nodo& n)
{
    if( n == Agen<T>::NODO_NULO )
        return Agen<T>::NODO_NULO;
    else
        if( A.elemento(n) == x )
            return n;
        else
        {
            typename Agen<T>::nodo aux = buscarEltoAgenRec(A, x, A.hijoIzqdo(n));
            if( aux != Agen<T>::NODO_NULO && A.elemento(aux) == x ) return aux;
            else return buscarEltoAgenRec(A, x, A.hermDrcho(n));
        }
}


/**
 * @brief Elimina el subarbol que se encuentra tras el arbol dado, 
 * no y n_it comienzan con el mismo valor 
 * @param Agen<T>::nodo& n, Agen<T>&A 
 */
template<class T>
void poda_sub_arbol(typename Agen<T>::nodo n, Agen<T>&A){
    //Procesamos todo el arbol menos la raiz de sub arbol
    if (n != Agen<T>::NODO_NULO) {
    //Comenzamos con el hijo izq
    while(A.hijoIzqdo(n) != Agen<T>::NODO_NULO )
        {
            poda_sub_arbol(A.hijoIzqdo(n),A);
            A.eliminarHijoIzqdo(n);
        }
        //Si eliminamos los hijos izquierdos estos eliminan todos los derechos, ya que 
        //todos los derechos cuelgan del izquierdo
    }
}

/**
 * @brief Poda del sub arbol cuya raiz sea igual al elemento dado e
 * @param typename Agen<T>::nodo na, typename Agen<T>::nodo nb, Agen<T> A, T e
 * @return void
 */
template <class T>
void poda_rec(typename Agen<T>::nodo n, Agen<T>& A, T e){

    cout<< A.elemento(buscarEltoAgenRec(A, 3, A.raiz()))<<endl;
}


int main(){
    Agen<int> A;
    A.insertaRaiz(1);
    A.insertarHijoIzqdo(A.raiz(), 2);
    A.insertarHermDrcho(A.hijoIzqdo(A.raiz()), 3);
    A.insertarHijoIzqdo(A.hermDrcho(A.hijoIzqdo(A.raiz())), 4);
    
    for(size_t i = 0; i < 4 ; i++ ){
        A.insertarHermDrcho(A.hijoIzqdo(A.hermDrcho(A.hijoIzqdo(A.raiz()))), 5 + i);
    }
    typename Agen<int>::nodo n = A.raiz();
    poda_sub_arbol(A.raiz(),A);
    poda_rec(A.raiz(),A,3);
return 0;
}
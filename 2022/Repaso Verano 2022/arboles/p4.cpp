#include <iostream>
#include "abb.h"
#include <vector>
#include <set>

using namespace std;//Avoid using std:: ....

//Headers
template <class T>
void abb_to_vector(const Abb<T>& A, vector<T>& v);

template<class T> 
Abb<T> equilibra_arbol(const Abb<T>& A);

template<class T>
Abb<T> union_abb(const Abb<T>& A, const Abb<T>&B);

//Main
int main(){
    vector<int> v = {3,4,5,6,234,71};
    
    Abb<int> A, B; 
    
    for (auto i : v){
        A.insertar(i);
        B.insertar(i);
    }

    B.insertar(13);

    union_abb(A,B);
    

return 0;
}

/**
 * @brief Recorrido en inorden de un abb, para obtener los elementos y pasarlos a un vector
 * @param const Abb<T>& A, vector<T>& v
 * @return void
 */
template <class T>
void abb_to_vector(const Abb<T>& A, vector<T>& v){

    if (!A.vacio())
    {
        abb_to_vector(A.izqdo(),v);
        v.push_back(A.elemento());
        abb_to_vector(A.drcho(),v);
    }
    

}

/**
 * @brief Equilibra un arbol binario de busqueda dado el arbol.
 * @param const Abb<T>& A 
 * @return Abb<T> (Arbol equlibrado)
 */
template<class T> 
Abb<T> equilibra_arbol(const Abb<T>& A){
    
    //Auxiliares para el algoritmo
    vector<T> v;
    Abb<T>R;

    abb_to_vector(A,v);

    //Repartimos equitativamente 
    R.insertar(v[v.size()/2]);//Insertamos la mediana

    int it_izq, it_der;

    it_izq = 0;
    it_der = v.size();

    while(it_der > (v.size()/2) || it_izq < (v.size()/2)){

        if (it_izq < v.size()/2)
        {
            R.insertar(v[it_izq]);
            it_izq++;
        }

        if (it_der > v.size()/2)
        {
            R.insertar(v[it_der]);
            it_der --;
        }
        
    }
return R;
}

/**
 * @brief Funcion encargada de insertar los elementos de un Abb en un conjunto de datos set
 * ya que este no permite elementos repetidos dentro del mismo.
 * @param const Abb<T>& A, set<T>& C
 * @return void
 */
template<class T>
void abb_conjunto(const Abb<T>& A , set<T>& C){
    if(!A.vacio()){
        abb_conjunto(A.izqdo(),C);
        C.emplace(A.elemento());
        abb_conjunto(A.drcho(),C);
    }
}

/**
 * @brief Dados dos conjuntos representados mediante árboles binarios de búsqueda, 
 * implementa la operación unión de dos conjuntos que devuelva como resultado otro 
 * conjunto que sea la unión de ambos, representado por un ABB equilibrado.
 * 
 * @param const Abb<T>& A , const Abb<T>&B
 * @return Abb<T> resultado de realizar la union de los dos arboles
 */
template <class T>
Abb<T> union_abb(const Abb<T>& A, const Abb<T>&B){
   
    Abb<T>R;
    set<T> C;
    abb_conjunto(A,C);
    abb_conjunto(B,C);
    
    for(auto i : C)
        R.insertar(i);
    
    return equilibra_arbol(R);
    
}

/**
 * @brief Dados dos conjuntos representados mediante árboles binarios de búsqueda, implementa 
 * la operación intersección de dos conjuntos, que devuelva como resultado otro conjunto que 
 * sea la intersección de ambos. El resultado debe quedar en un árbol equilibrado.
 * @param const Abb<T>& A, const Abb<T>&B
 * @return Abb<T> resultado de la interseccion de los elementos de A y B
 */
template<class T>
Abb<T> interseccion(const Abb<T>& A , const Abb<T>& B){
    vector<T> va,vb;
    set<T> C;
    Abb<T> R;
    
    abb_to_vector(A,va);
    abb_to_vector(B,vb);

    //Hallamos los elementos que coinciden, la interseccion sin repeticion
    for ( auto i : va){
        for(auto j : vb){
            if( i == j)
                C.emplace(i);
        }
    }

    for ( auto i : C)
        R.insertar(i);
    
    return equilibra_arbol(R);

}


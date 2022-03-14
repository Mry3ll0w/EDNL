#include <iostream>
#include <string>
#include <algorithm>
#include <stdlib.h>
#include <cmath>
#include <cassert>


/* -------------------------------------------------------------------------- */
/*                                 EJERCICIO 4                                */
/* -------------------------------------------------------------------------- */

//Crear un arbol binario con la reprensentación dada en el enunciado de la practica

/* -------------------------------------------------------------------------- */
/*                          REPRESENTACION ARBOL BIN                          */
/* -------------------------------------------------------------------------- */
//La pega que tiene el arbol binario implementado es que no funciona de forma correcta con nodos que tengan elementos
//repetidos
template <class t>
class abin_pos_rel{


public:
    
   typedef int nodo; 

    t NODO_NULO;
    abin_pos_rel(const t caracter_nulo, const unsigned int& h = 0):NODO_NULO(caracter_nulo),max_altura(h),
    arr_size(std::pow(2,h+1)-1)
    {
        
        arbol = new t [arr_size];

        for (int i=0; i<arr_size; i++)
            arbol[i] = caracter_nulo;

    }

    void insertar_nodo_raiz(t elto);
    void insertar_hijo_der(const t& elto,const t& padre);
    void insertar_hijo_izq(const t& elto,const t& padre);

    void muestra_vec(){
        std::cout << "size reservado : "<<arr_size<<std::endl;
        for (size_t i = 0; i < arr_size; i++){
            std::cout << arbol[i] << ", ";
        }
        
        std::cout<<std::endl;
    
    }

    int altura_maxima_nodo(t nodo);//IMPLEMENTAR

    ~abin_pos_rel(){delete[] arbol;}
private:

    unsigned int it_altura;
    
    t* arbol;

    int arr_size;

    unsigned int max_altura;

    
};

template <class t>
void abin_pos_rel<t>::insertar_nodo_raiz(t elto){

    //en nodo raiz ira en la posicion [2^(h-1) - 1 ]/2 

    arbol[arr_size/2] = elto;

    
}

template <class t>
void abin_pos_rel<t>::insertar_hijo_der(const t& elto,const t& padre){

    int n_pos = 0;

    for (; n_pos < arr_size && padre != arbol[n_pos]; ++n_pos);

    if (n_pos < arr_size){ // lo ha encontrado
        
        arbol[ n_pos + (int)(std::pow(2,max_altura-1)) ] = elto;

    }
    else
        std::cout << "No existe el nodo donde se quiere insertar" << std::endl;

}

template <class t>
void abin_pos_rel<t>::insertar_hijo_izq(const t& elto,const t& padre){

    int n_pos = 0;

    for (; n_pos < arr_size && padre != arbol[n_pos]; ++n_pos);

    if (n_pos < arr_size){ // lo ha encontrado
        
        arbol[ n_pos - (int)(std::pow(2,max_altura-1)) ] = elto;

    }
    else
        std::cout << "No existe el nodo donde se quiere insertar" << std::endl;

}



template<class t>
int abin_pos_rel<t>::altura_maxima_nodo(t nodo){

    int altura_nodo = arr_size/2;
    int saltos = 0 ;
    //contar el numero de saltos de búsqueda dicotómica


}
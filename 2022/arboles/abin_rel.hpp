#include <iostream>
#include <string>
#include <algorithm>
#include <vector>
#include <stdlib.h>
#include <cmath>
#include <cassert>


/* -------------------------------------------------------------------------- */
/*                                 EJERCICIO 4                                */
/* -------------------------------------------------------------------------- */

//Crear un arbol binario con la reprensentación dada en el enunciado de la practica

template <class t>
class abin_pos_rel{


public:
    
    struct nodo{
        
        nodo(t elt , char l, unsigned int h):elemento(elt),altura(h),lado(l){}

        t elemento;
        
        char lado; //izq = i , der= d, raiz = r

        unsigned int altura;

        bool operator ==(const nodo& other) const{
            return elemento == other.elemento && altura == other.altura && lado == other.lado;
        }

        nodo (nodo & n){
            elemento = n.elemento;
            altura = n.altura;
            lado = n.lado;
        }

    };

    t NODO_NULO;
    abin_pos_rel(const t caracter_nulo, const unsigned int& h = 0):NODO_NULO(caracter_nulo),max_altura(h),
    arbol(std::vector<nodo>(std::pow(2,h+1)-1, nodo(caracter_nulo, caracter_nulo,-1))){}

    void insertar_nodo_raiz(t elto);
    void insertar_hijo_der(t elto,nodo& n);
    void insertar_hijo_izq(t elto,nodo& n);

    void muestra_vec(){
        for (auto i : arbol){
            std::cout << i.elemento << ", ";
        }
        std::cout<<std::endl;
    }

private:

    unsigned int it_altura;
    
    std::vector<nodo>arbol;

    unsigned int max_altura;

    
};

template <class t>
void abin_pos_rel<t>::insertar_nodo_raiz(t elto){

    //en nodo raiz ira en la posicion [2^(h-1) - 1 ]/2 

    arbol[arbol.size()/2] = nodo(elto,'r',0);

    
}

//Preguntar el significado de la n 


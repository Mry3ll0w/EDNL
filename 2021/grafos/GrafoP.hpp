#ifndef GRAFOP_HPP_
#define GRAFOP_HPP_

#include <vector>
#include <limits>
#include<iostream>
#include "..\..\TADS_AAED\Lista.hpp"

// Grafo ponderado como matriz de costes
template <typename T> class GrafoP {
    public:
        typedef T tCoste;
        typedef size_t vertice; // un valor entre 0 y GrafoP::numVert()-1
        static const tCoste INFINITO; // peso arista inexistente
        explicit GrafoP(size_t n): costes(n, std::vector<tCoste>(n,INFINITO)){}
        size_t numVert() const {return costes.size();}
        const std::vector<tCoste>& operator [](vertice v) const {return costes[v];}
        std::vector<tCoste>& operator [](vertice v) {return costes[v];}
        bool esDirigido() const
        {
            for(size_t i=0;i<costes.size();++i)
            {
                for(size_t j=0;j<costes.size();++j)
                {
                    if(costes[i][j]!=costes[j][i])
                        return false;
                }
            }
            return true;
        }
        struct arista {
            vertice orig, dest;
            tCoste coste;
            explicit arista(vertice v=vertice(), vertice w=vertice(),
                tCoste c=tCoste()): orig(v), dest(w), coste(c) {}
            // Orden de aristas para Prim y Kruskall
            bool operator <(const arista& a) const { return coste < a.coste; }
        };
    private:
        std::vector<std::vector<tCoste> > costes;
};
// Definición de INFINITO
template <typename T>
const typename GrafoP<T>::tCoste GrafoP<T>::INFINITO = std::numeric_limits<T>::max();

//Grafo ponderado como Lista
template <typename T> class GrafoPL { // Grafo ponderado
    public:
        typedef T tCoste;
        typedef size_t vertice; // un valor entre 0 y GrafoP::numVert()-1
        struct vertice_coste { // vértice adyacente y coste
            vertice v;
            tCoste c;
            // requerido por Lista<vertice_coste>::buscar()
            bool operator ==(const vertice_coste& vc) const {return v == vc.v;}
        };
        static const tCoste INFINITO; // peso de arista inexistente
        GrafoPL(size_t n): ady(n) {}
        size_t numVert() const {return ady.size();}
        const Lista<vertice_coste>& adyacentes(vertice v) const {return ady[v];}
        Lista<vertice_coste>& adyacentes(vertice v) {return ady[v];}
    private:
        std::vector<Lista<vertice_coste> > ady; // vector de listas de vértice-coste
};
// Definición de INFINITO
template <typename T>
const T GrafoPL<T>::INFINITO = std::numeric_limits<T>::max();

template<typename tCoste>
std::ostream& operator<<(std::ostream& os, const GrafoPL<tCoste>& g)
{
    for(size_t i=0;i<g.numVert();++i)
    {
        os << "Nodo " << i << ": ";
        for(typename Lista<typename GrafoPL<tCoste>::vertice_coste>::posicion p=g.adyacentes(i).primera();p!=g.adyacentes(i).fin();p=g.adyacentes(i).siguiente(p))
        {
            os << g.adyacentes(i).elemento(p).v << " ";
        }
        os << std::endl;
    }
    return os;
}

template<typename T> void mostrar_grafoP(const GrafoP<T>& g)
{
    for(size_t i=0;i<g.numVert();++i)
    {
        for(size_t j=0;j<g.numVert();++j)
        {
            std::cout << g[i][j] << " ";
        }
        std::cout << std::endl;
    }
}
#endif
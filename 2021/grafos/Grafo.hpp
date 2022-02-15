#ifndef GRAFO_HPP_
#define GRAFO_HPP_
#include<iostream>
#include <vector>
#include "../../TADS_AAED/Lista.hpp"

//Grafo representado mediante una matriz de adyacencia
class Grafo {
    public:
        typedef size_t vertice; // un valor entre 0 y Grafo::numVert()-1
        explicit Grafo(size_t n): ady(n, std::vector<bool>(n, false)) {}
        size_t numVert() const {return ady.size();}
        const std::vector<bool>& operator [](vertice v) const {return ady[v];}
        std::vector<bool>& operator [](vertice v) {return ady[v];}
    private:
        std::vector<std::vector<bool> > ady;
};
////Grafo representado mediante una lista de adyacencia

class GrafoL {
    public:
        typedef size_t vertice; // un valor entre 0 y Grafo::numVert()-1
        explicit GrafoL(size_t n): ady(n) {}
        size_t numVert() const {return ady.size();}
        const Lista<vertice>& adyacentes(vertice v) const {return ady[v];}
        Lista<vertice>& adyacentes(vertice v) {return ady[v];}
    private:
        std::vector<Lista<vertice> > ady; // vector de listas de vértices
};

std::ostream& operator<<(std::ostream& os,const Grafo& g)
{
    for(size_t i=0;i<g.numVert();++i)
    {
        for(size_t j=0;j<g.numVert();++j)
        {
            if (g[i][j])
                os << " 1 ";
            else
                os << " 0 ";
        }
        os << std::endl;
    }
    return os;
}
void mostrar_grafo(const Grafo& g)
{
    for(size_t i=0;i<g.numVert();++i)
    {
        for(size_t j=0;j<g.numVert();++j)
        {
            if (g[i][j])
                std::cout << " T ";
            else
                std::cout << " F ";

        }
        std::cout << std::endl;
    }
}

#endif

#ifndef KRUSKAL_HPP_
#define KRUSKAL_HPP_

#include "Particion.hpp"
#include "GrafoP.hpp"
#include "../Arboles/Apo.hpp"

// Devuelve un árbol generador de coste mínimo de un grafo no dirigido ponderado y conexo G.
template <typename tCoste>
GrafoP<tCoste> Kruskal(const GrafoP<tCoste>& G)
{
    typedef typename GrafoP<tCoste>::vertice vertice;
    typedef typename GrafoP<tCoste>::arista arista;
    const tCoste INFINITO = GrafoP<tCoste>::INFINITO;

    const size_t n = G.numVert();
    GrafoP<tCoste> g(n); // Árbol generador de coste mínimo.
    Particion P(n); // Partición inicial de los vértices de G.
    Apo<arista> A(n*n); // Aristas de G ordenadas por costes.

    // Copiar aristas del grafo G en el APO A.
    for (vertice u = 0; u < n; u++)
        for (vertice v = u+1; v < n; v++)
            if (G[u][v] != INFINITO)
                A.insertar(arista(u, v, G[u][v]));

    size_t i = 1;
    while (i <= n-1) { // Seleccionar n-1 aristas.
        arista a = A.cima(); // arista de menor coste
        A.suprimir();
        vertice u = P.encontrar(a.orig);
        vertice v = P.encontrar(a.dest);
        if (u != v) {// extremos de a pertenecen a distintos componentes
            P.unir(u, v); //Une los nodos desde el menor al mayor
        // Incluir la arista a en el árbol g.
            g[a.orig][a.dest] = g[a.dest][a.orig] = a.coste;
            i++;
        }
    }
    return g;
}
#endif
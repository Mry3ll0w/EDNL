#include "../Arboles/Apo.hpp"
#include "GrafoP.hpp"
template <typename tCoste>
GrafoP<tCoste> Prim(const GrafoP<tCoste>& G)
    // Devuelve un árbol generador de coste mínimo
    // de un grafo no dirigido ponderado y conexo G.
{
    typedef typename GrafoP<tCoste>::vertice vertice;
    typedef typename GrafoP<tCoste>::arista arista;
    const tCoste INFINITO = GrafoP<tCoste>::INFINITO;
    arista a;
    const size_t n = G.numVert();
    GrafoP<tCoste> g(n); // Árbol generador de coste mínimo.
    vector<bool> U(n, false); // Conjunto de vértices incluidos en g.
    Apo<arista> A(n*(n-1)/2-n+2); // Aristas adyacentes al árbol g
                                 // ordenadas por costes.
    U[0] = true; // Incluir el primer vértice en U.
    // Introducir en el APO las aristas adyacentes al primer vértice.
    for (vertice v = 1; v < n; v++)
        if (G[0][v] != INFINITO)
            A.insertar(arista(0, v, G[0][v]));
    for (size_t i = 1; i <= n-1; i++) { // Seleccionar n-1 aristas.
                                        // Buscar una arista a de coste mínimo que no forme un ciclo.
                                        // Nota: Las aristas en A tienen sus orígenes en el árbol g.
        do {
            a = A.cima();
            A.suprimir();
        } while (U[a.dest]); // a forma un ciclo (a.orig y a.dest
                            // están en U y en g).
                            // Incluir la arista a en el árbol g y el nuevo vértice u en U.
        g[a.orig][a.dest] = g[a.dest][a.orig] = a.coste;
        vertice u = a.dest;
        U[u] = true;
        // Introducir en el APO las aristas adyacentes al vértice u
        // que no formen ciclos.
        for (vertice v = 0; v < n; v++)
            if (!U[v] && G[u][v] != INFINITO)
                A.insertar(arista(u, v, G[u][v]));
    }
return g;
}
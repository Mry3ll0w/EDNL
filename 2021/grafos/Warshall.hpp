
#ifndef WARSHALL_HPP_
#define WARSHALL_HPP_
#include "matriz.hpp"

matriz<bool> Warshall(const Grafo& G)
{
    typedef Grafo::vertice vertice;
    const size_t n = G.numVert();
    matriz<bool> A(n);

    // Inicializar A con la matriz de adyacencia de G
    for (vertice i = 0; i <= n-1; i++) {
        A[i] = G[i];
        //A[i][i] = true;
    }
    // Comprobar camino entre cada par de vértices i, j
    // a través de cada vértice k
    for (vertice k = 0; k <= n-1; k++)
        for (vertice i = 0; i <= n-1; i++)
            for (vertice j = 0; j <= n-1; j++)
                if (!A[i][j])
                    A[i][j] = A[i][k] && A[k][j];

    return A;
}
#endif
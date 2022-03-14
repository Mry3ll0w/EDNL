#ifndef FLOYD_HPP_
#define FLOYD_HPP_
#include "matriz.hpp"
#include<vector>
template <typename tCoste>
matriz<tCoste> Floyd(const GrafoP<tCoste>& G, matriz<typename GrafoP<tCoste>::vertice>& P)
{
    typedef typename GrafoP<tCoste>::vertice vertice;
    const size_t n = G.numVert();
    matriz<tCoste> A(n); // matriz de costes mínimos
    // Iniciar A y P con caminos directos entre cada par de vértices.
    P = matriz<vertice>(n);
    for (vertice i = 0; i < n; i++) {
        A[i] = G[i]; // copia costes del grafo
        A[i][i] = 0; // diagonal a 0
        P[i] = std::vector<vertice>(n, i); // caminos directos
    }
    // Calcular costes mínimos y caminos correspondientes
    // entre cualquier par de vértices i, j
    for (vertice k = 0; k <= n-1; k++){
        for (vertice i = 0; i <= n-1; i++){
            for (vertice j = 0; j <= n-1; j++) {
                tCoste ikj = suma(A[i][k], A[k][j]);
                if (ikj < A[i][j]) { //if (ikj > A[i][j] && ikj != INFINITO) Para maximizar
                    A[i][j] = ikj;
                    P[i][j] = k;
                }
            }
        }
    }
    return A;
}
#endif
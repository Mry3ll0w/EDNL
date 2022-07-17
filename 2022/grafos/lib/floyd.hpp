#include "matriz.h"
#include "grafoPMC.h"
template <typename tCoste>
matriz<tCoste> Floyd(const GrafoP<tCoste>& G,
                    matriz<typename GrafoP<tCoste>::vertice>& P)
{
typedef typename GrafoP<tCoste>::vertice vertice;
const size_t n = G.numVert();
matriz<tCoste> A(n); // matriz de costes mínimos
    
    // Iniciar A y P con caminos directos entre cada par de vértices. P = matriz<vertice>(n);
    for (vertice i = 0; i <= n-1; i++) {
        A[i] = G[i];
        A[i][i] = 0;
        P[i] = vector<vertice>(n, i);
    }

    // Calcular costes mínimos y caminos correspondientes
    // entre cualquier par de vértices i, j
    for (vertice k = 0; k <= n-1; k++)
        for (vertice i = 0; i <= n-1; i++)
            for (vertice j = 0; j <= n-1; j++) {
                tCoste ikj = suma(A[i][k], A[k][j]); 
                if (ikj < A[i][j]) {
                    A[i][j] = ikj;
                    P[i][j] = k; 
                }
            } 
return A;//Devuelve el resultado
}

#include <algorithm>
#include <iostream>

#include "lib/alg_grafoPMC.h"

// Maximizamos con esta función, porque no queremos planamente
// usar std::max. En el caso donde (a == INF) ^ (b == INF), no debemos escoger
// INF, sino el valor que no sea INF (puesto que INF representa ausencia de
// arista, pero de a y b sabemos que uno de ellos sí existe arista... por lo que
// deberíamos de tomarlo)
template <typename tCoste> tCoste max_inf(tCoste a, tCoste b)
{
  static const tCoste INF = GrafoP<tCoste>::INFINITO;
  if (a == INF && b == INF)
    return INF;
  else if (a == INF)
    return b;
  else if (b == INF)
    return a;
  else
    return std::max(a, b);
}

template <typename tCoste> matriz<tCoste> FloydMax(const GrafoP<tCoste> &G)
{
  typedef typename GrafoP<tCoste>::vertice vertice;
  const size_t N = G.numVert();
  static const tCoste INF = GrafoP<tCoste>::INFINITO;

  // Creamos una copia del grafo, y por supuesto con los costes
  // triviales de los caminos i->i a 0
  matriz<tCoste> R(N);
  for (vertice i = 0; i < N; i++)
  {
    R[i] = G[i];
    R[i][i] = 0;
  }

  // Para cada vértice, probamos para cada par de vértices i,j
  // si incluir k en el camino de i->j es más optimo (= más caro)
  // que i->j a secas
  for (vertice k = 0; k < N; k++)
    for (vertice i = 0; i < N; i++)
      for (vertice j = 0; j < N; j++)
        R[i][j] = max_inf(R[i][j], suma(R[i][k], R[k][j]));

  return R;
}

template <typename tCoste>
tCoste viaje_mas_costoso(const GrafoP<tCoste> &G,
                         typename GrafoP<tCoste>::vertice &origen,
                         typename GrafoP<tCoste>::vertice &destino)
{
  typedef typename GrafoP<tCoste>::vertice vertice;
  const size_t N = G.numVert();
  static const tCoste INF = GrafoP<tCoste>::INFINITO;

  tCoste mayor_coste = 0;
  auto R = FloydMax(G);

  // Finalmente, tomamos cada posible camino i->j y seleccionamos
  // siempre aquella que exista y sea más costosa
  for (vertice i = 0; i < N; i++)
    for (vertice j = 0; j < N; j++)
      if (R[i][j] != INF && mayor_coste > R[i][j])
      {
        mayor_coste = R[i][j];
        origen = i;
        destino = j;
      }

  return mayor_coste;
}

int main() {}

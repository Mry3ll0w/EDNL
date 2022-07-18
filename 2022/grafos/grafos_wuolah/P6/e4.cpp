#include <algorithm>
#include <iostream>

#include "alg_grafoPMC.hpp"

template <typename tCoste>
matriz<tCoste> zuelandiaCalc(GrafoP<tCoste> G, // Copia implícita
                             const std::vector<bool> &ciudad_tomada,
                             const matriz<bool> &carreteras_tomadas,
                             typename GrafoP<tCoste>::vertice capital)
{
  typedef typename GrafoP<tCoste>::vertice vertice;
  const size_t N = G.numVert();
  static const tCoste INF = GrafoP<tCoste>::INFINITO;

  // Eliminamos toda arista que venga o salga
  // de toda ciudad tomada
  for (vertice i = 0; i < N; i++)
  {
    if (ciudad_tomada[i])
      for (vertice j = 0; j < N; j++)
        G[i][j] = G[j][i] = INF;
  }

  // Eliminamos también toda arista que represente una
  // carretera tomada
  for (vertice i = 0; i < N; i++)
    for (vertice j = 0; j < N; j++)
      if (carreteras_tomadas[i][j])
        G[i][j] = INF;

  // Como siempre tenemos que incluir la capital en el camino,
  // queremos obtener la mejor ruta para i->capital->j
  std::vector<vertice> P;
  // Representa i->capital
  auto hacia_capital = DijkstraInv(G, capital, P);
  // Representa capital->j
  auto desde_capital = Dijkstra(G, capital, P);

  // Para cada par de ciudades i,j, calculamos
  // la distancia i->capital->j y la asignamos a la arista i,j
  GrafoP<tCoste> Gp(N);
  for (vertice i = 0; i < N; i++)
    for (vertice j = 0; j < N; i++)
      Gp[i][j] = suma(hacia_capital[i], desde_capital[j]);

  return Gp;
}

int main() {}

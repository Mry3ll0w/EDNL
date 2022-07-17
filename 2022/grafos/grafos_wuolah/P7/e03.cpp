#include <algorithm>
#include <cmath>
#include <iostream>
#include <numeric>

#include "alg_grafoPMC.hpp"

// Precondición: asumimos que existe un camino de origen a cualquier
// ciudad del grafo y de vuelta.
template <typename tCoste>
tCoste distribuir(const typename GrafoP<tCoste>::vertice origen,
                  size_t cantidad, const GrafoP<tCoste> &G,
                  const std::vector<double> &almacenes,
                  const std::vector<double> &subvenciones,
                  std::vector<int> &cantidades)
{
  typedef typename GrafoP<tCoste>::vertice vertice;
  static const tCoste INF = GrafoP<tCoste>::INFINITO;
  using std::vector;

  int N = G.numVert();

  // Obtenemos los costes de viajar a cada
  vector<vertice> P;
  auto D = Dijkstra(G, origen, P);
  for (vertice i = 0; i < N; i++)
    D[i] = D[i] * (1. - subvenciones[i]);
  D[origen] = INF; // No tenemos que viajar a origen

  // `idx` será un vector de vértices, ordenados de menor coste a mayor coste
  // (reflejado de D).
  vector<vertice> idx(N);

  // idx = 0, 1, 2, ..., N-2, N-1
  std::iota(idx.begin(), idx.end(), 0);

  // y aquí ordenamos idx en base a D
  std::sort(idx.begin(), idx.end(), [&D](int i, int j) { return D[i] < D[j]; });

  // De menor a mayor coste, investigamos cada vértice...
  cantidades = vector<int>(N, 0);
  double coste = 0.;
  for (auto v = idx.begin(); v != idx.end() && cantidad > 0; v++)
  {
    // Ponemos en el almacén con el mejor coste todo lo que podamos
    // poner, hasta rellenar el almacén o hasta que no tengamos más
    cantidades[*v] = std::min(almacenes[*v], cantidad);

    // ... y lo dado se sustrae de nuestra cantidad
    cantidad -= cantidades[*v];

    // Además, acumulamos el coste total de viajar al vértice *v
    coste += D[*v];
  }

  return coste;
}

int main() {}

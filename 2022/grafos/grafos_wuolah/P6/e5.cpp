#include <algorithm>
#include <iostream>

#include "grafoPLA.hpp"

template <typename tCoste> tCoste suma(tCoste x, tCoste y)
{
  if (x == GrafoP<tCoste>::INFINITO || y == GrafoP<tCoste>::INFINITO)
    return GrafoP<tCoste>::INFINITO;
  else
    return x + y;
}

template <typename tCoste>
std::vector<tCoste> Dijkstra(const GrafoP<tCoste> &G,
                             typename GrafoP<tCoste>::vertice origen,
                             std::vector<typename GrafoP<tCoste>::vertice> &P)
{
  typedef typename GrafoP<tCoste>::vertice vertice;
  static const tCoste INF = GrafoP<tCoste>::INFINITO;
  const size_t N = G.numVert();
  using std::vector;

  // Conjunto de vértices vacío
  vector<bool> S(N, false);

  // Vector de vértices. La posición i-ésima indica a cuál vértice hay que
  // ir desde i para llegar a la distancia mas corta
  P = vector<vertice>(N, origen);

  // Costes mínimos desde el origen
  // Todos los caminos desde el origen se tratan como inexistentes...
  vector<tCoste> D(N, INF);

  // ... excepto aquellos que son immediatos desde el origen
  auto &Lt = G.adyacentes(origen);
  for (auto ptr = Lt.primera(); ptr != Lt.fin(); ptr = Lt.siguiente(ptr))
  {
    auto elem = Lt.elemento(ptr);
    D[elem.v] = elem.c;
  }

  // Primer iteración, ya sabemos a priori y trivialmente
  // que el menor camino a optimizar por ahora es de origen->origen
  D[origen] = 0;
  S[origen] = true;

  vertice v, w;
  for (int i = 1; i < N - 1; i++)
  {
    // Encontramos el siguiente camino no visitado más óptimo (= menor coste)
    tCoste mejor_coste = INF;
    for (v = 0; v < N; v++)
    {
      if (!S[v] && D[v] <= mejor_coste)
      {
        mejor_coste = D[v];
        w = v;
      }
    }

    // Lo marcamos como visitado
    S[w] = true;
    auto Dw = D[w];

    // Actualizamos los costes óptimos al incluir w en el camino
    // de origen->v para cada v no visitado aún
    auto &Lt = G.adyacentes(w);
    for (auto ptr = Lt.primera(); ptr != Lt.fin(); ptr = Lt.siguiente(ptr))
    {
      auto elem = Lt.elemento(ptr);
      if (!S[elem.v])
      {
        // origen->w + w->v
        auto Ovw = suma(Dw, elem.c);
        if (Ovw < D[elem.v])
        {
          D[elem.v] = Ovw;
          P[elem.v] = w;
        }
      }
    }
  }

  return D;
}

int main()
{
  typedef typename GrafoP<int>::vertice vertice;
  GrafoP<int> G(5);

  {
    auto &L = G.adyacentes(0);
    L.insertar({1, 3}, L.fin());
    L.insertar({2, 50}, L.fin());
    L.insertar({4, 3}, L.fin());
  }

  {
    auto &L = G.adyacentes(1);
    L.insertar({2, 5}, L.fin());
  }

  {
    auto &L = G.adyacentes(2);
    L.insertar({3, 30}, L.fin());
    L.insertar({4, 5}, L.fin());
    L.insertar({0, 50}, L.fin());
  }

  std::vector<vertice> P;
  auto D = Dijkstra(G, 0, P);

  for (auto d : D)
    std::cout << d << " ";
}

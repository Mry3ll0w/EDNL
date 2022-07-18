#include <iostream>

#include "alg_grafoPMC.hpp"

template <typename tCoste>
vector<tCoste> DijkstraInv_(const GrafoP<tCoste> &G,
                            typename GrafoP<tCoste>::vertice destino,
                            vector<typename GrafoP<tCoste>::vertice> &P)
{
  using std::vector;
  typedef typename GrafoP<tCoste>::vertice vertice;
  const size_t N = G.numVert();

  vertice v, w;

  // Conjunto de vértices vacío
  vector<bool> S(N, false);

  // Costes mínimos desde el origen
  vector<tCoste> D(N);
  for (vertice i = 0; i < N; i++)
    D.push_back(G[i][destino]);

  // Vector de vértices. La posición i-ésima indica a cuál vértice hay que
  // ir desde i para llegar a la distancia mas corta
  P = vector<vertice>(N, destino);

  D[destino] = 0;
  S[destino] = true;
  for (size_t i = 1; i < N - 1; i++)
  {
    // w = vértice con el coste de menor tamaño que no se haya
    // computado aún
    tCoste costeMin = GrafoP<tCoste>::INFINITO;
    for (v = 0; v < N; v++)
      if (!S[v] && D[v] <= costeMin)
      {
        costeMin = D[v];
        w = v;
      }

    // Ahora hemos seleccionado este vértice para reducir su distancia
    S[w] = true;

    // Recalculamos la distancia *hacia* w desde cada vértice aún no usado *v*
    // Si usar la ruta desde v hasta w. y desde w al destino es mejor que la ruta
    // original de v a destino (aka "incluir w en el camino v -> destino"),
    // entonces tenemos que actualizarla
    for (v = 0; v < N; v++)
      if (!S[v])
      {
        tCoste Ovw = suma(D[w], G[v][w]);
        if (Ovw < D[v])
        {
          D[v] = Ovw;
          P[v] = w;
        }
      }
  }

  return D;
}

int main()
{
  std::vector<typename GrafoP<int>::vertice> P(5);
  GrafoP<int> G(5);
  G[1][0] = 5;
  G[2][1] = 5;
  G[3][2] = 10;
  G[3][0] = 50;
  G[4][3] = 50;

  std::cout << G << "\n";

  auto D = DijkstraInv_(G, 0, P);

  for (auto d : D)
    std::cout << d << " ";
  std::cout << "\n";
  for (auto p : P)
    std::cout << p << " ";
}

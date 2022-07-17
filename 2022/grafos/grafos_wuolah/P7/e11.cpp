#include "alg_grafoPMC.hpp"

template <typename tCost> struct Puente
{
  typedef typename GrafoP<tCost>::vertice ciudad;
  ciudad a, b;
};

template <typename tCoste>
matriz<tCoste> costes_viajes_islas(GrafoP<tCoste> &S1, GrafoP<tCoste> &S2,
                                GrafoP<tCoste> &S3,
                                const std::vector<Puente<tCoste>> &puentes)
{
  typedef typename GrafoP<double>::vertice vertice;
  const int N1 = S1.numVert(), N2 = S2.numVert(), N3 = S3.numVert();

  // Construimos un grafo global, donde metamos todos los 3 grafos y...
  GrafoP<tCoste> G(N1 + N2 + N3);
  for (int i = 0; i < N1; i++)
    for (int j = 0; j < N1; j++)
      G[i][j] = S1[i][j];

  for (int i = 0; i < N2; i++)
    for (int j = 0; j < N2; j++)
      G[i + N1][j + N1] = S2[i][j];

  for (int i = 0; i < N3; i++)
    for (int j = 0; j < N3; j++)
      G[i + N1 + N2][j + N1 + N2] = S3[i][j];

  // ... enlazamos los grafos por cada puente, de ida y vuelta
  for (auto &p : puentes)
    G[p.a][p.b] = G[p.b][p.a] = 0;

  // Y por último, calculamos la matriz de mínimo coste para cada par de ciudades
  std::vector<vertice> P(G.numVert());
  return Floyd(G, P);
}

int main() {}

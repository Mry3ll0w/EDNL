#include "alg_grafoPMC.hpp"

double coste_arbol_expansion_min(const GrafoP<double> &G)
{
  typedef typename GrafoP<double>::vertice vertice;
  typedef typename GrafoP<double>::arista arista;
  const double INFINITO = GrafoP<double>::INFINITO;
  const size_t N = G.numVert();

  // Sólo tenemos que sumar el coste de todas las aristas
  // del árbol de expansión mínimo
  double costeTotal = 0.;
  auto T = Kruskall(G);
  for (vertice i = 0; i < N; i++)
    for (vertice j = i + 1; j < N; j++)
      if (T[i][j] != GrafoP<double>::INFINITO)
        costeTotal += T[i][j];

  return costeTotal;
}

int main() {}

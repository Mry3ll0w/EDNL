#include <algorithm>
#include <iostream>

#include "alg_grafoPMC.hpp"

template <typename tCoste>
bool aciclico_rec(typename GrafoP<tCoste>::vertice i,
                  std::vector<bool> &visitado, const GrafoP<tCoste> &G);

template <typename tCoste> bool aciclico(const GrafoP<tCoste> &G)
{
  typedef typename GrafoP<tCoste>::vertice vertice;
  static const tCoste INF = GrafoP<tCoste>::INFINITO;
  const size_t N = G.numVert();

  // Pila de vértices
  std::vector<vertice> visitado;

  // Para cada vértice...
  for (vertice i = 0; i < N; i++)
    // Si encontramos un ciclo,
    // entonces claramente el grafo es cíclico
    if (!aciclico_rec(i, visitado, G))
      return false;

  // Y si no encontramos ningún ciclo, entonces G es acíclico
  return true;
}

template <typename tCoste>
bool aciclico_rec(typename GrafoP<tCoste>::vertice i,
                  std::vector<typename GrafoP<tCoste>::vertice> &visitado,
                  const GrafoP<tCoste> &G)
{
  typedef typename GrafoP<tCoste>::vertice vertice;
  static const tCoste INF = GrafoP<tCoste>::INFINITO;
  const size_t N = G.numVert();

  visitado.push_back(i);

  // clang-format off
  for (vertice j = 0; j < N; j++)
    if (i != j && // No visitamos la arista i->i (que no es "realmente" una arista)
        G[i][j] != INF && // Visitamos sólo aristas que existen
        (std::find(visitado.begin(), visitado.end(), j) != visitado.end() ||
        // Si j ya existe en el camino original, entonces hay ciclo
        !aciclico_rec(j, visitado, G)
        // O si ya encontramos un ciclo a partir de j...
    ))
      return false; // Entonces el grafo no es acíclico
  // clang-format on

  visitado.pop_back();
  return true;
}

int main()
{
  GrafoP<int> G(5);
  G[1][2] = 1;
  G[0][2] = 1;
  G[0][3] = 1;

  G[3][4] = 1;
  G[4][1] = 1;

  std::cout << aciclico(G) << "\n";
}

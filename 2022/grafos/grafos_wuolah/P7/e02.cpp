#include <algorithm>
#include <cmath>
#include <iostream>

#include "alg_grafoPMC.hpp"

// Necesario para especificar el origen, destino y paredes
// por parte del usuario
struct Celda
{
  int x, y;
  Celda(int x, int y) : x(x), y(y) {}

  int dis(const Celda o) { return std::abs(x - o.x) + std::abs(y - o.y); }
};

struct Pared
{
  Celda a, b;
};

typename GrafoP<int>::vertice celda2vertice(Celda c, const size_t N)
{
  return c.x + c.y * N;
}

Celda vertice2celda(typename GrafoP<int>::vertice i, const int N)
{
  return Celda(i % N, i / N);
}

std::vector<Celda> camino_laberinto(const size_t N,
                                    const std::vector<Pared> &paredes,
                                    Celda origen, Celda destino)
{

  typedef typename GrafoP<int>::vertice vertice;
  static const int INF = GrafoP<int>::INFINITO;
  using std::vector;
  const size_t TAM = N * N;

  // Creamos un grafo de N*N (N^2 celdas en el laberinto)
  GrafoP<int> G(TAM);

  // Para cada par de vértices i->j, definimos su coste directo.
  // Por defecto, no existe arista directa en i->j
  for (vertice i = 0; i < TAM; i++)
  {
    // Claramente, la distancia de una celda a si misma es 0
    G[i][i] = 0;

    Celda celda_i = vertice2celda(i, N);
    for (vertice j = 0; j < TAM; j++)
    {
      Celda celda_j = vertice2celda(i, N);

      // Codificamos los vértices i,j y miramos su distancia de Manhattan.
      // Si es 1, o lo que es lo mismo, horizontalmente/verticalmente adyacente,
      // entonces la distancia también es 1
      if (celda_i.dis(celda_j) == 1)
        G[i][j] = 1;
    }
  }

  // Para cada pared, tomamos las celdas a,b que lo representan,
  // los vértices i,j que representan respectivamente y
  // eliminamos las aristas i->j y j->i del grafo.
  for (auto pared : paredes)
  {
    auto i = celda2vertice(pared.a, N);
    auto j = celda2vertice(pared.b, N);

    G[i][j] = G[j][i] = INF;
  }

  const vertice destino_v = celda2vertice(destino, N);
  const vertice origen_v = celda2vertice(origen, N);

  // Ahora buscamos el camino más corto del origen al destino
  vector<vertice> P;
  auto D = Dijkstra(G, celda2vertice(origen, N), P);

  // Si no hay ruta, devolvemos un camino vacío (convenio)
  if (D[destino_v] == INF)
    return vector<Celda>();
  else
  {
    // Y si lo hay, recorremos P desde el destino hasta el origen
    // para guardar el camino construido
    vector<Celda> camino;
    camino.insert(camino.begin(), destino);
    for (vertice i = destino_v; i != origen_v; i = P[i])
      camino.insert(camino.begin(), vertice2celda(P[i], N));

    return camino;
  }
}

int main() {}

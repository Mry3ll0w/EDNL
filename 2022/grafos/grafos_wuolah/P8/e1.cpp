#include "alg_grafoPMC.hpp"

#include <cmath>

struct Coord
{
  double x, y;
  double dist(const Coord &) const;
};

inline double dist(const Coord &a, const Coord &b)
{
  return std::sqrt(std::pow(a.x - b.x, 2) + std::pow(a.y - b.y, 2));
}

inline double Coord::dist(const Coord &o) const { return ::dist(*this, o); }

Particion tombuctu(const std::vector<Coord> &ciudades, const Grafo &G,
                   matriz<double> &costes)
{
  typedef typename GrafoP<double>::vertice vertice;
  static const double INF = GrafoP<double>::INFINITO;
  const size_t N = G.numVert();

  // Nos deshacemos immediatamente del problema fácil...
  GrafoP<double> Gc(N);
  for (vertice i = 0; i < N; i++)
    for (vertice j = 0; j < N; j++)
      if (G[i][j])
        Gc[i][j] = ciudades[i].dist(ciudades[j]);
  matriz<vertice> P(N);
  costes = Floyd(Gc, P);

  Particion particion(N);//1 2 3 4 5 .. 

  for (vertice i = 0; i < N; i++)
    for (vertice j = 0; j < N; j++)
      if (
        costes[i][j] != INF //No hay infinto existe un camino ==> Pertenece a una isla
        && 
        particion.encontrar(i) != particion.encontrar(j)//Esta ya en esa isla ??
      )
        particion.unir(i, j);

  return particion;
}

int main() {}

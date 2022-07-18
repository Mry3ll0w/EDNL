#include "alg_grafoPMC.hpp"
#include "apo.hpp"

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

struct LineaAerea
{
  typedef typename GrafoP<double>::vertice vertice;
  vertice a, b; double dist;

  LineaAerea(vertice a, vertice b, double dist) : a(a), b(b), dist(dist) {}

  bool operator<(const LineaAerea &o) { return dist < o.dist; }
};

std::vector<LineaAerea> tombuctu2(const std::vector<Coord> &ciudades,
                                  const Grafo &G, matriz<double> &costes)
{
  typedef typename GrafoP<double>::vertice vertice;
  static const double INF = GrafoP<double>::INFINITO;
  const size_t N = G.numVert();

  GrafoP<double> Gc(N);

  for (vertice i = 0; i < N; i++)
    for (vertice j = 0; j < N; j++)
      if (G[i][j])
        Gc[i][j] = ciudades[i].dist(ciudades[j]);

  matriz<vertice> P;
  auto D = Floyd(Gc, P);

  Particion particion(N);
  int islas = N;

  for (vertice i = 0; i < N; i++)
    for (vertice j = 0; j < N; j++)
      if (costes[i][j] != INF && particion.encontrar(i) != particion.encontrar(j))
      {
        islas--;
        particion.unir(i, j);
      }

  std::vector<LineaAerea> LA;
  matriz<bool> visitado(N);

  Apo<LineaAerea> APO(N * (N - 1) / 2);
  for (vertice i = 0; i < N; i++)
    for (vertice j = i + 1; j < N; j++)
      APO.insertar(LineaAerea(i, j, Gc[i][j]));

  for(int i = 0; i < islas * (islas - 1) / 2;)
  {
    auto linea = APO.cima(); APO.suprimir();
    auto a_part = particion.encontrar(linea.a);
    auto b_part = particion.encontrar(linea.b);

    if(!visitado[a_part][b_part])
    {
      visitado[a_part][b_part] = visitado[b_part][a_part] = true;
      LA.push_back(linea);
    }
  }

  return LA;
}

int main() {}

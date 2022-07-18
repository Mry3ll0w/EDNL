#include "alg_grafoPMC.hpp"

#include <algorithm>
#include <cmath>
#include <iostream>


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


GrafoP<double> reconstruirIsla(const std::vector<Coord> &isla)
{
  typedef typename GrafoP<double>::vertice vertice;
  const int N = isla.size();

  GrafoP<double> G(N);

  // construir distancias entre cada par de ciudades
  for (vertice i = 0; i < N; i++)
    for (vertice j = i + 1; i < N; i++)
      G[i][j] = G[j][i] = isla[i].dist(isla[j]);

  // mejores carreteras son seleccionadas
  return Kruskall(G);
}

GrafoP<double> reconstruir(const std::vector<Coord> &fobos,
                           const std::vector<Coord> &deimos,
                           const std::vector<bool> &fobosCosteras,
                           const std::vector<bool> &deimosCosteras)
{
  int fobosN = fobos.size();
  int deimosN = deimos.size();

  // reconstruir cada carretera
  GrafoP<double> fobosCarreteras = reconstruirIsla(fobos);
  GrafoP<double> deimosCarreteras = reconstruirIsla(deimos);

  // * buscar puente = construir toda arista C_1 × C_2 y encontrar la mas
  // pequeña
  // la cond. 2 indica que solo hay un puente. si no existiera, podrian
  // haber mas de un puente que minimize el coste global de reconstruccion,
  // segun el coste de un puente
  int candFobos = 0;
  int candDeimos = 0;
  double costeMin = GrafoP<double>::INFINITO;

  for (int i = 0; i < fobosN; i++)
  {
    if (fobosCosteras[i])
    {
      for (int j = 0; j < deimosN; j++)
      {
        if (deimosCosteras[j])
        {
          auto dis = fobos[i].dist(deimos[j]);
          if (dis < costeMin)
          {
            candFobos = i;
            candDeimos = j;
            costeMin = dis;
          }
        }
      }
    }
  }

  std::cout << costeMin << "\n";

  // * construir grafo global
  GrafoP<double> global(fobosN + deimosN);
  for (int i = 0; i < fobosN; i++)
    for (int j = i + 1; j < fobosN; j++)
      global[i][j] = global[j][i] = fobosCarreteras[i][j];

  for (int i = 0; i < deimosN; i++)
    for (int j = i + 1; j < deimosN; j++)
      global[i + fobosN][j + fobosN] = global[j + fobosN][i + fobosN] =
          deimosCarreteras[i][j];

  // poner puente
  global[candFobos][candDeimos + fobosN] =
      global[candDeimos + fobosN][candFobos] = costeMin;

  return global;
}

struct Ciudad
{
  int indice;
  bool esDeDeimos;
};

double mejorCosteViaje(const std::vector<Coord> &fobos,
                       const std::vector<Coord> &deimos,
                       const std::vector<bool> &fobosCosteras,
                       const std::vector<bool> &deimosCosteras, Ciudad origen,
                       Ciudad destino)
{
  auto global = reconstruir(fobos, deimos, fobosCosteras, deimosCosteras);
  std::vector<typename GrafoP<double>::vertice> P(fobos.size() + deimos.size());

  int origenIdx = origen.indice + origen.esDeDeimos * fobos.size();
  int destIdx = destino.indice + destino.esDeDeimos * fobos.size();
  return Dijkstra(global, origenIdx, P)[destIdx];
}

int main()
{
  std::vector<Coord> fobos{
      {1, 2},
      {2, 2},
      {3, -1},
      {4, 7},
  };

  std::vector<Coord> deimos{
      {11, 16},
      {12, 8},
      {13, 18},
      {14, 17},
  };

  std::vector<bool> fobosCosteras{true, false, true, false};
  std::vector<bool> deimosCosteras{false, true, false, true};

  std::cout << "puentes 'posibles'\n";
  for (int i = 0; i < 4; i++)
    for (int j = 0; j < 4; j++)
      std::cout << i << " " << j << " " << fobos[i].dist(deimos[j]) << "\n";

  std::cout << "\ndistancias fobos\n";
  for (int i = 0; i < 4; i++)
    for (int j = 0; j < 4; j++)
      std::cout << i << " " << j << " " << dist(fobos[i], fobos[j]) << "\n";

  std::cout << "\ndistancias deimos\n";
  for (int i = 0; i < 4; i++)
    for (int j = 0; j < 4; j++)
      std::cout << i << " " << j << " " << dist(deimos[i], deimos[j]) << "\n";
  std::cout << "\n";

  std::cout << mejorCosteViaje(fobos, deimos, fobosCosteras, deimosCosteras,
                               {1, false}, {0, true})
            << "\n";
}

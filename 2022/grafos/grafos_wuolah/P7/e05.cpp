#include "alg_grafoPMC.hpp"

enum class Alergia
{
  CARRETERA,
  TREN,
  AVION,
};

template <typename tCoste>
std::vector<bool>
viajero_alergico(const typename GrafoP<tCoste>::vertice origen,
                 const tCoste dinero,
                 const GrafoP<tCoste> G1, // Copia implícita
                 const GrafoP<tCoste> &G2)
{
  typedef typename GrafoP<tCoste>::vertice vertice;
  const size_t N = G1.numVert();

  for (vertice i = 0; i < N; i++)
    for (vertice j = 0; j < N; j++)
      G1[i][j] = std::min(G1[i][j], G2[i][j]);

  std::vector<vertice> P;
  auto D = Dijkstra(G1, origen, P);

  std::vector<bool> visitable(N);
  for (vertice i = 0; i < N; i++)
    visitable[i] = D[i] <= dinero;

  return visitable;
}

template <typename tCoste>
std::vector<bool>
viajero_alergico(const typename GrafoP<tCoste>::vertice origen,
                 const tCoste dinero,
                 const GrafoP<tCoste> &carretera, const GrafoP<tCoste> &tren,
                 const GrafoP<tCoste> &avion, Alergia alergia)
{
  switch (alergia)
  {
  case Alergia::AVION:
    return viajero_alergico(origen, carretera, tren);
  case Alergia::CARRETERA:
    return viajero_alergico(origen, avion, tren);
  case Alergia::TREN:
    return viajero_alergico(origen, avion, carretera);
  }
}

int main() {}

#include "alg_grafoPMC.hpp"

template <typename tCoste>
tCoste mejor_coste_un_transborde(typename GrafoP<tCoste>::vertice origen,
                                 typename GrafoP<tCoste>::vertice destino,
                                 const GrafoP<tCoste> &tren,
                                 const GrafoP<tCoste> &autobus)
{
  typedef typename GrafoP<tCoste>::vertice vertice;
  const size_t N = tren.numVert();

  std::vector<vertice> P;
  auto tren_orig_cambio = Dijkstra(tren, origen, P);
  auto tren_cambio_dest = DijkstraInv(tren, destino, P);
  auto bus_orig_cambio = Dijkstra(autobus, origen, P);
  auto bus_cambio_dest = DijkstraInv(autobus, destino, P);

  tCoste coste = GrafoP<tCoste>::INFINITO;

  for (vertice i = 0; i < N; i++)
    coste = std::min({
        coste,
        sum(tren_orig_cambio[i], bus_cambio_dest[i]),
        sum(bus_orig_cambio[i], tren_cambio_dest[i]),
    });

  return coste;
}

int main(){}

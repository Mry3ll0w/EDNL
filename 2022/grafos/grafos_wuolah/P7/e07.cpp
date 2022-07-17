#include "alg_grafoPMC.hpp"

template <typename tCoste>
tCoste tarifa_minima(typename GrafoP<tCoste>::vertice cambio1,
                     typename GrafoP<tCoste>::vertice cambio2,
                     typename GrafoP<tCoste>::vertice origen,
                     typename GrafoP<tCoste>::vertice destino,
                     const GrafoP<tCoste> &tren, const GrafoP<tCoste> &autobus,
                     std::vector<typename GrafoP<tCoste>::vertice> &ruta)
{
  typedef typename GrafoP<tCoste>::vertice vertice;
  const size_t N = tren.numVert();

  // Obtenemos los mejores costes de viajar por cada uno
  // de los medios dados
  std::vector<vertice> P_ida;
  auto ida_origen = Dijkstra(tren, P_ida);

  std::vector<vertice> P_vuelta;
  auto vuelta_destino = DijkstraInv(autobus, P_vuelta);

  // Y ahora obtenemos por cuál ciudad de cambio es mejor viajar
  tCoste costes[] = {
      suma(ida_origen[origen][cambio1], vuelta_destino[cambio1][destino]),
      suma(ida_origen[origen][cambio2], vuelta_destino[cambio2][destino]),
  };

  tCoste min_coste;
  vertice cambio;

  if (costes[0] < costes[1])
  {
    min_coste = costes[0];
    cambio = cambio1;
  }
  else
  {
    min_coste = costes[1];
    cambio = cambio2;
  }

  // Por último, recuperamos la ruta. Primero recuperamos desde destino hasta
  // cambio y después desde cambio hasta origen
  ruta = std::vector<vertice>();
  ruta.push_back(destino);
  for (auto i = destino; i != cambio; i = P_vuelta[i])
    ruta.insert(ruta.begin(), P_vuelta[i]);
  for (auto i = cambio; i != origen; i = P_ida[i])
    ruta.insert(ruta.begin(), P_ida[i]);

  return min_coste;
}

int main() {}

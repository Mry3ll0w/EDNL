#include "alg_grafoPMC.hpp"

template <typename tCoste>
tCoste mejor_coste_tres_medios(typename GrafoP<tCoste>::vertice origen,
                               typename GrafoP<tCoste>::vertice destino,
                               const tCoste coste_tren_bus,
                               const tCoste coste_aero,
                               const GrafoP<tCoste> &tren,
                               const GrafoP<tCoste> &autobus,
                               const GrafoP<tCoste> &avion,
                               Lista<typename GrafoP<tCoste>::vertice> &ruta)
{
  typedef typename GrafoP<tCoste>::vertice vertice;
  static const tCoste INF = GrafoP<tCoste>::INFINITO;
  const size_t N = tren.numVert();
  using std::vector;

  // Creamos un grafo en el que se guarden los 3 grafos tren, autobus y avion
  // Creamos aristas en los nodos equivalentes de tren a autobus y viceversa,
  // con coste coste_tren_bus
  // Creamos aristas en los nodos equivalentes de auto/tren a aero y viceversa,
  // con coste coste_aero
  GrafoP<tCoste> global(N * 3);
  for (vertice i = 0; i < N; i++)
  {
    global[i][i + N] = global[i + N][i] = coste_tren_bus;

    // clang-format off
    global[i][i + N * 2]
      = global[i + N][i + N * 2]
      = global[i + N * 2][i]
      = global[i + N * 2][i + N] = coste_aero;
    // clang-format on

    for (vertice j = 0; j < N; j++)
    {
      global[i][j] = tren[i][j];
      global[i + N][j + N] = autobus[i][j];
      global[i + N * 2][j + N * 2] = avion[i][j];
    }
  }

  // Calculamos Dijkstra para cada caso de partida (desde avion, tren y bus),
  // y en cada caso, también cada posible destino equivalente
  // clang-format off
  std::vector<vertice> p_tren;
  auto d_tren = Dijkstra(global, origen, p_tren);
  auto coste_min_tren =
    std::min({ d_tren[destino], d_tren[destino + N], d_tren[destino + N * 2] });

  std::vector<vertice> p_bus;
  auto d_bus = Dijkstra(global, origen, p_bus);
  auto coste_min_bus =
    std::min({ d_bus[destino], d_bus[destino + N], d_bus[destino + N * 2] });

  std::vector<vertice> p_aero;
  auto d_aero = Dijkstra(global, origen, p_aero);
  auto coste_min_aero =
    std::min({ d_aero[destino], d_aero[destino + N], d_aero[destino + N * 2] });
  // clang-format on

  // Obtenemos de cuál vector de distancia y posición trabajaremos
  // para obtener la distancia
  auto coste_min = std::min({coste_min_tren, coste_min_bus, coste_min_aero});
  GrafoP<tCoste> &d_grafo = d_tren;
  matriz<vertice> &p_grafo = p_tren;

  if (coste_min == coste_min_bus)
  {
    origen = origen + N;
    d_grafo = d_bus;
    p_grafo = p_bus;
  }
  else if (coste_min == coste_min_aero)
  {
    origen = origen + N * 2;
    d_grafo = d_aero;
    p_grafo = p_aero;
  }

  // Del coste mínimo global, tenemos que descubrir qué destino se usó.
  // Para ello, buscamos en los 3 posibles destinos codificados en el grafo.
  for (int i = 0; i < 3; i++)
    if (coste_min == d_grafo[destino + i * N])
      ruta = camino(origen, d_grafo, destino + i * N);

  // Por último, cambiamos los vértices del camino para que pertenezcan a módulo N
  for (auto i = ruta.primera(); i != ruta.fin(); i = ruta.siguiente(i))
    ruta.elemento(i) = ruta.elemento(i) % N;

  return coste_min;
}

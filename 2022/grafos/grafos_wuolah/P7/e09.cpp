#include "alg_grafoPMC.hpp"

template <typename tCoste>
tCoste mejor_coste_dos_transportes(typename GrafoP<tCoste>::vertice origen,
                                 typename GrafoP<tCoste>::vertice destino,
                                 tCoste coste_taxi, const GrafoP<tCoste> &tren,
                                 const GrafoP<tCoste> &autobus,
                                 Lista<typename GrafoP<tCoste>::vertice> &ruta)
{
  typedef typename GrafoP<tCoste>::vertice vertice;
  static const tCoste INF = GrafoP<tCoste>::INFINITO;
  const size_t N = tren.numVert();
  using std::vector;

  // Creamos un grafo que una los grafos tren y autobus, de tal forma
  // que los N primeros vértices copian exactamente a tren, y los N siguientes,
  // los de autobús. Además, para cada vértice i de 0 a N-1, creamos las aristas
  // i->i+N y i+N->i, con coste taxi, para representar el transbordo entre
  // medios
  GrafoP<tCoste> global(N * 2);
  for (vertice i = 0; i < N; i++)
  {
    global[i][i + N] = global[i + N][i] = coste_taxi;

    for (vertice j = 0; j < N; j++)
    {
      global[i][j] = tren[i][j];
      global[N + i][N + j] = autobus[i][j];
    }
  }

  // Aplicamos floyd para encontrar el mejor camino...
  matriz<tCoste> P;
  auto global_dist = Floyd(global, P);

  // Y seleccionamos el mejor coste de 4 posibles rutas (las cuales
  // diferenciamos porque, al crear el grafo global, hemos duplicado el destino
  // y el origen):
  // - salir en tren y llegar en tren
  // - salir en autobús y llegar en tren
  // - salir en tren y llegar en autobús
  // - salir en autobús y llegar en autobús
  tCoste costes[] = {
      global_dist[origen][destino],
      global_dist[origen + N][destino],
      global_dist[origen][destino + N],
      global_dist[origen + N][destino + N],
  };
  auto coste_min = std::min(costes);

  // También cambiamos los vértices de origen y destino, para...
  if (coste_min == costes[0])
    ; // No hacer nada
  else if (coste_min == costes[1])
    origen = origen + N;
  else if (coste_min == costes[2])
    destino = destino + N;
  else
    destino = destino + N, origen = origen + N;

  // ... el posterior cálculo de la ruta de origen a destino en el grafo
  // global. Queremos adaptar la ruta para que sea únicamente en los vértices
  // originales, usando el módulo de N sobre cada vértice (puesto que i == i + N
  // (mod N)).
  ruta = camino(origen, destino, P);
  for (auto i = ruta.primera(); i != ruta.fin(); i = ruta.siguiente(i))
    ruta.elemento(i) = ruta.elemento(i) % N;

  return coste_min;
}

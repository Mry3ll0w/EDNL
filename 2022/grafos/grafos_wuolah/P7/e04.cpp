#include "lib/alg_grafoPMC.h"

template <typename tCoste>
tCoste distribuir_carga(typename GrafoP<tCoste>::vertice capital,
                  const GrafoP<tCoste> &G, const std::vector<int> &parte)
{
  typedef typename GrafoP<tCoste>::vertice vertice;
  const size_t N = G.numVert();

  // Sabemos que el coste de distribuir 1 carga es el coste del
  // camino capital->cliente->capital. Sabemos también que
  // capital->cliente != cliente->capital, por lo que tenemos que calcular
  // tanto la ida como la vuelta
  matriz<vertice> P(N);
  // capital->cliente
  auto hacia_cliente = Dijkstra(G, capital, P);
  // cliente->capital
  auto desde_cliente = DijkstraInv(G, capital, P);

  // Acumulamos el coste de distribuir la carga para un cliente
  tCoste coste = 0;
  for (vertice i = 0; i < N; i++)
    coste += (hacia_cliente[i] + desde_cliente[i]) * parte[i];

  return coste;
}

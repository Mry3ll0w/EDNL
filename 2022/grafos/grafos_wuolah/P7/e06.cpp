#include "alg_grafoPMC.hpp"

template <typename tCoste>
matriz<tCoste> tarifa_minima(typename GrafoP<tCoste>::vertice cambio,
                             const GrafoP<tCoste> &tren,
                             const GrafoP<tCoste> &autobus)
{
  typedef typename GrafoP<tCoste>::vertice vertice;
  const size_t N = tren.numVert();

  matriz<vertice> P;
  // Obtenemos los mejores costes de viajar por cada uno
  // de los medios dados
  auto tren_floyd = Floyd(tren, P);
  auto autobus_floyd = Floyd(autobus, P);

  matriz<tCoste> tarifa(N);

  // Para cada ruta i->j, obtenemos qué viaje es mejor:
  // - viajar únicamente en tren
  // - viajar únicamente en bús
  // - viajar en tren, cambiar, y después en bús
  // - viajar en bís, cambiar, y después en tren
  for (vertice i = 0; i < N; i++)
    for (vertice j = 0; j < N; j++)
      tarifa[i][j] = std::min({
          tren_floyd[i][j],
          autobus_floyd[i][j],
          suma(autobus_floyd[i][cambio], tren_floyd[cambio][j]),//Para que sirve esa suma
          suma(tren_floyd[i][cambio], autobus_floyd[cambio][j]),
      });

  return tarifa;
}

int main()
{
}

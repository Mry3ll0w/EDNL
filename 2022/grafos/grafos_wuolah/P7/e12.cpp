#include "alg_grafoPMC.hpp"

template <typename tCost> struct Puente
{
  typedef typename GrafoP<tCost>::vertice ciudad;
  ciudad a, b;
};

template <typename tCoste>
typename GrafoP<tCoste>::vertice
costera_optima(const GrafoP<tCoste> &isla, const std::vector<bool> &costera)
{
  typedef typename GrafoP<tCoste>::vertice vertice;
  using std::vector;
  const size_t N = isla.numVert();

  // Calculamos la mejor ruta para cada posible par de ciudades...
  auto coste_min = GrafoP<tCoste>::INFINITO;
  std::vector<vertice> P(isla.numVert());
  auto D = Floyd(isla, P);

  // Y ahora, por cada ciudad _costera_, sumamos los costes de viajar
  // desde ella a toda otra ciudad. Tomamos sólo la de menor coste...
  vertice mejor_ciudad = 0;
  for (vertice i = 0; i < N; i++)
    if (costera[i])
    {
      tCoste temp = 0;
      for (vertice j = 0; j < N; j++)
        temp = suma(temp, D[i][j]);

      if (temp < coste_min)
      {
        coste_min = temp;
        mejor_ciudad = i;
      }
    }

  // ... y la devolvemos
  return mejor_ciudad;
}

template <typename tCoste>
Puente<tCoste> grecoland(const GrafoP<tCoste> &fobos,
                               const GrafoP<tCoste> &deimos,
                               const std::vector<bool> &costeras_fobos,
                               const std::vector<bool> &costeras_deimos)
{
  typedef typename GrafoP<tCoste>::vertice vertice;
  static const tCoste INF = GrafoP<tCoste>::INFINITO;
  using std::vector;

  // Sólo necesitamos un puente, y por tanto sólo dos ciudades,
  // uno de cada isla
  Puente<tCoste> P;
  P.a = costera_optima(fobos, costeras_fobos);
  P.b = costera_optima(deimos, costeras_deimos);
  return P;
}

int main() {}

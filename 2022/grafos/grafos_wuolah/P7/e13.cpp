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
void huries(const GrafoP<tCoste> &S1, const GrafoP<tCoste> &S2,
            const GrafoP<tCoste> &S3, const std::vector<bool> &C1,
            const std::vector<bool> &C2, const std::vector<bool> &C3,
            Puente<tCoste> &P1, Puente<tCoste> &P2)
{
  typedef typename GrafoP<tCoste>::vertice vertice;
  static const tCoste INF = GrafoP<tCoste>::INFINITO;
  using std::vector;

  // Sólo necesitamos dos puentes, el primero usa una ciudad y otra,
  // y esta última ciudad se usa, junto con otra ciudad más, en el segundo
  // puente. Así logramos no necesitar 3 puentes, puesto que viajar
  // directamente entre islas sin un puente directo sólo requiere
  // de tomar el viaje a través de los dos puentes
  P1 = Puente<tCoste>();
  P2 = Puente<tCoste>();
  P1.a = costera_optima(S1, C1);
  P1.b = P2.a = costera_optima(S2, C2);
  P2.b = costera_optima(S3, C3);
}

int main() {}

#include "alg_grafoPMC.hpp"

struct Canal
{
  int origen, dest;
  double longitud;
  double caudal;
};

std::vector<Canal> calcularCanales(const matriz<double> &distancia,
                                   const matriz<double> &caudales,
                                   const double subvencion,
                                   const double costeCanal)
{
  typedef typename GrafoP<double>::vertice vertice;
  typedef typename GrafoP<double>::arista arista;
  const double INF = GrafoP<double>::INFINITO;
  const size_t N = distancia.dimension();
  GrafoP<double> coste(N);

  // Los costes para cada potencial canal i->j (y j->i) será
  // la distancia * coste del canal por metro, pero menos la cantidad
  // de subvención dada en base al caudal del canal
  for (vertice i = 0; i < N; i++)
    for (vertice j = i + 1; j < N; j++)
      coste[i][j] = coste[j][i] =
          costeCanal * distancia[i][j] - subvencion * caudales[i][j];

  // Construimos el árbol de expansión mínimo que minimiza el coste
  // total, con Kruskall
  auto D = Kruskall(coste);

  // Construimos los canales a partir del árbol de Kruskal
  std::vector<Canal> canales;
  for (vertice i = 0; i < N; i++)
    for (vertice j = i + 1; j < N; j++)
      if (D[i][j] != INF)
        canales.push_back(
            (Canal){(int)i, (int)j, distancia[i][j], caudales[i][j]});

  return canales;
}

int main() {}

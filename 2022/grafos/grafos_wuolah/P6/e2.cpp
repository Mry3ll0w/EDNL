#include <algorithm>
#include <iostream>

#include "alg_grafoPMC.hpp"

template <typename tCoste> tCoste pseudocentro(const GrafoP<tCoste> &G)
{
  typedef typename GrafoP<tCoste>::vertice vertice;
  static const tCoste INF = GrafoP<tCoste>::INFINITO;
  const size_t N = G.numVert();

  // Queremos reducir el diametro, asi que lo inicializamos
  // al mayor coste que hay. *Convenio: grafos vacíos tienen
  // diámetro infinito*
  tCoste diametro = INF;

  // Compatibilidad con la API de Floyd
  matriz<vertice> P(N);

  // Calculamos los costes de cualquier camino en G
  auto D = Floyd(G, P);

  for (vertice i = 0; i < N; i++)
  {
    // Buscamos los 2 vértices con los costes de mayor tamaño
    // Consideramos que por defecto, los 2 "mejores" vértices
    // inicialmente son i dos veces.
    auto v = i, w = i;
    tCoste v_coste = 0, w_coste = 0;
    for (vertice j = 0; j < N; j++)
      // Sólo computamos las aristas que existen = de coste no infinito
      if (D[i][j] != INF)
      {
        // Cuando encontremos uno con mayor coste que los dos vértices
        // lo guardamos como el mejor vértice hasta el momento. Si un vértice
        // tiene peor coste que el mejor vértice encontrado
        if (D[i][j] >= v_coste)
        {
          w_coste = v_coste;
          v_coste = D[i][j];
          v = j;
        }
        else if (D[i][j] >= w_coste)
        {
          w_coste = D[i][j];
          w = j;
        }
      }

    // Minimizamos en base al mejor diámetro y el diámetro
    // obtenido en esta iteración
    diametro = std::min(diametro, suma(v_coste, w_coste));
  }

  return diametro;
}

int main()
{
  GrafoP<int> G(5);
  G[1][0] = G[0][1] = 5;
  G[2][1] = G[2][1] = 5;
  G[3][2] = G[2][3] = 10;
  G[3][0] = G[0][3] = 50;
  G[4][3] = G[3][4] = 50;

  std::cout << pseudocentro(G) << "\n";
}

#include <iostream>
#include "libGrafos/alg_grafoPMC.h"
#include <list>
using namespace std; // Avoid using std:: ....

/**
 * Tu agencia de viajes “OTRAVEZUNGRAFO S.A.” se enfrenta a un curioso cliente.
 * Es un personaje sorprendente, no le importa el dinero y quiere hacer el viaje más caro
 * posible entre las ciudades que ofertas. Su objetivo es gastarse la mayor cantidad de
 * dinero posible (ojalá todos los clientes fueran así), no le importa el origen ni el destino
 * del viaje.
 * Sabiendo que es imposible pasar dos veces por la misma ciudad, ya que casualmente
 * el grafo de tu agencia de viajes resultó ser acíclico, devolver el coste, origen y destino
 * de tan curioso viaje. Se parte de la matriz de costes directos entre las ciudades del grafo.
 */

template <class T>
pair<T, T> otravezunGrafoMasCaro(matriz<T> MatrizCostes)
{
    if (MatrizCostes.dimension() == 0)
    {
        return make_pair<int, int>(0, 0);
    }
    else
    {
        matriz<T> MatrizCaminosMaximos = MatrizCostes;

        for (int i = 0; i < MatrizCostes.dimension(); i++)
            MatrizCaminosMaximos[i][i] = 0;

        for (int k = 0; k < MatrizCostes.dimension(); k++)
        {
            for (int i = 0; i < MatrizCostes.dimension(); i++)
            {
                for (int j = 0; j < MatrizCostes.dimension(); j++)
                {
                    MatrizCaminosMaximos[i][j] = max(MatrizCaminosMaximos[i][j], MatrizCaminosMaximos[i][k] + MatrizCaminosMaximos[k][j]);
                }
            }
        }
        // Buscamos el mayor numero de la matriz de caminos
        pair<T, T> parPuntosMasCaros(0, 0);
        T TCosteMaximo = 0;
        for (int i = 0; i < MatrizCostes.dimension(); i++)
        {
            for (int j = 0; j < MatrizCostes.dimension(); j++)
            {
                if (TCosteMaximo < MatrizCaminosMaximos[i][j])
                {
                    TCosteMaximo = MatrizCaminosMaximos[i][j];
                    parPuntosMasCaros.first = i;
                    parPuntosMasCaros.second = j;
                }
            }
        }
        return parPuntosMasCaros;
    }
}

/**
 *  Se dispone de un laberinto de NxN casillas del que se conocen las casillas de entrada
 * y salida del mismo. Si te encuentras en una casilla sólo puedes moverte en las siguientes
 * cuatro direcciones (arriba, abajo, derecha, izquierda). Por otra parte, entre algunas de las
 * casillas hay una pared que impide moverse entre las dos casillas que separa dicha pared
 * (en caso contrario no sería un verdadero laberinto).
 * Implementa un subprograma que dados
 * N (dimensión del laberinto),
 *  - la lista de paredes del laberinto,
 *  - la casilla de entrada, y
 *  - la casilla de salida,
 * Calcule el camino más corto para ir de la entrada a la salida y su longitud.
 */

template <class T>
GrafoP<T> colocaParedes(GrafoP<T> GrafoLaberinto, std::list<pair<T, T>> lpParedes)
{
    GrafoP<T> GrafoCorregido = GrafoLaberinto;
    for (auto pared : lpParedes)
    {
        GrafoCorregido[pared.first][pared.second] = GrafoP<T>::INFINITO; // INFINITO
    }
    return GrafoCorregido
}

// No termino de entender como implementar el concepto de moverse en diagonal ==> Procesando los diagonales?

template <class T>
pair<int, std::vector<T>> longitudCamino(GrafoP<T> GrafoLaberinto, std::list<pair<T, T>> lpParedes, const T &origen, const T &destino)
{
    // Add paredes de laberinto
    GrafoP<T> GrafoCorregido = colocaParedes(GrafoLaberinto, lpParedes);

    // Hallamos el camino minimo
    std::vector<T> vCaminoDijkstra, vCostesMinimos;

    vCostesMinimos = Dijkstra(GrafoCorregido, vCaminoDijkstra);

    int iIterador = destino;
    std::vector<T> vCaminoMinimo;
    vCaminoMinimo.insert(vCaminoMinimo.begin(), iDestino);
    while (iIterador != origen)
    {
        vCaminoMinimo.insert(vCaminoMinimo.begin(), iIterador);
        iIterador = vCaminoDijkstra[iIterador];
    }
    // Calculamos ahora el coste total del camino (entiendo que eso es la longitud)
    int iLongitud = 0;
    for (auto i : vCaminoMinimo)
    {
        iLongitud += i;
    }

    return make_pair(iLongitud, vCaminoMinimo);
}

int main()
{

    return 0;
}

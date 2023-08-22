#include <iostream>
#include "../grafos/libGrafos/grafoPMC.h"
#include "../grafos/libGrafos/grafoMA.h"
#include "../grafos/libGrafos/alg_grafoPMC.h"

/**
 *
 * La capital de Zuelandia está alcanzando niveles de toxicidad muy elevados, por ello se ha
 * decretado el cierre a la ciudad como paso de tránsito hacia otras ciudades. (Para ir de una
 * ciudad a otra no se podrá pasar por C.Zuelandia, pero si se podrá ir si es residente de la misma
 * empleándola como ciudad destino u origen).
 * Implemente un subprograma que dada la capital y un grafo ponderado con los km de las
 * carreteras existentes entre las ciudades del país, nos devuelva los caminos resultantes de
 * nuestra nueva política “Sin pasar por la capital, por favor”.ºººº
 *
 * Datos que nos dan
 * Capital
 * Grafo Zuelandia
 *
 */

template <class T>
GrafoP<T> creaGrafoCortado(const int iCapital, GrafoP<T> gOriginal)
{
    for (size_t i = 0; i < gOriginal.numVert(); i++)
    {
        gOriginal[i][iCapital] = GrafoP<T>::INFINITO;
        gOriginal[iCapital][i] = GrafoP<T>::INFINITO;
    }
    return gOriginal;
}

template <class T>
GrafoP<T> caminoMinimoSinCapital(int iCapital, GrafoP<T> gZuelandia)
{
    GrafoP<T> gSinCapital = creaGrafoCortado(iCapital, gZuelandia);

    auto gMinimos = Floyd(gSinCapital, std::vector<T>());

    // Tenemos caminos minimos, hacemos residentes
    // Usando el grafo original obtenemos los caminos de los residentes, es decir , los que tienen como origen la capital
    std::vector<T> vDistanciasDesdeCapital = Dijkstra(gZuelandia, iCapital, std::vector<T>());
    std::vector<T> vDistanciasHaciaCapitalResidentes = DijkstraInv_(gZuelandia, iCapital, std::vector<T>());
    for (int i = 0; i < gZuelandia.numVert(); ++i)
    {
        gMinimos[iCapital][i] = vDistanciasDesdeCapital[i];
        gMinimos[i][iCapital] = vDistanciasHaciaCapitalResidentes[i]; //! FALTA LA DISTANCIA HACIA LA CAPITAL EL RESIDENTE PUEDE VOLVER
    }
    return gMinimos;
}

int main()
{
}
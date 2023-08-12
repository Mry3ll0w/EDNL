#include <iostream>
#include "../grafos/libGrafos/grafoPMC.h"
#include "../grafos/libGrafos/grafoMA.h"
#include "../grafos/libGrafos/alg_grafoPMC.h"
using namespace std; // Avoid using std:: ....

/**
 * Teoria
 * 1) Aparte de una mejora en el problema de la busqueda ¿realizan alguna aportacion adicional los arboles?
 * 2) Un AVL es un ABB, pero el reciproco no es cierto ¿Estas de acuerdo?
 * 3) Explicar ventajas e inconvenientes que plantean las colas con prioridad frente a un APO.
 * 4) ¿Que estrategia de union (por altura o por tamaño) combina mejor con la tecnica de compresión de caminos con la
 *    tecnica de compresion de caminos del TAD Particion ?
 * 5) Todos los subgrafos de n-1 aristas de un grafo de n nodos ¿son árboles generadores? ¿O son solo subgrafos de
 * coste minimo?
 *
 */

/**
 * Problema de Grafos
 * Grecolandia formada por 2 islas: Fobos y Deimos que tienen N1 y N2 ciudades, de las cuales C1 y C2 ciudades costeras.
 * Dispones de Grafos de Fobos y Deimos, representados como matriz de adyacencia, si el valor es true hay carretera.
 * Nos planteamos construir un puente entre todas las posibles ciudades costeras.
 * Los costes de viajar por un puente y carretera, su distancia euclidea.
 *
 * De cara a poder decidir que puente construir es importante indicar que se can a realizar el mismo numero de ciudades
 * del archipielago. Todos los posibles viajes origen-destino en el archipielago son, por tanto, da igual importancia y
 * en consecuencia, debemos escoger el piente que minimice el coste minimo de viajar entre las ciudades del archipielago
 * dado lo irrelevante del coste de construcion.
 *
 * Implementa una función que devuelva el puente a construir, dados:
 * MAdyacencia Fobos
 * MAdyacencia Deimos
 * Lista de ciudades Fobos representadas mediante sus coordenadas cartesianas
 * Lista de ciudades de Deimos representadas mediante sus coordenadas cartesianas
 * Lista de ciudades costeras de Fobos
 * Lista de ciudades costeras de Deimos
 *
 */

struct Ciudad
{
    int id;
    double x, y;
};

double distanciaEuclidea(Ciudad c1, Ciudad c2)
{
    return std::abs(std::pow(c1.x - c2.x, 2) - std::pow(c1.y - c2.y, 2));
}

template <class T>
GrafoP<double> construyeCarreteras(matriz<bool> mAdyacencia, std::vector<Ciudad> vCiudades)
{
    GrafoP<double> gr(vCiudades.size());
    for (int i = 0; i < gr.numVert(); i++)
    {
        for (int j = 0; j < gr.numVert(); j++)
        {
            if (mAdyacencia[i][j])
                gr[i][j] = distanciaEuclidea(vCiudades[i], vCiudades[j]);
            else
                gr[i][j] = GrafoP<double>::INFINITO;
        }
    }
    return gr;
}

template <class T>
std::pair<int, int> colocaMejorPuente(double dTotalFobos, double dTotalDeimos, std::vector<Ciudad> vCosterasFobos, std::vector<Ciudad> vCosterasDeimos)
{
    double dDistanciaMinimaTotal = GrafoP<double>::INFINITO;
    std::pair<int, int> pairMejorPuente;

    // Calculamos el coste de conectar por carretera cada archipielago

    for (int i = 0; i < vCosterasDeimos.size(); i++)
    {
        for (int j = 0; j < vCosterasFobos.size(); j++)
        {
            // Tiene truco, hay que usar kruskal para comprobar el coste total de conectar todas las ciudades, para asi tener el coste minimo,
            // no la distancia euclidea y ya, para eso nos dan el resto de ciudades, queremos minimizar el coste de cada par de ciudades
            if (dDistanciaMinimaTotal > dTotalDeimos + distanciaEuclidea(vCosterasDeimos[i], vCosterasFobos[j]) + dTotalFobos)
            {
                dDistanciaMinimaTotal = dTotalDeimos + distanciaEuclidea(vCosterasDeimos[i], vCosterasFobos[j]) + dTotalFobos;
                pairMejorPuente.first = i;
                pairMejorPuente.second = j;
            }
        }
    }
    return dMejorPuente;
}

template <class T>
std::pair<Ciudad, Ciudad> mejorPuenteGrecolandia(matriz<bool> mAdyFobos, matriz<bool> mAdyDeimos, std::vector<Ciudad> vCosterasDeimos, std::vector<Ciudad> vCosterasFobos,
                                                 std::vector<Ciudad> vDeimos, std::vector<Ciudad> vFobos)
{
    // Creamos los grafos de carreteras
    GrafoP<double> grCarreterasDeimos = construyeCarreteras(mAdyDeimos, vDeimos);
    GrafoP<double> grCarreterasFobos = construyeCarreteras(mAdyFobos, vFobos);

    // Hacemos Kruskall para obtener la suma de los costes
    GrafoP<double> grKruskallDeimos = Kruskall(grCarreterasDeimos);
    GrafoP<double> grKruskallFobos = Kruskall(grCarreterasFobos);
    double dTotalDeimos = 0, dTotalFobos = 0;
    for (int i = 0; i < grKruskallDeimos.numVert(); i++)
    {
        for (int j = 0; j < grKruskallDeimos.numVert(); j++)
        {
            if (grKruskallDeimos[i][j] != GrafoP<double>::INFINITO)
                dTotalDeimos += grKruskallDeimos[i][j];
        }
    }

    for (int i = 0; i < grKruskallFobos.numVert(); i++)
    {
        for (int j = 0; j < grKruskallFobos.numVert(); j++)
        {
            if (grKruskallFobos[i][j] != GrafoP<double>::INFINITO)
                dTotalFobos += grKruskallFobos[i][j];
        }
    }

    std::pair<int, int> verticesPuente = colocaMejorPuente(dTotalFobos, dTotalDeimos, vCosterasFobos, vCosterasDeimos);
    return std::make_pair(vDeimos[verticesPuente.first], vFobos[verticesPuente.second]);
}

int main()
{

    return 0;
}
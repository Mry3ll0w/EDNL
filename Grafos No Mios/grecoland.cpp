#include "../libGrafos/grafoPMC.h"
#include "../libGrafos/alg_grafoPMC.h"
#include "../libGrafos/listaenla.h"
#include <iostream>

/**
 * El archipiélago de Grecoland (Nozuelandia) está formado únicamente por tres islas:
Fobos, Deimos y Europa que tienen N1, N2 y N3 ciudades, respectivamente, todas ellas costeras.

Se dispone de la relación de ciudades de cada una de las tres islas, representadas por sus coordenadas cartesianas.

Dentro del programa COMUNICA de la ONU hemos conseguido fondos para comunicar todas las ciudades de Grecoland.
Las condiciones del programa COMUNICA indican que se sufragarán todos los costes de construcción
de las comunicaciones (carreteras y puentes) al MENOR coste posible.

Se sabe que la construcción de cualquier puente es más cara que la de cualquier carretera.
También es conocido que el coste de construcción de una carretera o de un puente es proporcional a su longitud.
En estas condiciones se debe calcular (mediante una función) qué carreteras y puentes deben
construirse para comunicar entre sí todas las ciudades de Grecoland, dados los siguientes datos:

    · Relación de ciudades de Fobos, representadas mediante sus coordenadas cartesianas.
    · Relación de ciudades de Deimos, representadas mediante sus coordenadas cartesianas.
    · Relación de ciudades de Europa, representadas mediante sus coordenadas cartesianas.
    · Coste unitario de construir una carretera
    · Coste unitario de construir un puente

 */

// Similar a las casillas del laberinto 2D
struct ciudad
{
    double x_, y_;
    ciudad(double x, double y) : x_(x), y_(y){};
};

// Une dos Ciudades de distintas islas
struct puente
{
    double coste;
    GrafoP<double>::vertice fobos, deimos;
};

// Calcula la distancia que separa 2 puntos concretos del mapa en COORDENADAS
double distaciaEuclidea(ciudad c1, ciudad c2)
{
    return std::sqrt(std::pow((c2.x_ - c1.x_), 2) + std::pow((c2.y_ - c1.y_), 2));
}

void grecoLandFixed(vector<ciudad> Fobos, vector<ciudad> Deimos, vector<ciudad> Europa, vector<GrafoP<double>::vertice> costerasFobos,
                    vector<GrafoP<double>::vertice> costerasDeimos, vector<GrafoP<double>::vertice> costerasEuropa, GrafoP<double>::vertice origen,
                    GrafoP<double>::vertice destino)
{

    struct Ciudad
    {
        double x, y;
        Ciudad(const double x_ = 0, const double y_ = 0) : x(x_), y(y_) {}
    };
}
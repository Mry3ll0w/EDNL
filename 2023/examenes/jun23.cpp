#include <iostream>
#include "../grafos/libGrafos/grafoPMC.h"
#include "../grafos/libGrafos/grafoMA.h"
#include "../grafos/libGrafos/alg_grafoPMC.h"

/**
 * Modelizaremos Narnia como una matriz de NxM casillas. Los
 * movimientos del fauno se modernizarán con los movimientos de
 * un caballo del ajedrez. Dicho de otra forma, cada movimiento del
 * fauno debe ser un movimiento de caballo de ajedrez.
 * A Narnia se llega a través de su entrada, casilla (0,0), y se marcha
 * uno a través de una única salida, en la casilla (N-1, M-1).
 * Sería un problema bastante fácil, pero Narnia es un país lleno de
 * peligros, en particular si eres un fauno.
 * Para empezar, los lugareños han puesto dentro de Narnia una
 * serie de trampas en determinadas casillas, de forma que si pasas
 * por ellas mueres.
 * Pero no contentos con eso, los habitantes de Narnia han
 * contratado Minos caballeros, que se colocan también en casillas
 * estratégicas. En este caso, el fauno no muerte si cae en una de
 * ellas, pero su muere en caso de caer en alguna de las casillas que
 * rodean al caballero, entre 3 y 8, dependiendo de su posición, ya
 * que su espada tiene longitud 1.
 *
 * El problema nos pide dos cosas, la primera saber si el fauno
 * puede hacer de forma segura el camino entre la entrada y la
 * salida de Narnia, y, en caso afirmativo, cual sería el número
 * mínimo de saltos necesarios para conseguirlo
 *
 * Datos
 * Laberinto es NxM
 * lista de casillas con trampa
 * lista de casillas con caballero
 *
 */

struct Casilla
{
    int x, y;
};

typedef Casilla Trampa;
typedef Casilla Caballero;

bool esAmenazadoPorCaballero(const Caballero &c)
{
}

// Determina el movimiento del Fauno
bool esColindanteFauno(Casilla casillaOrigen, Casilla cDestino)
{
}

int main()
{

    return 0;
}
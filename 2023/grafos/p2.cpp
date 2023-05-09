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
                    int iElementoIJ = MatrizCaminosMaximos[i][j];
                    int iElementoIK = MatrizCaminosMaximos[i][k];
                    int iElementoKJ = MatrizCaminosMaximos[k][j];

                    if (iElementoIJ == std::GrafoP<T>::INFINITO)
                        iElementoIJ = -1;
                    if (iElementoIK == std::GrafoP<T>::INFINITO)
                        iElementoIK = -1;
                    if (iElementoKJ == std::GrafoP<T>::INFINITO)
                        iElementoKJ = -1;

                    // Es necesario controlar los numeros infinitos
                    MatrizCaminosMaximos[i][j] = max(iElementoIJ, suma(iElementoIK, iElementoKJ));
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

// No se puede pasar directamente el grafo, hay que construirlo

//! El laberinto tiene n nodos * nfilas ==> La matriz de coste es de n^2 * n^2, ya
//! que si hay n2 nodos es de n4 casillas
//! No nos dan matriz de costes, hay que crearla

// Las casillas tienen un par de casillas
struct Casilla
{
    int iFila;
    int iColumna;
};

struct Pared
{
    // Las 2 paredes que delimitan
    Casilla c1, c2;
};

// Comprueba si las casillas son adyacentes, controla el movimiento, solo es
// Adyacente si esta dentro del movimiento permitido
bool sonAdyacentes(Casilla c1, Casilla c2)
{
    return std::abs(c1.iFila - c2.iFila + c1.iColumna - c2.iColumna) == 1; // Cuando difieren en 1
}

// Tenemos que comprobar que los nodos del grafo son adyacentes, por lo que pasamos
// de casilla a nodo.
template <class T>
Casilla NodoToCasilla(const int iNumNodo, const int n)
{
    Casilla c;
    c.iFila = iNumNodo / (n - 1);
    c.iColumna = iNumNodo & (n - 1);
    return c;
}

// Rellena la matriz de coste que representa al grafo
template <class T>
matriz<T> construyeMatrizCoste(const int &n)
{
    // Solo hay 3 valores 0, 1, infinito
    matriz<T> MatrizCoste(n * n);
    const int iCasillas = n * n;
    for (size_t i = 0; i < iCasillas; ++i)
    {
        for (size_t j = 0; j < iCasillas; ++j)
        {
            if (i == j)
            {
                MatrizCoste[i][j] = 0;
            }
            else if (sonAdyacentes(nodoToCasilla(i, n), nodoToCasilla(j, n))) // Son adyacentes
            {
                MatrizCoste[i][j] = 1;
            }
            else
            {
                MatrizCoste[i][j] = GrafoP<T>::INFINITO;
            }
        }
    }
}

// Pasar de casilla a nodo

int CasillaToNodo(const Casilla &c, const int &n)
{
    return (c.iFila * n + c.iColumna);
}

// Colocamos las paredes

template <class T>
void colocaParedes(matriz<T> &MatrizCoste, const int &n, std::list<Pared> lParedes)
{
    // Para saber donde colocar la pared hay que pasar de casilla a nodo
    for (auto i : lParedes)
    {
        int p1 = CasillaToNodo(i.c1, n), p2 = CasillaToNodo(i.c2, n);
        MatrizCoste[p1][p2] = std::GrafoP<T>::INFINITO;
        MatrizCoste[p2][p1] = std::GrafoP<T>::INFINITO;
    }
}

// Ahora tenemos la matriz de costes, tenemos que tratar el origen y destino, con Dijkstra
//  se acepta el camino como lo que deveulve Dijkstra
//  en este caso hay que pasar el camino de Nodos a casillas, ya que el camino de Dijkstra
//  es un vector de caminos de Nodos no casillas

template <class T>
std::vector<Casilla> caminoMasCorto(Casilla CasillaSalida, Casilla Destino, const int &n, std::list<Pared> lParedes)
{
    // Construimos la matriz de costes
    matriz<T> MatrizCoste = construyeMatrizCoste(n);

    // Colocamos la paredes
    colocaParedes(MatrizCoste, n, lParedes);

    int NodoOrigen = CasillaToNodo(CasillaSalida, n);
    int NodoDestino = CasillaToNodo(Destino, n);

    // Hacemos Dijsktra al grafo con los nodos de origen y destino

    GrafoP<T> GrafoLaberinto = MatrizCoste;
    std::vector<T> P; // Vector de camino en NODOS
    Dijkstra(GrafoLaberinto, NodoOrigen, P);

    // Camino mas corto ==> En P se almacena el camino, por lo que hacemos el camino reverso
    // pasandolo a casillas

    std::vector<Casilla> vCaminoCasillas;

    int i = Destino;
    while (i != NodoOrigen)
    {
        vCaminoCasillas.insert(vCaminoCasillas.begin(), NodoToCasilla(i, n));
        i = P[i];
    }

    return vCaminoCasillas;
}

/**
 * Eres el orgulloso dueño de una empresa de distribución. Tu misión radica en distribuir todo tu stock entre las diferentes ciudades en las que tu empresa dispone de almacén.
 * Tienes un grafo representado mediante la matriz de costes, en el que aparece el coste (por unidad de producto) de transportar los productos entre las diferentes ciudades del grafo.
 * Pero además resulta que los Ayuntamientos de las diferentes ciudades en las que tienes almacén están muy interesados en que almacenes tus productos en ellas, por lo que están dispuestos a subvencionarte con un porcentaje de los gastos mínimos de transporte hasta la ciudad.
 * Para facilitar el problema, consideraremos despreciables los costes de volver el camión a su base (centro de producción).
 * He aquí tu problema. Dispones de
 *  el centro de producción, nodo origen en el que tienes tu producto (no tiene almacén),
 *  una cantidad de unidades de producto (cantidad),
 *  la matriz de costes del grafo de distribución con N ciudades,
 *  la capacidad de almacenamiento de cada una de ellas,
 *  el porcentaje de subvención (sobre los gastos mínimos) que te ofrece cada
 * Ayuntamiento.
 * Las diferentes ciudades (almacenes) pueden tener distinta capacidad, y además la
 * capacidad total puede ser superior a la cantidad disponible de producto, por lo que debes decidir cuántas unidades de producto almacenas en cada una de las ciudades.
 * Debes tener en cuenta además las subvenciones que recibirás de los diferentes Ayuntamientos, las cuales pueden ser distintas en cada uno y estarán entre el 0% y el 100% de los costes mínimos.
 * La solución del problema debe incluir las cantidades a almacenar en cada ciudad bajo estas condiciones y el coste mínimo total de la operación de distribución para tu empresa.
 */

int main()
{

    return 0;
}

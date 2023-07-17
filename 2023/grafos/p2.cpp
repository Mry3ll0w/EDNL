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
 * Eres el orgulloso dueño de una empresa de distribución. Tu misión radica en distribuir
 * todo tu stock entre las diferentes ciudades en las que tu empresa dispone de almacén.
 * Tienes un grafo representado mediante la matriz de costes, en el que aparece el coste
 * (por unidad de producto) de transportar los productos entre las diferentes ciudades del grafo.
 * Pero además resulta que los Ayuntamientos de las diferentes ciudades en las que tienes almacén
 * están muy interesados en que almacenes tus productos en ellas, por lo que están dispuestos a
 * subvencionarte con un porcentaje de los gastos mínimos de transporte hasta la ciudad.
 * Para facilitar el problema, consideraremos despreciables los costes de volver el camión a su
 * base (centro de producción).
 * He aquí tu problema. Dispones de
 *  el centro de producción, nodo origen en el que tienes tu producto (no tiene almacén),
 *  una cantidad de unidades de producto (cantidad),
 *  la matriz de costes del grafo de distribución con N ciudades,
 *  la capacidad de almacenamiento de cada una de ellas,
 *  el porcentaje de subvención (sobre los gastos mínimos) que te ofrece cada
 * Ayuntamiento.
 * Las diferentes ciudades (almacenes) pueden tener distinta capacidad, y además la
 * capacidad total puede ser superior a la cantidad disponible de producto, por lo que debes
 * decidir cuántas unidades de producto almacenas en cada una de las ciudades.
 * Debes tener en cuenta además las subvenciones que recibirás de los diferentes Ayuntamientos,
 * las cuales pueden ser distintas en cada uno y estarán entre el 0% y el 100% de los costes
 * mínimos.
 * La solución del problema debe incluir las cantidades a almacenar en cada ciudad bajo estas
 * condiciones y el coste mínimo total de la operación de distribución para tu empresa.
 *
 * Datos que recibes:
 * Grafo/Matriz de costes
 * Vector de subvenciones
 *
 * Notas:
 *
 * Comprobar como aplicar subvenciones, es decir, todos las ciudades, hay que aplicar la
 * subvencion sobre los costes minimos
 *
 * SOLO APLICAR Dijsktra inverso cuando aparecen grafos dirigidos, es decir, si el camino
 * de ida puede ser distinto al de vuelta, en este caso la vuelta no es relevante implica
 * que vale lo mismo que la ida ==> Se aplica salvo que ocurra eso.
 */

// 1 aplicar subveciones a costes minimos de dijsktra

template <class T>
matriz<T> aplicarSubvenciones(matriz<T> grafo, vector<T> subvencionCiudades)
{
}

// Vaciado de almacenes en los que toque
//  hay que llenar el almacen antes de pasar al siguiente

/**
 * Problema 5:Se dispone de tres grafos que representan la matriz de costes para viajes en un
 * determinado país pero por diferentes medios de transporte, por supuesto todos los grafos
 * tendrán el mismo número de nodos. El primer grafo representa los costes de ir por
 * carretera, el segundo en tren y el tercero en avión. Dado un viajero que dispone
 * de una determinada cantidad de dinero, que es alérgico a uno de los tres medios de
 * transporte, y que sale de una ciudad determinada, implementar un subprograma que
 * determine las ciudades a las que podría llegar nuestro infatigable viajero.
 *
 * Notas:
 *  Los trasbordos se pueden hacer
 *  Requiere crear una combinacion entre grafos,
 *  Hay un Origen => No se hace Floyd
 *
 * 1) Se crea el grafo con los minimos de cada grafo M[i,j] = min(M1[i,j], M2[i,j])
 */

template <class T>
matriz<T> combinacionTransportes(const GrafoP<T> &g1, const GrafoP<T> &g2)
{
    matriz<T> MatrizResultado(g1.numVert());
    for (int i = 0; i < g1.numVert(); ++i)
    {
        for (int j = 0; j < g1.numVert(); ++j)
        {
            MatrizResultado[i][j] = std::min(g1[i][j], g2[i][j]);
        }
    }
    return MatrizResultado;
}

template <class T>
std::vector<T> ciudadesAlcanzables(const GrafoP<T> &GrafoAvion, const GrafoP<T> &GrafoCoche, const GrafoP<T> &GrafoTren, char &alergia, const int &iPresupuesto)
{
    GrafoP<T> g1, g2;
    if (c = 'T')
    {
        g1 = GrafoAvion;
        g2 = GrafoCoche;
    }
    else if (c == 'C')
    {
        g1 = GrafoAvion;
        g2 = GrafoTren;
    }
    else
    {
        g1 = GrafoCoche;
        g2 = GrafoTren;
    }

    // Aplico Dijkstra para cer a donde llega

    // Creo la lista con las ciudades a donde llega
}

/**
 * Al dueño de una agencia de transportes se le plantea la siguiente situación.
 * La agencia de viajes ofrece distintas trayectorias combinadas entre N ciudades
 * españolas utilizando tren y autobús. Se dispone de dos grafos que representan los
 * costes (matriz de costes) de viajar entre diferentes ciudades, por un lado en tren, y
 *  por otro en autobús (por supuesto entre las ciudades que tengan línea directa entre ellas).
 * Además coincide que los taxis de toda España se encuentran en estos momentos en huelga general,
 * lo que implica que sólo se podrá cambiar de transporte en una ciudad determinada en la que,
 * por casualidad, las estaciones de tren y autobús están unidas.
 * Implementa una función que calcule la tarifa mínima (matriz de costes mínimos) de viajar
 * entre cualesquiera de las N ciudades disponiendo del grafo de costes en autobús, del grafo
 * de costes en tren, y de la ciudad que tiene las estaciones unidas.
 *
 *  1) Floyd a ambas matrices originales => Minimizamos ir hasta el cambio
 *  2) Obtenemos la suma del cambio
 */

template <typename tCoste>
matriz<tCoste> tarifa_minima(typename GrafoP<tCoste>::vertice cambio,
                             const GrafoP<tCoste> &tren,
                             const GrafoP<tCoste> &autobus)
{
    typedef typename GrafoP<tCoste>::vertice vertice;
    const size_t N = tren.numVert();

    matriz<vertice> P;
    // Obtenemos los mejores costes de viajar por cada uno
    // de los medios dados
    auto tren_floyd = Floyd(tren, P);
    auto autobus_floyd = Floyd(autobus, P);

    matriz<tCoste> tarifa(N);

    // Para cada ruta i->j, obtenemos qué viaje es mejor:
    // - viajar únicamente en tren
    // - viajar únicamente en bús
    // - viajar en tren, cambiar, y después en bús
    // - viajar en bís, cambiar, y después en tren
    for (vertice i = 0; i < N; i++)
        for (vertice j = 0; j < N; j++)
            tarifa[i][j] = std::min({
                tren_floyd[i][j],
                autobus_floyd[i][j],
                suma(autobus_floyd[i][cambio], tren_floyd[cambio][j]), // Para que sirve esa suma
                suma(tren_floyd[i][cambio], autobus_floyd[cambio][j]),
            });

    return tarifa;
}

/**
 * Problema 6:
 * Se dispone de dos grafos (matriz de costes) que representan los costes de viajar entre N
 * ciudades españolas utilizando el tren (primer grafo) y el autobús (segundo grafo).
 * Ambos grafos representan viajes entre las mismas N ciudades.
 * Nuestro objetivo es hallar el camino de coste mínimo para viajar entre dos ciudades
 * concretas del grafo, origen y destino, en las siguientes condiciones:
 *  La ciudad origen sólo dispone de transporte por tren.
 *  La ciudad destino sólo dispone de transporte por autobús.
 *  El sector del taxi, bastante conflictivo en nuestros problemas, sigue en huelga,
 * por lo que únicamente es posible cambiar de transporte en dos ciudades del grafo,
 * cambio1 y cambio2, donde las estaciones de tren y autobús están unidas.
 *
 * Implementa un subprograma que calcule la ruta y el coste mínimo para viajar entre las
 * ciudades Origen y Destino en estas condiciones.
 *
 * Posibles viajes:
 * 1) Origen -> cambio1 -> Destino
 * 2) Origen -> cambio2 -> Destino
 * Es obligatorio cambiar puesto que el origen solo tiene tren y el destino solo tiene bus
 *
 * Pasos
 * 1) Dijsktra de origen al cambio1 y DijsktraInverso de cambio1 a Destino => Sumo el ambos y tengo el total1
 * 2) Dijsktra de origen al cambio2 y DijstktraInverso de cambio2 a Destino => "" total2
 *
 */

int main()
{

    return 0;
}

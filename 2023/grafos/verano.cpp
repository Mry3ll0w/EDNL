#include <iostream>
#include "libGrafos/alg_grafoPMC.h"
#include <list>
using namespace std; // Avoid using std:: ....

/**
 * Repaso de EDNL de grafos y arboles para verano de 2023
 * No se trata de hacer todos y cada uno de los ejercicios si no los mas frecuentes.
 */

/**
 * Ejercicio 3 P1 Grafos.
 * Tu empresa de transportes “PEROTRAVEZUNGRAFO S.A.” acaba de recibir la lista de posibles subvenciones del Ministerio de
 * Fomento en la que una de las más jugosas se concede a las empresas cuyo grafo asociado a su matriz de costes sea acíclico.
 * ¿Puedes pedir esta subvención?
 * Implementa un subprograma que a partir de la matriz de costes nos indique si tu empresa tiene derecho a dicha subvención.
 *
 * Objetivo ==> Puedo solicitar la subvencion para los aciclicos?
 * Datos necesarios ==>
 * 1) Recibo Matriz de costes NO GRAFO, por lo que es necesario crear un grafo
 * 2) Grafo Aciclico ==> Un grafo acliclico es aque cuyos nodos no poseen ciclos, es decir, caminos en los que se apuntan a si mismos
 *
 *
 */

// 1) Pasamos la matriz de costes a matriz de adyacencia
matriz<bool> conversorPonderadaAdyacencia(const GrafoP<int> &G)
{
    matriz<bool> MatrizbAdyacencia(G.numVert());
    for (size_t i = 0; i < G.numVert(); i++)
    {
        for (size_t j = 0; j < G.numVert(); j++)
        {
            MatrizbAdyacencia[i][j] = G[i][j] != GrafoP<int>::INFINITO;
        }
    }
    return MatrizbAdyacencia;
}

// Usando Warshall sin el primer bucle comprobamos que es posible ir de un nodo a si mismo, si es posible existen ciclos por lo
// no tendriamos un grafo aciclico.
void floydModCiclicos(matriz<bool> &Grafo, const int n)
{
    // Como vamos a comprobar ciclos simplemente eliminamos la primera parte
    for (int k = 0; k < n; ++k)
    {
        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < n; j++)
            {
                Grafo[i][j] = Grafo[i][k] || (Grafo[i][k] && Grafo[k][j]);
            }
        }
    }
}

bool esAciclica(GrafoP<int> &Grafo)
{
    matriz<bool> MatrizAdyacencia(Grafo.numVert());
    MatrizAdyacencia = conversorPonderadaAdyacencia(Grafo);
    floydModCiclicos(MatrizAdyacencia, Grafo.numVert());
    for (int i = 0; i < Grafo.numVert(); i++)
    {
        if (MatrizAdyacencia[i][i])
            return false;
    }
    return true;
}

/**
 * Ejercicio 4 Practica 1 Grafos
 * Se necesita hacer un estudio de las distancias mínimas necesarias para viajar entre dos ciudades cualesquiera de un país llamado Zuelandia.
 * El problema es sencillo pero hay que tener en cuenta unos pequeños detalles:
 * a) La orografía de Zuelandia es un poco especial, las carreteras son muy estrechas y por tanto solo permiten un sentido de la circulación.
 *
 * ==> Se trata de un grafo dirigido y unidireccional
 *
 * b) Actualmente Zuelandia es un país en guerra. Y de hecho hay una serie de ciudades del país que han sido tomadas por los rebeldes,
 * por lo que no pueden ser usadas para viajar. ==> Hay que poner a INFINITO las ciudades tomadas
 *
 * c) Los rebeldes no sólo se han apoderado de ciertas ciudades del país, sino que también han cortado ciertas carreteras,
 * (por lo que estas carreteras no pueden ser usadas).==> Se cortan las carreteras que salen de las ciudades rebeldes
 *
 * d) Pero el gobierno no puede permanecer impasible ante la situación y ha exigido que absolutamente todos los viajes que
 * se hagan por el país pasen por la capital del mismo, donde se harán los controles de seguridad pertinentes.
 * ==> Los viajes se hacen desde Origen X a Capital y desde Capital a Origen X (Dijkstra normal y Dijkstra inverso)
 *
 * Dadas estas cuatro condiciones, se pide implementar un subprograma que dados
 * • el grafo (matriz de costes) de Zuelandia en situación normal,
 * • la relación de las ciudades tomadas por los rebeldes,
 * • la relación de las carreteras cortadas por los rebeldes
 * • y la capital de Zuelandia.
 *
 * Calcule la matriz de costes mínimos para viajar entre cualesquiera dos ciudades zuelandesas en esta situación.
 *
 */

// Funcion que pasa de matriz de coste a grafo, ya que recibimos una matriz no un grafo
template <class T>
GrafoP<T> matrizCoste2GrafoP(const matriz<T> &matriz)
{
    GrafoP<T> grafo(matriz.dimension());
    for (int i = 0; i < matriz.dimension(); i++)
    {
        for (int j = 0; j < matriz.dimension(); j++)
        {
            grafo[i][j] = matriz[i][j];
        }
    }
    return grafo;
}

template <class T>
void eliminarCiudadesTomadas(std::list<int> lCiudadesTomadas, GrafoP<int> &grafoZuelandia)
{
    for (auto i : lCiudadesTomadas)
    {
        for (int j = 0; j < grafoZuelandia.numVert(); j++)
        {
            // Cortamos desde ir a la ciudad y hacia la ciudad
            grafoZuelandia[i][j] = GrafoP<T>::INFINITO;
            grafoZuelandia[j][i] = GrafoP<T>::INFINITO;
        }
    }
}

template <class T>
void eliminarCarreterasTomadas(const std::list<std::pair<int, int>> lCarreterasTomadas, GrafoP<T> &grafoZuelandia)
{
    for (auto i : lCarreterasTomadas)
    {
        grafoZuelandia[i.first][i.second] = grafoZuelandia[i.second][i.first] = GrafoP<T>::INFINITO;
    }
}

template <class T>
matriz<int> caminosMinimosZuelandia(const matriz<T> &matrizCostes, const std::list<int> lCiudadesTomadas,
                                    const std::list<std::pair<int, int>> &lCarreterasTomadas, const int &iCapital)
{
    GrafoP<int> grafoZuelandia = matrizCoste2GrafoP(matrizCostes);
    eliminarCarreterasTomadas(lCarreterasTomadas, grafoZuelandia);
    eliminarCiudadesTomadas(lCiudadesTomadas, grafoZuelandia);

    // Si no lo esta calculamos los costes minimos
    matriz<T> matrizCostesMinimos(grafoZuelandia.numVert());
    for (int i = 0; i < grafoZuelandia.numVert(); i++)
    {
        for (int j = 0; j < grafoZuelandia.numVert(); j++)
        {
            int iCosteMinimo = 0;
            std::vector<T> costesOrigenCapital = Dijkstra(grafoZuelandia, i, std::vector<T>());
            iCosteMinimo = suma(iCosteMinimo, costesOrigenCapital[iCapital]);
            std::vector<T> costesCapitalDestino = DijkstraInv_(grafoZuelandia, j, std::vector<T>());
            iCosteMinimo = suma(iCosteMinimo, costesCapitalDestino[iCapital]);
            matrizCostesMinimos[i][j] = iCosteMinimo;
        }
    }
    return matrizCostesMinimos;
}

/**
 * Ejercicio 1 P2 Grafos
 * Tu agencia de viajes “OTRAVEZUNGRAFO S.A.” se enfrenta a un curioso cliente. Es un personaje sorprendente, no le importa el dinero
 * y quiere hacer el viaje más caro posible entre las ciudades que ofertas.
 * Su objetivo es gastarse la mayor cantidad de dinero posible (ojalá todos los clientes fueran así), no le importa el origen
 * ni el destino del viaje.
 * Sabiendo que es imposible pasar dos veces por la misma ciudad, ya que casualmente el grafo de tu agencia de ==> Recibo un grafo
 * viajes resultó ser acíclico, devolver el coste, origen y destino de tan curioso viaje.
 * Se parte de la matriz de costes directos entre las ciudades del grafo.
 *
 * Simplemente modificamos el algoritmo de Floyd para poder realizar viajes con coste maximo
 */

std::pair<int, int> viajeMasCaro(GrafoP<int> grafo)
{
    for (int i = 0; i < grafo.numVert(); ++i)
    {
        grafo[i][i] = 0;
    }
    for (int k = 0; k < grafo.numVert(); k++)
    {
        for (int i = 0; i < grafo.numVert(); i++)
        {
            for (int j = 0; j < 0; j++)
            {
                grafo[i][j] = std::max(grafo[i][j], suma(grafo[i][k], grafo[k][j]));
            }
        }
    }
}

/**
 * LABERINTO, suele caer en examenes variantes de 2 dimensiones y 3 dimensiones
 *
 * Se dispone de un laberinto de NxN casillas del que se conocen las casillas de entrada y salida del mismo.
 * Si te encuentras en una casilla sólo puedes moverte en las siguientes cuatro direcciones
 * (arriba, abajo, derecha, izquierda).
 * Por otra parte, entre algunas de las casillas hay una pared que impide moverse entre las dos casillas
 * que separa dicha pared (en caso contrario no sería un verdadero laberinto).
 * Implementa un subprograma que dados
 * · N (dimensión del laberinto),
 * · la lista de paredes del laberinto,
 * · la casilla de entrada, y
 * · la casilla de salida,
 *
 * Calcule el camino más corto para ir de la entrada a la salida y su longitud.
 *
 * 1) Crear la matriz de costes, ya que nos dan un grafo laberinto, n por n casillas, siendo la matriz de coste
 * asociada de n^2 * n^2 casillas
 *
 * 2) Calcular los costes de moverse entre casillas teniendo en cuenta lo anterior
 *
 * 3) Hacer Dijkstra para ir de la casilla Origen a la casilla de Destino
 *
 * 4) Por el camino vamos a necesitar multiples funciones de apoyo para irnos moviendo en el laberinto
 *
 */

// Las casillas tienen un par de casillas struct Casilla
struct Casilla
{
    int iFila;    //* Posicion X en el laberinto
    int iColumna; //* Posicion Y en el laberinto
};

// Representa la pared que delimita el movimiento entre 2 casillas
struct Pared
{
    //* Las 2 paredes que delimitan
    Casilla c1, c2;
};

// Comprueba si las casillas son adyacentes, controla el movimiento, solo es
// Adyacente si esta dentro del movimiento permitido, haciendo asi que se limiten los movimientos de Dijkstra.
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
GrafoP<T> construyeMatrizCoste(const int &n)
{
    // Solo hay 3 valores 0, 1, infinito para que Dijkstra cuente el numero de movimientos como coste para la matriz.
    GrafoP<T> MatrizCoste(n * n);
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
                //* Solo permitimos el movimiento si 2 casillas son adyacentes, por lo que i y j representan nodos de la matriz
            }
            else
            {
                MatrizCoste[i][j] = GrafoP<T>::INFINITO;
            }
        }
    }
}

// Pasar de casilla a nodo, necesitamos esta funcion para la colocacion de las paredes del laberinto
// puesto que la lista de paredes son representadas por elementos con las 2 casillas que limitan,
// teniendo que pasar de casilla del laberinto a nodo de la matriz de costes.

int CasillaToNodo(const Casilla &c, const int &n)
{
    return (c.iFila * n + c.iColumna);
}

// Colocamos las paredes

template <class T>
void colocaParedes(GrafoP<T> &MatrizCoste, const int &n, std::list<Pared> lParedes)
{
    // Para saber donde colocar la pared hay que pasar de casilla a nodo
    for (auto i : lParedes)
    {
        int p1 = CasillaToNodo(i.c1, n), p2 = CasillaToNodo(i.c2, n);
        MatrizCoste[p1][p2] = std::GrafoP<T>::INFINITO;
        MatrizCoste[p2][p1] = std::GrafoP<T>::INFINITO;
    }
}

template <class T>
std::pair<int, std::vector<Casilla>> caminoMasCortoLaberinto2D(const int &iDimensionLaberinto, const Casilla &casillaEntrada,
                                                               const Casilla &casillaSalida, std::list<Pared> lParedes)
{
    GrafoP<T> matrizCoste(iDimensionLaberinto);
    matrizCoste = construyeMatrizCoste(iDimensionLaberinto);
    colocaParedes(matrizCoste, iDimensionLaberinto, lParedes);

    // Pasamos las casillas Origen y destino a su forma de nodo de la matriz para aplicarles Dijkstra
    auto nodoOrigen = CasillaToNodo(casillaEntrada, iDimensionLaberinto);
    auto nodoDestino = CasillaToNodo(casillaSalida, iDimensionLaberinto);
    std::vector<T> P;
    std::vector<T> aCostesMinimos = (matrizCoste, nodoOrigen, P);
    // Hallamos el camino
    int i = nodoDestino;
    std::vector<Casilla> aCamino;
    while (i != nodoOrigen)
    {
        aCamino.push_back(NodoToCasilla(i, iDimensionLaberinto));
        i = P[i];
    }

    return std::make_pair(aCostesMinimos[nodoDestino], aCamino);
}

/**
 * Problema 3 Practica 2 Grafos
 *
 * 3. Eres el orgulloso dueño de una empresa de distribución. Tu misión radica en distribuir todo tu stock entre las diferentes ciudades
 * en las que tu empresa dispone de almacén.
 * Tienes un grafo representado mediante la matriz de costes, en el que aparece el coste (por unidad de producto) de transportar los
 * productos entre las diferentes ciudades del grafo. ==> Tengo matriz de costes bidimensional
 * Pero además resulta que los Ayuntamientos de las diferentes ciudades en las que tienes almacén están muy interesados en que
 * almacenes tus productos en ellas, por lo que están dispuestos a subvencionarte con un porcentaje de los gastos mínimos de
 * transporte hasta la ciudad. ==> Lista de ciudades junto con su subvencion correspondiente
 *
 * Para facilitar el problema, consideraremos despreciables los costes de volver el camión a su base (centro de producción).
 * He aquí tu problema.
 *
 * Dispones de ==> DATOS CON LOS QUE PARTIMOS
 * · El centro de producción, nodo origen en el que tienes tu producto (no tiene almacén),
 * · Una cantidad de unidades de producto (cantidad),
 * · La matriz de costes del grafo de distribución con N ciudades,
 * · La capacidad de almacenamiento de cada una de ellas,
 * · El porcentaje de subvención (sobre los gastos mínimos) que te ofrece cada Ayuntamiento.
 *
 * Las diferentes ciudades (almacenes) pueden tener distinta capacidad, y además la capacidad total puede ser superior a
 * la cantidad disponible de producto, por lo que debes decidir cuántas unidades de producto almacenas en cada una de las ciudades.
 * Debes tener en cuenta además las subvenciones que recibirás de los diferentes Ayuntamientos, las cuales pueden ser distintas en
 * cada uno y estarán entre el 0% y el 100% de los costes mínimos.
 * La solución del problema debe incluir las cantidades a almacenar en cada ciudad bajo estas condiciones y el coste mínimo total
 * de la operación de distribución para tu empresa.
 */

template <class T>
void aplicaSubvenciones(const std::list<std::pair<int, double>> &lCiudadSubvencion, GrafoP<T> &grafo)
{
    for (auto oneCity : lCiudadSubvencion)
    {
        for (int j = 0; j < grafo.numVert(); j++)
        {
            grafo[oneCity.first][j] = grafo[oneCity.first][j] * (1 - oneCity.second);
            grafo[j][oneCity.first] = grafo[j][oneCity.first] * (1 - oneCity.second);
        }
    }
}

// Algoritmo de reparto en si
template <class T>
std::pair<double, std::list<T>> repartoStockCiudades(GrafoP<T> grafoP, int stock, const T &centroProduccion,
                                                     const std::list<std::pair<int, double>> &lCiudadSubvencion)
{
    //! FALTA POR REPARTIR LAS CARGAS
}

int main()
{

    return 0;
}
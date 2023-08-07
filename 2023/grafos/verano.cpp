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
void eliminarCiudadesTomadas(std::list<T> lCiudadesTomadas, GrafoP<int> &grafoZuelandia)
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
 *
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
    // Hallamos el maximo
    int maximo, iMax, jMax;
    maximo = iMax = jMax = 0;

    for (int i = 0; i < grafo.numVert(); ++i)
    {
        for (size_t j = 0; j < grafo.numVert(); j++)
        {
            if (maximo < grafo[i][j])
            {
                maximo = grafo[i][j];
                iMax = i;
                jMax = j;
            }
        }
    }

    return std::make_pair(iMax, jMax);
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
            else if (sonAdyacentes(NodoToCasilla(i, n), NodoToCasilla(j, n))) // Son adyacentes
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
        MatrizCoste[p1][p2] = GrafoP<T>::INFINITO;
        MatrizCoste[p2][p1] = GrafoP<T>::INFINITO;
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
    std::vector<T> aCostesMinimos = Dijkstra(matrizCoste, nodoOrigen, P);
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
 * Eres el orgulloso dueño de una empresa de distribución. Tu misión radica en distribuir todo tu stock entre las diferentes ciudades
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
            grafo[j][oneCity.first] = grafo[j][oneCity.first] * (1 - oneCity.second);
        }
    }
}

// Algoritmo de reparto en si
template <class T>
std::pair<double, std::list<T>> repartoStockCiudades(GrafoP<T> grafoCostesCiudad, const std::vector<int> aCapacidacidadCidudad, int stock, const T &centroProduccion,
                                                     const std::list<std::pair<int, double>> &lCiudadSubvencion)
{
    int iDescargas = 0;
    int stockOriginal = stock;
    std::vector<int> aCantidadesGuardadasEnCiudad(grafoCostesCiudad.numVert(), 0);
    aplicaSubvenciones(lCiudadSubvencion, grafo); // Aplicamos a los costes de ir a la ciudad la rebaja del total
    T &nodoActual = centroProduccion;
    do
    {
        // Calculamos el mejor desde el nodo de produccion
        std::vector<T> aCostes = Dijkstra(grafoCostesCiudad, nodoActual, std::vector<T>());
        T nodoMejor = 1; // El siguiente despues de el mismo

        for (int i = 1; i < aCostes.size(); ++i)
        {
            if (aCostes[nodoMejor] > aCostes[i] && aCapacidacidadCidudad[nodoMejor] > 0) // Buscamos el de menor coste
            {
                nodoMejor = i;
            }
        }

        // Comprobamos que llegamos con el stock actual
        if (stock >= aCapacidacidadCidudad[nodoMejor]) // Si llegamos con lo que tenemos repartimos a la ciudad
        {
            // Obtenemos cuanto dejamos en esa ciudad
            stock -= aCapacidacidadCidudad[nodoMejor];
            aCantidadesGuardadasEnCiudad[nodoMejor] = aCapacidacidadCidudad[nodoMejor];
            nodoActual = nodoMejor;
        }
        else // No llegamos, con lo que tenemos, por lo que dejamos y volvemos al punto inicial
        {
            aCantidadesGuardadasEnCiudad[nodoMejor] = stock;
            stock = 0;
        }
        iDescargas++;
    } while (iDescargas < grafoCostesCiudad.numVert() && stock > 0);
}

/**
 *
 * El zuelandés es una persona que se toma demasiadas “libertades” en su trabajo,
 * de hecho, tienes fundadas sospechas de que tus conductores utilizan los camiones de la empresa para usos particulares (es decir indebidos, y a tu costa)
 * por lo que quieres controlar los kilómetros que recorren tus camiones.
 *
 * Todos los días se genera el parte de trabajo, en el que se incluyen el número de cargas de cemento (1 carga = 1 camión lleno de cemento) que
 * debes enviar a cada cliente (cliente = ciudad de Zuelandia). Es innecesario indicar que no todos los días hay que enviar cargas a todos los clientes,
 * y además, puedes suponer razonablemente que tu flota de camiones es capaz de hacer el trabajo diario.
 * Para la resolución del problema quizá sea interesante recordar que Zuelandia es un país cuya especial orografía sólo permite que las carreteras
 * tengan un sentido de circulación. ==> Grafo Dirigido
 *
 * Implementa una función que
 * dado el grafo con las distancias directas entre las diferentes ciudades zuelandesas,
 * el parte de trabajo diario, y
 * la capital de Zuelandia, ==> Desde donde parte el camion (ya sea para carga y/o descarga)
 * devuelva la distancia total en kilómetros que deben recorrer tus camiones en el día, para que puedas descubrir si
 * es cierto o no que usan tus camiones en actividades ajenas a la empresa.
 *
 * Datos
 *  1) Grafo Distancias directas entre ciudades
 *  2) Desde donde salen los camiones
 *  3) Parte de Trabajo ==> Entiendo que la lista de sitios que tienen que ir en total, asumo que he de calcular la suma total de las distancias
 *
 */

template <class T>
struct ParteTrabajo
{
    int iCargas;
    T &ciudad;
    ParteTrabajo(cosnt T &c = T(), const int &cargas = 0) : iCargas(cargas), ciudad(c) {}
};

template <class T>
bool totalDistanciaCamionesZuelandia(const T &totalDistanciasdada, const GrafoP<T> grafoDistancias, std::vector<ParteTrabajo<T>> vTrabajo, const T &capitalZuelandia)
{
    T nodoActual = capitalZuelandia;
    T &distanciaRecorrida = 0;
    for (int i = 0; i < grafoDistancias.numVert(); i++)
    {
        while (vTrabajo[i].iCargas > 0)
        {
            std::vector<T> aCostesIda = Dijkstra(grafoDistancias, nodoActual, std::vector<T>());
            distanciaRecorrida += aCostesIda[vTrabajo[i].ciudad];
            nodoActual = vTrabajo[i].ciudad;
            vTrabajo[i].iCargas--; // Descargamos el cargamento
            // Calculamos el camino de vuelta desde donde hemos descargado a la capital
            std::vector<T> aCostesVuelta = DijsktraInverso(grafoDistancias, capitalZuelandia, std::vector<T>());
            distanciaRecorrida += aCostesVuelta[vTrabajo[i].ciudad];
            nodoActual = capitalZuelandia;
        }
        // Hacemos Dijkstra desde el nodo en el que estamos hasta el que no tenemos mas partes a repartir
        nodoActual = capitalZuelandia;
    }
    return totalDistanciasdada == distanciaRecorrida;
}

/**
 * Se dispone de tres grafos que representan la matriz de costes para viajes en un determinado país pero por diferentes medios de
 * transporte, por supuesto todos los grafos tendrán el mismo número de nodos. El primer grafo representa los costes de ir por carretera,
 * el segundo en tren y el tercero en avión. Dado un viajero que dispone de una determinada cantidad de dinero, que es alérgico a uno
 * de los tres medios de transporte, y que sale de una ciudad determinada, implementar un subprograma que determine las ciudades
 * a las que podría llegar nuestro infatigable viajero.
 */

GrafoP<int> combinacionesGrafos(const GrafoP<int> g1, const GrafoP<int> g2)
{
    GrafoP<int> grafoResultado(g1.numVert());
    for (int i = 0; i < g1.numVert(); i++)
    {
        for (int j = 0; j < g1.numVert(); j++)
        {
            grafoResultado[i][j] = std::min(g1[i][j], g2[i][j]);
        }
    }
    return grafoResultado;
}

template <class T>
std::vector<int> viajeroAlergico5(const char &cAlergia, GrafoP<int> grafoTren, GrafoP<int> grafoAvion,
                                  GrafoP<int> grafoCoche, const int &presupuesto, const int &origen)
{
    GrafoP<int> grafoResultado(grafoAvion.numVert());
    if (cAlergia == 'c')
    {
        grafoResultado = combinacionesGrafos(grafoAvion, grafoTren);
    }
    else if (cAlergia == 't')
    {
        grafoResultado = combinacionesGrafos(grafoAvion, grafoCoche);
    }
    else
    {
        grafoResultado = combinacionesGrafos(grafoCoche, grafoTren);
    }

    // Hallamos los costes minimos
    std::vector<int> aCostes = Dijkstra(grafoResultado, origen, std::vector<int>());
    for (auto i : aCostes)
    {
        if (i > presupuesto)
            i = -1;
    }
    return aCostes;
}

/**
 * Ejercicio 6:
 *
 * Al dueño de una agencia de transportes se le plantea la siguiente situación.
 * La agencia de viajes ofrece distintas trayectorias combinadas entre N ciudades españolas utilizando tren y autobús.
 * Se dispone de dos grafos que representan los costes (matriz de costes) de viajar entre diferentes ciudades, por un lado en tren,
 * y por otro en autobús (por supuesto entre las ciudades que tengan línea directa entre ellas). Además coincide que los taxis de
 * toda España se encuentran en estos momentos en huelga general, lo que implica que sólo se podrá cambiar de transporte en una
 * ciudad determinada en la que, por casualidad, las estaciones de tren y autobús están unidas.
 *
 * Implementa una función que calcule la tarifa mínima (matriz de costes mínimos) de viajar entre cualesquiera de las N ciudades
 * disponiendo del grafo de costes en autobús, del grafo de costes en tren, y de la ciudad que tiene las estaciones unidas.
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
    auto tren_floyd = Floyd(tren, P); // Usamos Floyd puesto que nos piden la matriz de costes minimos no ir de A hacia B
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
                suma(autobus_floyd[i][cambio], tren_floyd[cambio][j]), // Hacemos los minimos entre ir al sitio usando solo tren
                suma(tren_floyd[i][cambio], autobus_floyd[cambio][j]), // solo tren y bus con los cambios pertinentes
            });

    return tarifa;
}

/**
 * Ejercicio 7:
 *  Se dispone de dos grafos (matriz de costes) que representan los costes de viajar entre N ciudades españolas utilizando el t
 * ren (primer grafo) y el autobús (segundo grafo).
 * Ambos grafos representan viajes entre las mismas N ciudades.
 * Nuestro objetivo es hallar el camino de coste mínimo para viajar entre dos ciudades concretas del grafo, origen y destino,
 * en las siguientes condiciones:
 *
 * · La ciudad origen sólo dispone de transporte por tren.
 *
 * · La ciudad destino sólo dispone de transporte por autobús.
 *
 * · El sector del taxi, bastante conflictivo en nuestros problemas, sigue en huelga,
 *   por lo que únicamente es posible cambiar de transporte en dos ciudades del grafo, cambio1 y cambio2,
 *   donde las estaciones de tren y autobús están unidas.
 *
 * Implementa un subprograma que calcule la ruta y el coste mínimo para viajar entre las ciudades Origen y Destino en
 * estas condiciones. ==> Nos hablan de coste minimo entre A y B, por lo que seria necesario trabajar con Dijsktra
 */

/**
 *  Necesitamos crear un supergrafo para calcular los saltos entre g1 y g2 y viceversa
 *  Pasos:
 *      1) Tamaño del grafo es numvert por el numero de Grafos que tenemos
 *      2) Cuadrante 0, 0 es el grafo 1 y cuadrante 1,1 es g2, rellenando el resto
 *      de INFINITO
 *      3) El resto de cuadrantes se rellenan a INF salco la diag ppal que se rellena
 *      con el precio del cambio
 */
template <class T>
GrafoP<T> creaSuperGrafoDoble(const GrafoP<T> &g1, const GrafoP<T> &g2, const T &costeAdicional = 0)
{
    size_t n = g1.numVert() + g2.numVert();
    GrafoP<T> SuperGrafo(n);

    // Rellenamos el grafo completo a INFITO
    for (int i = 0; i < n; ++i)
    {
        for (int j = 0; j < n; j++)
        {
            // Cuadrante perteneciente al grafo 1 0,0
            SuperGrafo[i][j] = GrafoP<T>::INFINITO;
        }
    }

    // Rellenamos el grafo con los valores necesarios para el problema
    for (int i = 0; i < n; ++i)
    {
        for (int j = 0; j < n; j++)
        {
            // Cuadrante perteneciente al grafo 1 0,0
            SuperGrafo[i][j] = g1[i][j];
            // Cuadrante perteneciente al grafo 2 c2 0,1
            SuperGrafo[i + n][j + n] = g2[i][j];

            // Cuadrante 1 0 DIAGONALES
            SuperGrafo[i][i + n] = costeAdicional;

            // Cuadrante 1 1 DIAGONALES
            SuperGrafo[i + n][i] = costeAdicional;
        }
    }
}

template <class T>
T costesMinimosTrenAvion(const GrafoP<T> gTren, const GrafoP<T> gBus, const typename GrafoP<T>::vertice cambio1, const typename GrafoP<T>::vertice cambio2,
                         const T &origen, const T &destino)
{
    // Creamos el superGrafo con los costes de ir en tren directamente y costes de ir en bus directamente para poder hacer Dijkstra correctamente
    GrafoP<T> sg = creaSuperGrafoDoble(gTren, gBus);
    const int n = gTren.numVert();
    // Tenemos que tener en cuenta que solo se permiten los cambios en c1 y c2 por lo que tendremos que ir a cada cuadrante del cambio y ponerlos a 0
    // Para esto ponemos cada una de las posiciones donde se permite el cambio a 0

    sg[cambio1][cambio1 + n] = 0; // Cambio1 en cuadrante 0 1 solo en tren
    sg[cambio1 + n][cambio1] = 0; // Cambio1 en cuadrante 1, solo en bus
    sg[cambio2][cambio2 + n] = 0; // igual con cambio 2 s
    sg[cambio2 + n][cambio2] = 0;

    // Aplicamos Dijkstra
    std::vector<T> costesMinimos = Dijkstra(sg, origen, std::vector<T>());

    return costesMinimos[destino];
}

/**
 * Ejercicio 8
 * “UN SOLO TRANSBORDO, POR FAVOR”. Este es el título que reza en tu flamante compañía de viajes. Tu publicidad explica, por supuesto,
 * que ofreces viajes combinados de TREN y/o AUTOBÚS (es decir, viajes en tren, en autobús, o usando ambos), entre N ciudades del país,
 * que ofreces un servicio inmejorable, precios muy competitivos, y que garantizas ante notario algo que no ofrece ninguno de tus competidores:
 * que en todos tus viajes COMO MÁXIMO se hará un solo transbordo (cambio de medio de transporte).
 * Bien, hoy es 1 de Julio y comienza la temporada de viajes.
 * ¡Qué suerte! Acaba de aparecer un cliente en tu oficina. Te explica que quiere viajar entre dos ciudades, Origen y Destino, y quiere saber
 * cuánto le costará.
 * Para responder a esa pregunta dispones de:
 *  dos grafos de costes directos (matriz de costes) de viajar entre las N ciudades del país,
 * un grafo con los costes de viajar en tren y otro en autobús.
 * Implementa un subprograma que calcule la tarifa mínima en estas condiciones.
 * Mucha suerte en el negocio, que la competencia es dura.
 */

template <class T>
void viajeUnicoTransbordo(const GrafoP<T> gBus, const GrafoP<T> gTren, const T &origen, const T &destino)
{
    // Se hace "a lo bestia"
    std::vector<T> costesMinimosSoloBus = Dijkstra(gBus, origen, std::vector<T>());
    std::vector<T> costesMinimosSoloTren = Dijkstra(gBus, origen, std::vector<T>());

    // Suponemos de hacer un unico cambio en una posicion x, por lo que hacemos del destino al resto
    std::vector<T> aCambioCostesMinimosBusTren = DijkstraInverso(gTren, destino, std::vector<T>());
    std::vector<T> aCambioCostesMinimosTrenBus = DijsktraInverso(gBus, destino, std::vector<T>());

    // Comprobamos cual es el de menor coste
    T costeMinimoTotal = GrafoP<T>::INFINITO;
    for (int i = 0; i < costesMinimosSoloBus.size(); ++i)
    {
        // Calculamos que seria mas rentable, si hacer el cambio en i o ir completo con el medio original
        costeMinimoTotal = std::min(costesMinimosTotales[i], costesMinimosSoloBus[i], costesMinimosSoloTren[i],
                                    suma(costesMinimosSoloBus[i], aCambioCostesMinimosBusTren[i]), suma(costesMinimosSoloTren[i], aCambioCostesMinimosTrenBus[i]));
    }
    return min(costeMinimoTotal, costesMinimosSoloBus[destino], costesMinimosSoloTren[destino]);
}

/**
 * Ejercicio 9
 * Se dispone de dos grafos que representan la matriz de costes para viajes en un determinado país, pero por diferentes medios de transporte
 * (tren y autobús, por ejemplo). Por supuesto ambos grafos tendrán el mismo número de nodos, N. Dados ambos grafos, una ciudad de origen,
 * una ciudad de destino y el coste del taxi para cambiar de una estación a otra dentro de cualquier ciudad (se supone constante e igual para todas las ciudades),
 * implementa un subprograma que calcule el camino y el coste mínimo para ir de la ciudad origen a la ciudad destino.
 *
 *       Tren y bus = NXN ==> Tren.numver * Bus.numvert
 *          TREN  |  Bus
 *            --------
 *          CTren | CBus
 *
 */

template <class T>
GrafoP<T> costesMinimosGastoTaxi(const GrafoP<T> gTren, const GrafoP<T> gBus, const T &costeTaxi, const T &origen, const T &destino)
{
    // Creamos el superGrafo
    int n = gTren.numVert() + gBus.numVert();
    GrafoP<T> superGrafo(n); // Asumo que el grafo tiene en sus casillas el valor infinito por defecto

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            // Rellenamos el superGrafo con el resto de valores dados por el enunciadoå

            superGrafo[i][j] = gTren[i][j];

            superGrafo[i + n][j + n] = gBus[i][j];

            // Actualizamos el coste de usar taxi en las diagonales principales
            superGrafo[i + n][i] = costeTaxi;
            superGrafo[i][i + n] = costeTaxi;
        }
    }

    // Hacemos Dijsktra desde origen hasta destino
    std::vector<T> costesMinimos = Dijkstra(superGrafo, origen, std::vector<T>());
    return costesMinimos[destino];
}

/**
 * Ejercicio 10
 * Se dispone de tres grafos que representan la matriz de costes para viajes en un determinado país, pero por diferentes medios de transporte
 * (tren, autobús y avión).
 * Por supuesto los tres grafos tendrán el mismo número de nodos, N.
 * Dados los siguientes datos:
 *  los tres grafos,
 *  una ciudad de origen,
 *  una ciudad de destino,
 *  el coste del taxi para cambiar, dentro de una ciudad, de la estación de tren a la
 * de autobús o viceversa (taxi-tren-bus) y
 *  el coste del taxi desde el aeropuerto a la estación de tren o la de autobús, o
 * viceversa (taxi-aeropuerto-tren/bus)
 * Asumiendo que ambos costes de taxi (distintos entre sí, son dos costes diferentes) son constantes e iguales para todas las ciudades,
 * implementa un subprograma que calcule el camino y el coste mínimo para ir de la ciudad origen a la ciudad destino.
 */

template <class T>
GrafoP<T> creaSuperGrafoTriple(const GrafoP<T> gTren, const GrafoP<T> gBus, const GrafoP<T> gAvion, const T &costeCambioTrenBus, const T &costeCambioAvionAlResto)
{

    const int n = gTren.numVert() + gBus.numVert() + gAvion.numVert();
    GrafoP<T> sg(n);

    // Inicializo los campos del grafo a infinito
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            sg[i][j] = GrafoP<T>::INFINITO;
        }
    }

    // Relleno los datos del enunciado
    for (int i = 0; i < gBus.numVert(); i++)
    {
        for (int j = 0; j < gBus.numVert(); j++)
        {
            sg[i][j] = gBus[i][j];          // Primer Cuadrante: Bus    0  + n + n      T       B       A
            sg[i + n][j + n] = gTren[i][j]; // Segundo Cuadrante Superior
            sg[i + 2 * n][j + 2 * n] = gAvion[i][j];

            // Rellenamos las diagonales con los costes
            sg[i + n][i] = costeCambioTrenBus;
            sg[i][i + n] = costeCambioTrenBus;
            sg[i + 2 * n][i] = costeCambioAvionAlResto;
            sg[i][i + 2 * n] = costeCambioAvionAlResto;
        }
    }
    return sg;
}

template <class T>
T costesMinimosAvionTrenBus(const GrafoP<T> gTren, const GrafoP<T> gBus, const GrafoP<T> gAvion, const T &costeCambioTrenBus, const T &costeCambioAvionAlResto, const T &origen, const T &destino)
{
    GrafoP<T> sg = creaSuperGrafoTriple(gTren, gBus, gAvion, costeCambioTrenBus, costeCambioAvionAlResto);
    return Dijkstra(sg, origen, std::vector<T>())[destino]; // No necesito ni almacenarlo
}

/** Ejercicio 11 P7 Grafos
 * 11. Disponemos de tres grafos (matriz de costes) que representan los costes directos de viajar entre las ciudades de tres de las islas del archipiélago
 * de las Huríes (Zuelandia). Para poder viajar de una isla a otra se dispone de una serie de puentes que conectan ciudades de las diferentes islas
 * a un precio francamente asequible (por decisión del Prefecto de las Huríes, el uso de los puentes es absolutamente gratuito).
Si el alumno desea simplificar el problema, puede numerar las N1 ciudades de la isla 1, del 0 al N1-1, las N2 ciudades de la isla 2, del N1 al N1+N2-1,
y las N3 de la última, del N1+ N2 al N1+N2+ N3-1.
Disponiendo de las tres matrices de costes directos de viajar dentro de cada una de las islas, y la lista de puentes entre ciudades de las mismas,
calculad los costes mínimos de viajar entre cualesquiera dos ciudades de estas tres islas.
¡¡¡ QUE DISFRUTÉIS EL VIAJE !!!
*/

template <class T>
matriz<T> costesMinimosPuentesGratisZuelandia(const GrafoP<T> mCostesIsla1, const GrafoP<T> mCostesIsla2, const GrafoP<T> mCostesIsla3)
{
    GrafoP<T> sgIslas(mCostesIsla1.numVert() + mCostesIsla2.numVert() + mCostesIsla3.numVert());
    // Inicializamos el superGrafo a INFINITO
    for (size_t i = 0; i < sgIslas.numVert(); i++)
    {
        for (size_t j = 0; j < sgIslas.numVert(); j++)
        {
            sgIslas[i][j] = GrafoP<T>::INFINITO;
        }
    }
    int n = mCostesIsla1.numVert();
    for (size_t i = 0; i < mCostesIsla1.numVert(); i++)
    {
        for (size_t j = 0; j < mCostesIsla1.numVert(); j++)
        {
            // Primera Isla
            sgIslas[i][j] = mCostesIsla1[i][j];

            // Segunda Isla
            sgIslas[i + n][j + n] = mCostesIsla2[i][j];

            // Tercera Isla
            sgIslas[i + 2 * n][j + 2 * n] = mCostesIsla3[i][j];

            // Rellenamos los costes de los puentes itermedios
            sgIslas[i][i + n] = 0;         // Puente entre isla 1 y 2
            sgIslas[i][i + 2 * n] = 0;     // Puente entre isla 1 y 3
            sgIslas[i + n][i + 2 * n] = 0; // Puente entre isla 2 y 3
        }
    }
    return Floyd(sgIslas, matriz<T>());
}

/**
 * Ejercicio 7 P8
 * El archipiélago de Grecoland (Zuelandia) está formado únicamente por dos islas, Fobos y Deimos, que tienen N1 y N2 ciudades, respectivamente, de las cuales C1 y C2
 * ciudades son costeras (obviamente C1 ≤ N1 y C2 ≤ N2 ). Se dispone de las coordenadas cartesianas (x, y) de todas y cada una de las ciudades del archipiélago.
 * El huracán Isadore acaba de devastar el archipiélago, con lo que todas las carreteras y puentes construidos en su día han desaparecido. En esta terrible situación
 * se pide ayuda a la ONU, que acepta reconstruir el archipiélago (es decir volver a comunicar todas las ciudades del archipiélago) siempre que se haga al mínimo coste.
 *
 * De cara a poder comparar costes de posibles reconstrucciones se asume lo siguiente:
    1. El coste de construir cualquier carretera o cualquier puente es proporcional a su longitud
    (distancia euclídea entre las poblaciones de inicio y fin de la carretera o del puente).
    2. Cualquier puente que se construya siempre será más caro que cualquier carretera que se construya.
    De cara a poder calcular los costes de VIAJAR entre cualquier ciudad del
    archipiélago se considerará lo siguiente:
        1. El coste directo de viajar, es decir de utilización de una carretera o de un puente, coincidirá con su longitud
        (distancia euclídea entre las poblaciones origen y destino de la carretera o del puente).

En estas condiciones, implementa un subprograma que calcule el coste mínimo de viajar entre dos ciudades de Grecoland, origen y destino,
después de haberse reconstruido el archipiélago, dados los siguientes datos:
    1. Lista de ciudades de Fobos representadas mediante sus coordenadas cartesianas.
    2. Lista de ciudades de Deimos representadas mediante sus coordenadas cartesianas.
    3. Lista de ciudades costeras de Fobos.
    4. Lista de ciudades costeras de Deimos.
    5. Ciudad origen del viaje.
    6. Ciudad destino del viaje.
 */

struct Ciudad
{
    int iNumeroCiudad;
    double x, y;
};

struct Puente
{
    Ciudad costeraFobos, costeraDeimos;
};

double distaciaEuclidea(Ciudad c1, Ciudad c2)
{
    return std::sqrt(std::pow((c2.x - c1.x), 2) + std::pow((c2.y - c1.y), 2)); // RAIZ de (x1-x2)^2 + (y1-y2)^2
}

// Crear un mapa de cada isla

GrafoP<double> creaMapaIsla(vector<Ciudad> ciudadesIsla)
{

    GrafoP<double> mapa(ciudadesIsla.size());

    for (int i = 0; i < ciudadesIsla.size(); ++i)
    {
        for (int j = 0; j < ciudadesIsla.size(); j++)
        {
            mapa[i][j] = distaciaEuclidea(ciudadesIsla[i], ciudadesIsla[j]);
        }
    }
}

template <class T>
double grecolandP8UnicoPuente(vector<Ciudad> Fobos, vector<Ciudad> Deimos, vector<Ciudad> costerasFobos,
                              vector<Ciudad> costerasDeimos, Ciudad origen,
                              Ciudad destino)
{

    // Calculo de las distancias entre Fobos y Deimos
    GrafoP<double> mapaFobos = creaMapaIsla(Fobos), mapaDeimos = creaMapaIsla(Deimos);

    // Para saber costes de carreteras usamos Kruskal, ya que conecta todos las ciudades con coste minimo
    GrafoP<double> carreterasFobos = Kruskall(mapaFobos);
    GrafoP<double> carreterasDeimos = Kruskall(mapaDeimos);

    // Conectar Ciudades Costeras entre Islas

    // Comprobamos que ciudades de Fobos y Deimos estan mas cercas entre si
    Puente mejorPuente;
    double dDistanciaMinimaPuente = GrafoP<double>::INFINITO;
    for (auto ciudadDeimos : costerasDeimos)
    {
        for (auto ciudadFobos : costerasFobos)
        {
            if (dDistanciaMinimaPuente < distaciaEuclidea(ciudadDeimos, ciudadFobos))
            {
                dDistanciaMinimaPuente = distaciaEuclidea(ciudadDeimos, ciudadFobos);
                mejorPuente.costeraDeimos = ciudadDeimos;
                mejorPuente.costeraFobos = ciudadFobos;
            }
        }
    }

    // Comprobamos donde estan las ciudades
    GrafoP<double> sgGrafo(mapaDeimos.numVert() + mapaFobos.numVert());
    for (int i = 0; i < sgGrafo.numVert(); i++)
    {
        for (int j = 0; j < sgGrafo.numVert(); j++)
        {
            sgGrafo[i][j] = GrafoP<double>::INFINITO;
        }
    }

    // Damos los valores al superGrafo
    for (int i = 0; i < mapaDeimos.numVert(); i++)
    {
        for (int j = 0; j < mapaFobos.numVert(); j++)
        {
            // Cuadrante Fobos
            sgGrafo[i][j] = mapaFobos[i][j];
            // Cuadrante Deimos
            sgGrafo[i + mapaDeimos.numVert()][j + mapaDeimos.numVert()] = mapaDeimos[i][j];
        }
    }

    // Colocamos puente en superGrafo
    sgGrafo[mejorPuente.costeraDeimos.iNumeroCiudad + mapaDeimos.numVert()][mejorPuente.costeraFobos.iNumeroCiudad] = dDistanciaMinimaPuente;
    sgGrafo[mejorPuente.costeraFobos.iNumeroCiudad][mejorPuente.costeraDeimos.iNumeroCiudad * mapaDeimos.numVert()] = dDistanciaMinimaPuente;

    // Hacer Dijsktra al SG
    return Dijsktra(sgGrafo, origen.iNumeroCiudad, std::vector<T>())[destino.iNumeroCiudad];
}

/**
 * Ejercicio 1 P8
 * El archipiélago de Tombuctú, está formado por un número indeterminado de islas, cada una de las cuales tiene, a su vez, un número
 * indeterminado de ciudades. En cambio, sí es conocido el número total de ciudades de Tombuctú (podemos llamarlo N, por ejemplo).
 * Dentro de cada una de las islas existen carreteras que permiten viajar entre todas las ciudades de la isla. Se dispone de las
 * coordenadas cartesianas (x, y) de todas y cada una de las ciudades del archipiélago. Se dispone de un grafo (matriz de adyacencia) en
 * el que se indica si existe carretera directa entre cualesquiera dos ciudades del archipiélago. El objetivo de nuestro problema es
 * encontrar qué ciudades de Tombuctú pertenecen a cada una de las islas del mismo y cuál es el coste mínimo de viajar entre cualesquiera
 * dos ciudades de una misma isla de Tombuctú.
 * Así pues, dados los siguientes datos:

    - Lista de ciudades de Tombuctú representada cada una de ellas por sus coordenadas cartesianas.
    - Matriz de adyacencia de Tombuctú, que indica las carreteras existentes en dicho archipiélago.

 * Implementen un subprograma que calcule y devuelva la distribución en islas de las ciudades de Tombuctú, así como el coste mínimo de
 * viajar entre cualesquiera dos ciudades de una misma isla del archipiélago.
*/

template <class T>
matriz<double> tombuctu(GrafoP<bool> adyTombuctu, std::vector<Ciudad> vCiudadesTombuctu)
{
    GrafoP<double> mCostesTombuctu(adyTombuctu.numVert());
    int n = adyTombuctu.numVert();
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            if (adyTombuctu[i][j])
            {
                mCostesTombuctu[i][j] = distaciaEuclidea(vCiudadesTombuctu[i], vCiudadesTombuctu[j]);
            }
            else
            {
                mCostesTombuctu[i][j] = std::GrafoP<double>::INFINITO;
            }
        }
    }

    return Floyd(mCostesTombuctu, matriz<T>(mCostesTombuctu.numVert()));
}

/**
 * Ejercicio 2 P8 VERSION DE DANI
 *
 * El archipiélago de Tombuctú2 está formado por un número desconocido de islas,
 * cada una de las cuales tiene, a su vez, un número desconocido de ciudades, las cuales
 * tienen en común que todas y cada una de ellas dispone de un aeropuerto. Sí que se
 * conoce el número total de ciudades del archipiélago (podemos llamarlo N, por ejemplo).
 * Dentro de cada una de las islas existen carreteras que permiten viajar entre todas
 * las ciudades de la isla. No existen puentes que unan las islas y se ha decidido que la
 * opción de comunicación más económica de implantar será el avión.
 * Se dispone de las coordenadas cartesianas (x, y) de todas y cada una de las
 * ciudades del archipiélago. Se dispone de un grafo (matriz de adyacencia) en el que se
 * indica si existe carretera directa entre cualesquiera dos ciudades del archipiélago.
 *
 * El objetivo de nuestro problema es encontrar qué líneas aéreas debemos implantar para
 * poder viajar entre todas las ciudades del archipiélago, siguiendo los siguientes criterios:
 *
 *  1) Se implantará una y sólo una línea aérea entre cada par de islas.
 *  2) La línea aérea escogida entre cada par de islas será la más corta entre toda
 *  las posibles.
 *
 * Así pues, dados los siguientes datos:
 *      • Lista de ciudades de Tombuctú2 representada cada una de ellas por sus coordenadas cartesianas.
 *      • Matriz de adyacencia de Tombuctú que indica las carreteras existentes en
 *        dicho archipiélago
 *
 * Implementen un subprograma que calcule y devuelva las líneas aéreas necesarias para
 * comunicar adecuadamente el archipiélago siguiendo los criterios anteriormente
 * expuestos.
 *
 * ¿Para que el particion?
 * 1 a 4
 *
 * Si aplicacmos el paticion ==> 1, 2           3,          4,5
 *
 */

struct tipo_coordenada
{
    double x, y;
    tipo_coordenada(double x_ = 0.0, double y_ = 0.0) : x(x_), y(y_) {}
};
struct Isla
{
    std::vector<Ciudad> vCiudades;
};

bool esBosque(Particion &p, size_t tam) // Si una particion es bosque es que tiene mas de un arbol
{
    bool es = false;
    for (size_t i = 0; i < tam - 1 && !es; ++i)
    {
        for (size_t j = i + 1; j < tam && !es; ++j)
        {
            if (p.encontrar(i) != p.encontrar(j))
                es = true;
        }
    }
    return es;
}

// Creamos las carreteras mediante la distancia euclidea
template <class T>
GrafoP<double> creaCarreteras(matriz<bool> adyTombuctu, std::list<Ciudad> vCiudadesTombuctu)
{
    GrafoP<double> gCarreteras(vCiudadesTombuctu.size());

    for (int i = 0; i < gCarreteras.numVert(); i++)
    {
        for (int j = 0; j < gCarreteras.numVert(); j++)
        {
            if (adyTombuctu[i][j])
                gCarreteras[i][j] = distaciaEuclidea(vCiudadesTombuctu[i], vCiudadesTombuctu[j]);
            else
                gCarreteras[i][j] = GrafoP<T>::INFINITO;
        }
    }
    return gCarreteras;
}

template <typename tCoste>
Grafo tombuctu2(Grafo &g, std::vector<tipo_coordenada> ciudades)
{
    Particion p(g.numVert()); // Para almacenar y crear el numero de islas
    typename Grafo::vertice origen, destino;
    tCoste costeMin = GrafoP<tCoste>::INFINITO;

    // Rellenamos la particion para agrupar las ciudades en islas (subconjuntos)
    for (size_t i = 0; i < g.numVert(); ++i)
    {
        for (size_t j = 0; j < g.numVert(); ++j)
        {
            if (g[i][j] || g[j][i]) // Si en la matriz de ady hay camino entre i y j, estan en la misma isla
            {
                if (p.encontrar(i) != p.encontrar(j)) // Si i,j no pertenecen al mismo subconjunto (no estan unidas aun)
                    p.unir(i, j);                     // las unimos en un subconjunto comun (la metemos en la misma isla)
            }
        }
    }

    //        I1      I2          I3
    // p={  {0,1}  {2,4,5}   {3,6,7,8,9}} = {{0,1,2,3,4,5,6,7,8,9}}

    //-----------------------------------------
    while (esBosque(p, g.numVert()) ºº) // Mientras haya islas desconectadas (Si una particion es un bosque es que tiene mas
                                        // de un subconjunto, por lo que aun existen nodos no conectados entre si)
    {
        // Este bucle recorre todas las posibles parejas de ciudades
        for (size_t i = 0; i < g.numVert(); ++i)
        {
            for (size_t j = 0; j < g.numVert(); ++j)
            {
                // si la pareja no está unida significa que estan en diferentes islas
                if (p.encontrar(i) != p.encontrar(j))
                {
                    // Comprueba si el coste de unir ambas ciudades es menor que el coste minimo anterior
                    if (distancia(ciudades[i], ciudades[j]) < costeMin)
                    {
                        // Si se cumple la condicion almacenamos coste y ciudades que une el camino
                        costeMin = distancia(ciudades[i], ciudades[j]); // Coste minimo el camino entre dos ciudades de distintas islas
                        origen = i;                                     // ciudad1
                        destino = j;                                    // ciudad2
                    }
                }
            }
        }
        // Al salir del bucle ya tenemos un camino que une 2 ciudades de diferentes islas,
        // marcamos en el grafo dicho camino como true
        g[origen][destino] = true;
        g[destino][origen] = true;
        p.unir(origen, destino); // unimos ambas ciudades en el mismo subconjunto de la particion y volvemos al while de arriba
        std::cout << "Linea aerea entre " << origen << " y " << destino << std::endl;
    } // Fin de mientras

    return g;
}

/**
 * Ejercicio 3
 * La empresa EMASAJER S.A. tiene que unir mediante canales todas las ciudades del
 * valle del Jerte (Cáceres). Calcula qué canales y de qué longitud deben construirse
 * partiendo del grafo con las distancias entre las ciudades y asumiendo las siguientes
 * premisas:
 *      − el coste de abrir cada nuevo canal es casi prohibitivo, luego la solución final
 *          debe tener un número mínimo de canales.
 *      − el Ministerio de Fomento nos subvenciona por Kms de canal, luego los canales
 *          deben ser de la longitud máxima posible.
 */

double distanciaEuclidea(const double x1, const double y1, const double x2, const double y2)
{
    return std::sqrt(std::pow(x1 - x2, 2) + std::pow(y1 - y2, 2));
}

template <class T>
GrafoP<T> unirCiudadesCaceres(Grafo gCiudadesAdyacencia, std::vector<Ciudad> vCiudades)
{
    GrafoP<T> gCiudadesUnidas(gCiudadesAdyacencia.numVert());
    for (int i = 0; i < gCiudadesAdyacencia.numVert(); i++)
    {
        for (int j = 0; j < gCiudadesAdyacencia.numVert(); j++)
        {
            gCiudadesUnidas[i][j] = (-1) * distaciaEuclidea(vCiudades[i].x, vCiudades[i].y, vCiudades[j].x, vCiudades[j].y);
        }
    }

    // MST DE COSTE MAXIMO
    gCiudadesUnidas = Kruskall(gCiudadesUnidas);

    for (int i = 0; i < gCiudadesAdyacencia.numVert(); i++)
    {
        for (int j = 0; j < gCiudadesAdyacencia.numVert(); j++)
        {
            gCiudadesUnidas[i][j] *= (-1)
        }
    }
    return gCiudadesUnidas;
}

/**
 * Ejercicio 5 P8
 *
 * La nueva compañía de telefonía RETEUNI3 tiene que conectar entre sí, con fibra
 * óptica, todas y cada una de las ciudades del país. Partiendo del grafo que representa las
 * distancias entre todas las ciudades del mismo, implementad un subprograma que
 * calcule la longitud mínima de fibra óptica necesaria para realizar dicha conexión
 * --> matriz<Costes>
 */

template <class T>
T reteUni3(const GrafoP<T> grCiudades)
{
    GrafoP<T> grMinimas = Kruskal(grCiudades);
    T totalDistancia = 0;
    for (int i = 0; i < grMinimas.numVert(); i++)
    {
        for (int j = 0; j < grMinimas.numVert(); j++)
        {
            if (grMinimas[i][j] != GrafoP<T>::INFINITO)
                totalDistancia = suma(grMinimas[i][j], totalDistancia);
        }
    }
    return totalDistancia;
}

/**
 * Ejercicio 6
 * /* 6.-
La empresa EMASAJER S.A. tiene que unir mediante canales todas las ciudades del
valle del Jerte (Cáceres), teniendo en cuenta las siguientes premisas:

− El coste de abrir cada nuevo canal es casi prohibitivo, luego la solución final debe
tener un número mínimo de canales.

− El Ministerio de Fomento nos subvenciona por m3/sg. de caudal, luego el
conjunto de los canales debe admitir el mayor caudal posible; pero por otra parte,
el coste de abrir cada canal es proporcional a su longitud, por lo que el conjunto de
los canales también debería medir lo menos posible. Así pues, la solución óptima
debería combinar adecuadamente ambos factores.


1.-Dada la matriz de distancias entre las diferentes ciudades del valle del Jerte,
2.-Matriz con los diferentes caudales máximos admisibles entre estas ciudades teniendo en
cuenta su orografía,
3.-La subvención que nos da Fomento por m3/sg. de caudal
4.-y el coste por km. de canal,
escribid un subprograma que calcule qué canales y de qué longitud y
caudal deben construirse para minimizar el coste (Floyd) total de la red de canales.

 */

template <class T>
GrafoP<T> uneCiudadesJerte2(const GrafoP<T> grDistanciasCiudades)
{
    return Kruskall(grDistanciasCiudades);
}

template <class T>
GrafoP<T> calculaCostesCanales(GrafoP<T> grDistancias, const vector<T> subvencionCaudal, double dCosteCanal)
{
    GrafoP<T> grCostes(grDistancias.numVert());
    for (int i = 0; i < grDistancias.numVert(); i++)
    {
        for (int j = 0; j < grDistancias.numVert(); j++)
        {
            if (grDistancias[i][j] != GrafoP<T>::INFINITO)
            {
                grCostes[i][j] = grDistancias[i][j] * dCosteCanal * (1 - subvencionCaudal[i]);
                grCostes[j][i] = grDistancias[j][i] * dCosteCanal * (1 - subvencionCaudal[j]);
            }
            else
                grCostes[i][j] = GrafoP<T>::INFINITO;
        }
    }
}

template <class T>
matriz<T> calcularCostesMinimosRedCanales(const GrafoP<T> grDistanciasCiudades, const GrafoP<T> subvencionCaudal, const double dCosteCanal)
{
    GrafoP<T> grDistancias = uneCiudadesJerte2(grDistanciasCiudades);
    GrafoP<T> costesCalculados = calculaCostesCanales(grDistancias, subvencionCaudal, dCosteCanal);
    return Floyd(costesCalculados, std::vector<T>());
}

/* 7.-
El archipiélago de Grecoland (Zuelandia) está formado únicamente por dos islas,
Fobos y Deimos, que tienen n1 y n2 ciudades, respectivamente, de las cuales c1 y c2 son
costeras. Se dispone de las coordenadas cartesianas (x, y) de todas y cada una de las
ciudades del archipiélago. El huracán Isadore acaba de devastar el archipiélago, con lo
que todas las carreteras y puentes construidos en su día han desaparecido. En esta
terrible situación se pide ayuda a la ONU, que acepta reconstruir el archipiélago (es
decir volver a comunicar todas las ciudades del archipiélago) siempre que se haga al
mínimo coste.
De cara a poder comparar costes de posibles reconstrucciones se asume lo
siguiente:
1. El coste de construir cualquier carretera o cualquier puente es proporcional a su
longitud (distancia euclídea entre las poblaciones de inicio y fin de la carretera o
del puente).
2. Cualquier puente que se construya siempre será más caro que cualquier carretera
que se construya.
De cara a poder calcular los costes de viajar entre cualquier ciudad del
archipiélago se considerará lo siguiente:
1. El coste directo de viajar, es decir de utilización de una carretera o de un puente,
coincidirá con su longitud (distancia euclídea entre las poblaciones origen y
destino de la carretera o del puente).
En estas condiciones, implementa un subprograma que calcule el coste mínimo
de viajar entre dos ciudades de Grecoland, origen y destino, después de haberse
reconstruido el archipiélago, dados los siguientes datos:
1. Lista de ciudades de Fobos representadas mediante sus coordenadas cartesianas.
2. Lista de ciudades de Deimos representadas mediante sus coordenadas
cartesianas.
3. Lista de ciudades costeras de Fobos.
4. Lista de ciudades costeras de Deimos.
5. Ciudad origen del viaje.
6. Ciudad destino del viaje.
*/

int main()
{

    return 0;
}
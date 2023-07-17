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
        for (int j : j < grafoZuelandia.numVert())
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
                                    const std::list<std::pair<int, int>> &lCarreterasTomadas, const int &iOrigen,
                                    const int &iDestino, const int &iCapital)
{
    GrafoP<int> grafoZuelandia = matrizCoste2GrafoP(matrizCostes);
    eliminarCarreterasTomadas(lCarreterasTomadas, grafoZuelandia);
    eliminarCiudadesTomadas(lCiudadesTomadas, grafoZuelandia);

    // Comprobamos que el origen/destino no esten en ciudades tomadas
    for (auto i : lCiudadesTomadas)
    {
        if (i == iOrigen || i == iDestino)
            return GrafoP<int>::INFINITO;
    }

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

int main()
{

    return 0;
}
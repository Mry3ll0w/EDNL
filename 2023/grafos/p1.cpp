#include <iostream>
#include <list>
#include "libGrafos/alg_grafoPMC.h"
using namespace std; // Avoid using std:: ....

/**
 * Ejercicio 5: Escribir una función genérica que implemente el algoritmo de Dijkstra
 * usando un grafo ponderado representado mediante listas de adyacencia.
 * */
template <typename tCoste>
vector<tCoste> DijkstraAdyacencia(const GrafoP<tCoste> &G,
                                  typename GrafoP<tCoste>::vertice origen,
                                  vector<typename GrafoP<tCoste>::vertice> &P)
// Calcula los caminos de coste mínimo entre origen y todos los
// vértices del grafo G. En el vector D de tamaño G.numVert()
// devuelve estos costes mínimos y P es un vector de tamaño
// G.numVert() tal que P[i] es el último vértice del camino
// de origen a i.
{
    typedef typename GrafoP<tCoste>::vertice vertice;
    vertice v, w;
    const size_t n = G.numVert();
    vector<bool> S(n, false); // Conjunto de vértices vacío.
    vector<tCoste> D;         // Costes mínimos desde origen.

    // Iniciar D y P con caminos directos desde el vértice origen.
    D = G[origen]; // Copiar toda la lista de Adyacencia
    D[origen] = 0; // Coste origen-origen es 0.
    P = vector<vertice>(n, origen);

    // Calcular caminos de coste mínimo hasta cada vértice.
    S[origen] = true; // Incluir vértice origen en S.
    for (size_t i = 1; i <= n - 2; i++)
    {
        // Seleccionar vértice w no incluido en S
        // con menor coste desde origen.
        tCoste costeMin = GrafoP<tCoste>::INFINITO;
        for (v = 0; v < n; v++)
            if (!S[v] && D[v] <= costeMin)
            {
                costeMin = D[v];
                w = v;
            }
        S[w] = true; // Incluir vértice w en S.
        // Recalcular coste hasta cada v no incluido en S a través de w.
        for (v = 0; v < n; v++)
            if (!S[v])
            {
                tCoste Owv = suma(D[w], G[w][v]); // Modificar G[w][v] para lista de adyacencia
                if (Owv < D[v])
                {
                    D[v] = Owv;
                    P[v] = w;
                }
            }
    }
    return D;
}

/**
 * Ejercicio 2:
 * 1)Definiremos el pseudocentro de un grafo conexo como el nodo del mismo que
 * minimiza la suma de las distancias mínimas a sus dos nodos más alejados
 * (por eso busco los maximos de cada fila).
 *
 * 2)Definiremos el diámetro del grafo como la suma de las distancias mínimas a los
 * dos nodos más alejados del pseudocentro del grafo.
 *
 * La que tiene la suma de las distancias minimas mas pequeñas
 *
 * Dado un grafo conexo representado mediante matriz de costes, implementa un
 * subprograma que devuelva la longitud de su diámetro.
 *
 * 1) Usamos floyd para obtener todas las distancias entre cada par de nodos
 * 2)
 */

/**
 * Ejercicio 3:
 * Tu empresa de transportes “PEROTRAVEZUNGRAFO S.A.” acaba de recibir la lista de
 * posibles subvenciones del Ministerio de Fomento en la que una de las más jugosas
 * se concede a las empresas cuyo grafo asociado a su matriz de costes sea acíclico.
 * ¿Puedes pedir esta subvención?
 * Implementa un subprograma que a partir de la matriz de costes nos indique si
 * tu empresa tiene derecho a dicha subvención
 *
 * Para determinar esto usaremos floyd junto con una matriz de adyacencias,
 * puesto que si tras aplicar floyd encontramos que existe un camino en la diagonal principal
 * entonces es aciclico
 *
 */
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
    bool bAciclica = true;
    for (int i = 0; i < Grafo.numVert() && bAciclica; i++)
    {
        if (MatrizAdyacencia[i][i])
            return false;
    }
    return true;
}

/**
 * Ejercicio 4: Zuelandia
 * Se necesita hacer un estudio de las distancias mínimas necesarias para viajar entre
 * dos ciudades cualesquiera de un país llamado Zuelandia.
 * El problema es sencillo pero hay que tener en cuenta unos pequeños detalles:
 * a) La orografía de Zuelandia es un poco especial, las carreteras son muy estrechas y
 * por tanto solo permiten un sentido de la circulación. ==> Se trata de un grafo ponderado dir
 * b) Actualmente Zuelandia es un país en guerra. Y de hecho hay una serie de ciudades del
 * país que han sido tomadas por los rebeldes, por lo que no pueden ser usadas para viajar.
 * c) Los rebeldes no sólo se han apoderado de ciertas ciudades del país, sino que también
 * han cortado ciertas carreteras, (por lo que estas carreteras no pueden ser usadas).
 *
 * d) Pero el gobierno no puede permanecer impasible ante la situación y ha exigido
 * que absolutamente todos los viajes que se hagan por el país pasen por la capital del mismo,
 * donde se harán los controles de seguridad pertinentes.
 * Dadas estas cuatro condiciones, se pide implementar un subprograma que dados
 * • el grafo (matriz de costes) de Zuelandia en situación normal,
 * • la relación de las ciudades tomadas por los rebeldes,
 * • la relación de las carreteras cortadas por los rebeldes
 * • y la capital de Zuelandia,
 * calcule la matriz de costes mínimos para viajar entre cualesquiera dos
 * ciudades zuelandesas en esta situación.
 */
GrafoP<int> procesaCarreteras(GrafoP<int> GrafoEnPaz, const std::list<std::pair<int, int>> &lCarreterasCortadas)
{
    GrafoP<int> GrafoCorregido = GrafoEnPaz;
    for (auto carretera : lCarreterasCortadas)
    {
        GrafoCorregido[carretera.first][carretera.second] = GrafoP<int>::INFINITO;
    }
    return GrafoCorregido;
}

void procesaCiudades(GrafoP<int> &Grafo, std::list<int> lCiudad)
{
    // Tenemos que eliminar la fila y la columna
    for (auto ciudad : lCiudad)
    {
        // Eliminamos las filas
        for (int i = 0; i < Grafo.numVert(); ++i)
        {
            Grafo[ciudad][i] = GrafoP<int>::INFINITO;
            Grafo[i][ciudad] = GrafoP<int>::INFINITO;
        }
    }
}

// Version Sin tener en cuenta que todo pasa por la capital
template <class T>
matriz<T> ZuelandiaSinCapital(GrafoP<int> GrafoPaz, std::list<std::pair<int, int>> lCarreteras, std::list<int> lCiudades)
{
    GrafoP<int> GrafoCorregido = GrafoPaz;
    GrafoCorregido = procesaCarreteras(GrafoPaz, lCarreteras);
    procesaCiudades(GrafoCorregido, lCiudades);
    // Hacemos floyd
    matriz<T> matrizCaminosFloyd;
    matrizCaminosFloyd = Floyd(GrafoCorregido, matrizCaminosFloyd);
    return matrizCaminosFloyd;
}

int main()
{

    return 0;
}

#include <iostream>
#include "lib/alg_grafoPMC.h"
using namespace std; // Avoid using std:: ....

/**
 * Ejercicio 5: Escribir una función genérica que implemente el algoritmo de Dijkstra
 * usando un grafo ponderado representado mediante listas de adyacencia.
 * */
template <typename tCoste>
vector<tCoste> Dijkstra(const GrafoP<tCoste> &G,
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
 */

int main()
{

    return 0;
}


/***********************************************
 *
 *
 *               LABERINTO 2D
 *
 *
 ************************************************/

#include "../libGrafos/grafoPMC.h"
#include "../libGrafos/alg_grafoPMC.h"
#include "../libGrafos/listaenla.h"

using namespace std;

typedef typename Grafo::vertice vertice;

struct Casilla
{
    int fila, columna;
};

struct Pared
{
    Casilla c1, c2;
};

// Cambio de casilla a nodo
/**
 * Esta función toma como entrada una estructura Casilla llamada c y el tamaño N de la cuadrícula (considerando que es una matriz cuadrada de NxN).
 * Luego, calcula el vértice correspondiente utilizando la siguiente fórmula:

    vertice = c.fila + c.columna * N

* Aquí, c.fila es el índice de fila de la casilla y c.columna es el índice de columna de la casilla. La multiplicación c.columna * N es necesaria para
* asegurarse de que el vértice se corresponda correctamente con la posición de la casilla en la cuadrícula.

CASO LABERINTO 3D

    int casilla_A_nodo(Casilla3D c, int N) {
        return c.x + c.y * N + c.z * N * N;
    }

    Casilla3D nodo_A_casilla(int v, int N) {
        Casilla3D c;
        c.z = v / (N * N);
        v = v % (N * N);
        c.y = v / N;
        c.x = v % N;
        return c;
    }
*/
vertice casilla_A_nodo(Casilla c, int N)
{
    return (c.fila + c.columna * N); // Si despejamos C.fila igualando a 0 sacamos la funcion de nodo a casilla
}

// Cambio de nodo a casilla
Casilla nodo_A_casilla(vertice v, int N)
{
    Casilla c;

    c.fila = (v / N) % N;
    c.columna = v % N;

    return c;
}

// Comprueba si 2 casillas son adyacentes
bool sonAdyacentes(Casilla c1, Casilla c2)
{
    return (abs(c1.fila - c2.fila) + abs(c1.columna - c2.columna)) == 1; // Si la distancia euclidea es 1 entonces estan adyacentes
}

template <typename T>
Lista<Casilla> recuperarCamino(vector<vertice> camino, vertice salida)
{
    Lista<Casilla> casillas;
    Lista<Casilla>::posicion p = casillas.primera();
    Casilla c = nodo_A_casilla(salida);
    vertice v;

    casillas.insertar(c, p);
    v = salida;

    while (v != 0)
    {
        v = camino[v];
        c = casilla_A_nodo(v);
        casillas.insertar(c, p);
    }

    return casillas;
}

template <typename T>
vector<Casilla> calcularCaminoLaberinto(int N, vector<Pared> paredes, Casilla entrada, Casilla salida, T &costeTotal)
{
    // Declaracion de variables
    GrafoP<T> G(N * N);

    Casilla c1, c2;
    vertice v, w;

    vector<T> costes;
    vector<vertice> camino;
    vector<Casilla> caminoCasillas;

    // Construccion del grafo
    for (vertice i = 0; i < G.numVert(); i++)
    {
        c1 = nodo_A_casilla(i, N);
        for (vertice j = 0; j < G.numVert(); j++)
        {
            c2 = nodo_A_casilla(j, N);

            if (i == j)
            {
                G[i][i] = 0;
            }
            if (sonAdyacentes(c1, c2))
            {
                G[i][j] = 1;
            }
            else
            {
                G[i][j] = GrafoP<T>::INFINITO;
            }
        }
    }

    // Introducimos las paredes
    for (int i = 0; i < paredes.size(); i++)
    {
        v = casilla_A_nodo(paredes[i].c1, N);
        w = casilla_A_nodo(paredes[i].c2, N);

        G[v][w] = GrafoP<T>::INFINITO;
        G[w][v] = GrafoP<T>::INFINITO;
    }

    // Dijkstra
    v = casilla_A_nodo(entrada, N);
    costes = Dijkstra(G, v, camino);

    // Calculamos el camino y el coste total
    costeTotal = 0;
    v = casilla_A_nodo(salida, N);
    w = casilla_A_nodo(entrada, N);

    caminoCasillas.push_back(salida);
    // P []
    while (v != w)
    {
        costeTotal += costes[v];
        c1 = nodo_A_casilla(camino[v], N);
        caminoCasillas.push_back(c1);
        v = camino[v];
    }

    caminoCasillas.push_back(entrada);
    reverse(caminoCasillas.begin(), caminoCasillas.end());

    return caminoCasillas;
}

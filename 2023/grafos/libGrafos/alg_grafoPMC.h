/*--------------------------------------------------------*/
/* alg_grafoPMC.h                                         */
/*                                                        */
/* Algoritmos para grafos ponderados representados        */
/* mediante matriz de costes (clase GrafoP<T>).           */
/*                                                        */
/* Estructuras de Datos no Lineales                       */
/* ©2016 José Fidel Argudo                                */
/*--------------------------------------------------------*/
/*
Funciones:

   template <typename tCoste> tCoste suma(tCoste x, tCoste y);
      Suma de costes. Devuelve GrafoP<tCoste>::INFINITO si alguno de los
      dos parámetros vale GrafoP<tCoste>::INFINITO.

   template <typename tCoste>
   vector<tCoste> Dijkstra(const GrafoP<tCoste>& G,
                           typename GrafoP<tCoste>::vertice origen,
                           vector<typename GrafoP<tCoste>::vertice>& P);
      Calcula los caminos de coste mínimo entre origen y todos los
      vértices del grafo G. Devuelve un vector de tamaño G.numVert()
      con estos costes mínimos y un vector P, también de tamaño
      G.numVert(), tal que P[i] es el último vértice del camino de
      coste mínimo de origen a i.

   template <typename tCoste> typename GrafoP<tCoste>::tCamino
   camino(typename GrafoP<tCoste>::vertice orig,
          typename GrafoP<tCoste>::vertice i,
          const vector<typename GrafoP<tCoste>::vertice>& P);
      Devuelve el camino de coste mínimo entre los vértices orig e i
      a partir de un vector P obtenido mediante la función Dijkstra().

   template <typename tCoste>
   matriz<tCoste> Floyd(const GrafoP<tCoste>& G,
                        matriz<typename GrafoP<tCoste>::vertice>& P);
      Calcula los caminos de coste mínimo entre cada par de vértices
      del grafo G. Devuelve una matriz de costes mínimos de tamaño
      n x n, con n = G.numVert(), y una matriz de vértices P de
      tamaño n x n, tal que P[i][j] es el vértice por el que pasa el
      camino de coste mínimo de i a j, si este vértice es i el camino
      es directo.

   template <typename tCoste> typename GrafoP<tCoste>::tCamino
   camino(typename GrafoP<tCoste>::vertice i,
          typename GrafoP<tCoste>::vertice j,
          const matriz<typename GrafoP<tCoste>::vertice>& P);
      Devuelve el camino de coste mínimo desde i hasta j a partir
      de una matriz P obtenida mediante la función Floyd().

   template <typename tCoste>
   GrafoP<tCoste> Prim(const GrafoP<tCoste>& G)
      Devuelve un árbol generador de coste mínimo
      de un grafo no dirigido ponderado y conexo G.

   template <typename tCoste>
   GrafoP<tCoste> Kruskall(const GrafoP<tCoste>& G)
      Devuelve un árbol generador de coste mínimo
      de un grafo no dirigido ponderado y conexo G.

*/
#ifndef ALG_GRAFO_P_H
#define ALG_GRAFO_P_H

#include <cassert>
#include "grafoPMC.h"  // grafo ponderado
#include <vector>      // para Dijkstra
#include "matriz.h"    // para Floyd
#include "apo.h"       // para Prim y Kruskall
#include "particion.h" // para Kruskall

/*----------------------------------------------------------------------------*/
/* Caminos de coste mínimo                                                    */
/*----------------------------------------------------------------------------*/
// Suma de costes (Dijkstra y Floyd)
template <typename tCoste>
tCoste suma(tCoste x, tCoste y)
{
   const tCoste INFINITO = GrafoP<tCoste>::INFINITO;
   if (x == INFINITO || y == INFINITO)
      return INFINITO;
   else
      return x + y;
}

// Calcula los costes de ir desde un nodo origen al resto de nodos del Grafo
// Almacena el resultado del mismo en D
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
   D = G[origen];
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
            tCoste Owv = suma(D[w], G[w][v]);
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
 *
 * @brief Desde cualquier origen a un destino concreto, no es hallar el camino.
 * El algoritmo se considera dado.
 * Recibe un nodo destino y calcula el camino del resto a este.
 */
template <typename tCoste>
vector<tCoste> DijsktraInverso(const GrafoP<tCoste> &G,
                               typename GrafoP<tCoste>::vertice destino,
                               vector<typename GrafoP<tCoste>::vertice> &P)
// Calcula los caminos de coste mínimo entre destino y todos los
// vértices del grafo G. En el vector D de tamaño G.numVert()
// devuelve estos costes mínimos y P es un vector de tamaño
// G.numVert() tal que P[i] es el último vértice del camino
// de destino a i.
{
   typedef typename GrafoP<tCoste>::vertice vertice;
   vertice v, w; // v es el vertice actual a optimizar y w es el nodo que estamos usando para optimizar
   const size_t n = G.numVert();
   vector<bool> S(n, false); // Conjunto de vértices vacío.
   vector<tCoste> D;         // Costes mínimos desde destino.

   // Iniciar D y P con caminos directos desde el vértice destino.
   D = G[destino];                  // Mete los nodos adyacentes del destino en D, guardamos los adyacentes al destino
   D[destino] = 0;                  // Coste destino-destino es 0.
   P = vector<vertice>(n, destino); // Se pone para que si existe un camino directo se mantenga

   // Calcular caminos de coste mínimo hasta cada vértice.
   S[destino] = true; // Incluir vértice destino en S.
   for (size_t i = 1; i <= n - 2; i++)
   {
      // Seleccionar vértice w no incluido en S
      // con menor coste desde destino.
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
         if (!S[v]) // S mantiene lps ya visitados
         {
            // tCoste Owv = suma(D[w], G[w][v]);//Coste de Origen a V pasando por w
            tCoste VwD = suma(G[v][w], D[v]); // Si la suma no supera lo metemos
            if (VwD < D[v])
            {
               D[v] = VwD;
               P[v] = w;
            }
         }
   }
   return D;
}

template <typename tCoste>
vector<tCoste> DijkstraInv_(const GrafoP<tCoste> &G, typename GrafoP<tCoste>::vertice destino, vector<typename GrafoP<tCoste>::vertice> &P)
{
   using std::vector;
   typedef typename GrafoP<tCoste>::vertice vertice;
   const size_t N = G.numVert();
   vertice v, w;
   // Conjunto de vértices vacío
   vector<bool> S(N, false);
   // Costes mínimos desde el origen
   vector<tCoste> D(N);
   for (vertice i = 0; i < N; i++)
      D.push_back(G[i][destino]);
   // Vector de vértices. La posición i-ésima indica a cuál vértice hay que
   // ir desde i para llegar a la distancia mas corta
   P = vector<vertice>(N, destino);
   D[destino] = 0;
   S[destino] = true;
   for (size_t i = 1; i < N - 1; i++)
   {
      // w = vértice con el coste de menor tamaño que no se haya
      // computado aún
      tCoste costeMin = GrafoP<tCoste>::INFINITO;
      for (v = 0; v < N; v++)
         if (!S[v] && D[v] <= costeMin)
         {
            costeMin = D[v];
            w = v;
         }
      // Ahora hemos seleccionado este vértice para reducir su distancia
      S[w] = true;
      // Recalculamos la distancia *hacia* w desde cada vértice aún no usado *v*
      // Si usar la ruta desde v hasta w. y desde w al destino es mejor que la ruta
      // original de v a destino (aka "incluir w en el camino v -> destino"),
      // entonces tenemos que actualizarla
      for (v = 0; v < N; v++)
         if (!S[v])
         {
            tCoste Ovw = suma(D[w], G[v][w]);
            if (Ovw < D[v])
            {
               D[v] = Ovw;
               P[v] = w;
            }
         }
   }
   return D;
}

template <typename tCoste>
typename GrafoP<tCoste>::tCamino
camino(typename GrafoP<tCoste>::vertice orig,
       typename GrafoP<tCoste>::vertice v,
       const vector<typename GrafoP<tCoste>::vertice> &P)
// Devuelve el camino de coste mínimo entre los vértices orig e v
// a partir de un vector P obtenido mediante la función Dijkstra().
{
   typename GrafoP<tCoste>::tCamino C;

   C.insertar(v, C.primera());
   do
   {
      C.insertar(P[v], C.primera());
      v = P[v];
   } while (v != orig);
   return C;
}

/**
 * @brief Aplica Floyd, devolviendo por return la matriz de costes minimos y por parametros
 * P, la matriz que representa el camino directo entre i y j
 */
template <typename tCoste>
matriz<tCoste> Floyd(const GrafoP<tCoste> &G,
                     matriz<typename GrafoP<tCoste>::vertice> &P)
// Calcula los caminos de coste mínimo entre cada
// par de vértices del grafo G. Devuelve una matriz
// de costes mínimos A de tamaño n x n, con n = G.numVert()
// y una matriz de vértices P de tamaño n x n, tal que
// P[i][j] es el vértice por el que pasa el camino de coste
// mínimo de i a j, si este vértice es i el camino es directo.
{
   typedef typename GrafoP<tCoste>::vertice vertice;
   const size_t n = G.numVert();
   matriz<tCoste> A(n); // matriz de costes mínimos

   // Iniciar A y P con caminos directos entre cada par de vértices.
   P = matriz<vertice>(n);
   for (vertice i = 0; i < n; i++)
   {
      A[i] = G[i];                  // copia costes del grafo
      A[i][i] = 0;                  // diagonal a 0
      P[i] = vector<vertice>(n, i); // caminos directos
   }
   // Calcular costes mínimos y caminos correspondientes
   // entre cualquier par de vértices i, j
   for (vertice k = 0; k < n; k++)
      for (vertice i = 0; i < n; i++)
         for (vertice j = 0; j < n; j++)
         {
            tCoste ikj = suma(A[i][k], A[k][j]);
            if (ikj < A[i][j])
            {
               A[i][j] = ikj;
               P[i][j] = k;
            }
         }
   return A;
}

template <typename tCoste>
typename GrafoP<tCoste>::tCamino
caminoAux(typename GrafoP<tCoste>::vertice v,
          typename GrafoP<tCoste>::vertice w,
          const matriz<typename GrafoP<tCoste>::vertice> &P)
// Devuelve el camino de coste mínimo entre v y w, exluidos estos,
// a partir de una matriz P obtenida mediante la función Floyd().
{
   typename GrafoP<tCoste>::tCamino C1, C2;
   typename GrafoP<tCoste>::vertice u = P[v][w];

   if (u != v)
   {
      C1 = caminoAux<tCoste>(v, u, P);
      C1.insertar(u, C1.fin());
      C2 = caminoAux<tCoste>(u, w, P);
      C1 += C2; // Lista<vertice>::operator +=(), concatena C1 y C2
   }
   return C1;
}

template <typename tCoste>
typename GrafoP<tCoste>::tCamino
camino(typename GrafoP<tCoste>::vertice v,
       typename GrafoP<tCoste>::vertice w,
       const matriz<typename GrafoP<tCoste>::vertice> &P)
// Devuelve el camino de coste mínimo desde v hasta w a partir
// de una matriz P obtenida mediante la función Floyd().
{
   typename GrafoP<tCoste>::tCamino C = caminoAux<tCoste>(v, w, P);
   C.insertar(v, C.primera());
   C.insertar(w, C.fin());
   return C;
}

/*----------------------------------------------------------------------------*/
/* Árboles generadores de coste mínimo                                        */
/*----------------------------------------------------------------------------*/
template <typename tCoste>
GrafoP<tCoste> Prim(const GrafoP<tCoste> &G)
// Devuelve un árbol generador de coste mínimo
// de un grafo no dirigido ponderado y conexo G.
{
   assert(!G.esDirigido());

   typedef typename GrafoP<tCoste>::vertice vertice;
   typedef typename GrafoP<tCoste>::arista arista;
   const tCoste INFINITO = GrafoP<tCoste>::INFINITO;
   arista a;
   const size_t n = G.numVert();
   GrafoP<tCoste> g(n);                    // Árbol generador de coste mínimo.
   vector<bool> U(n, false);               // Conjunto de vértices incluidos en g.
   Apo<arista> A(n * (n - 1) / 2 - n + 2); // Aristas adyacentes al árbol g
                                           // ordenadas por costes.
   U[0] = true;                            // Incluir el primer vértice en U.
   // Introducir en el APO las aristas adyacentes al primer vértice
   for (vertice v = 1; v < n; v++)
      if (G[0][v] != INFINITO)
         A.insertar(arista(0, v, G[0][v]));
   for (size_t i = 1; i <= n - 1; i++)
   { // Seleccionar n-1 aristas.
      // Buscar una arista a de coste mínimo que no forme un ciclo.
      // Nota: Las aristas en A tienen sus orígenes en el árbol g.
      do
      {
         a = A.cima();
         A.suprimir();
      } while (U[a.dest]); // a forma un ciclo (a.orig y a.dest están en U y en g).
      // Incluir la arista a en el árbol g y el nuevo vértice u en U.
      g[a.orig][a.dest] = g[a.dest][a.orig] = a.coste;
      vertice u = a.dest;
      U[u] = true;
      // Introducir en el APO las aristas adyacentes al vértice u
      // que no formen ciclos.
      for (vertice v = 0; v < n; v++)
         if (!U[v] && G[u][v] != INFINITO)
            A.insertar(arista(u, v, G[u][v]));
   }
   return g;
}

template <typename tCoste>
GrafoP<tCoste> Kruskall(const GrafoP<tCoste> &G)
// Devuelve un árbol generador de coste mínimo
// de un grafo no dirigido ponderado y conexo G.
{
   assert(!G.esDirigido());

   typedef typename GrafoP<tCoste>::vertice vertice;
   typedef typename GrafoP<tCoste>::arista arista;
   const tCoste INFINITO = GrafoP<tCoste>::INFINITO;
   const size_t n = G.numVert();
   GrafoP<tCoste> g(n);  // Árbol generador de coste mínimo.
   Particion P(n);       // Partición inicial del conjunto de vértices de G.
   Apo<arista> A(n * n); // Aristas de G ordenadas por costes.

   // Copiar aristas del grafo G en el APO A.
   for (vertice u = 0; u < n; u++)
      for (vertice v = u + 1; v < n; v++)
         if (G[u][v] != INFINITO)
            A.insertar(arista(u, v, G[u][v]));

   size_t i = 1;
   while (i <= n - 1)
   {                       // Seleccionar n-1 aristas.
      arista a = A.cima(); // arista de menor coste
      A.suprimir();
      vertice u = P.encontrar(a.orig);
      vertice v = P.encontrar(a.dest);
      if (u != v)
      { // Los extremos de a pertenecen a componentes distintas
         P.unir(u, v);
         // Incluir la arista a en el árbol g
         g[a.orig][a.dest] = g[a.dest][a.orig] = a.coste;
         i++;
      }
   }
   return g;
}

#endif // ALG_GRAFO_P_H

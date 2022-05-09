#include <iostream>
#include <vector>
#include <list>
#include "lib/alg_grafoPMC.h"
#include "lib/grafoPMC.h"

template<class tCoste>
vector<tCoste> DijkstraInv(const GrafoP<tCoste>& G,
                        typename GrafoP<tCoste>::vertice destino,
                        vector<typename GrafoP<tCoste>::vertice>& P);

template <class tCoste>
std::vector<int> custom_reverse_Dijkstra(std::vector<tCoste> P,const int& Origen, const int Destino);

GrafoP<unsigned int>::vertice pseudocentro(GrafoP<unsigned int>& G);

int main(){

   
   typedef unsigned int tCoste;

   std::cout << "Valor coste infinito: " << GrafoP<tCoste>::INFINITO << std::endl << std::endl;

   GrafoP<tCoste> G("lib/data/ejpmc.txt");
   std::cout << " ** Se rellena G ** " << std::endl;
   std::cout << G << std::endl;

   std::cout << std::endl << "/////////////////////////////// EJERCICIO 1 ///////////////////////////////" << std::endl << std::endl;

   GrafoP<tCoste>::vertice origen = 0;
   std::vector<GrafoP<tCoste>::vertice> P(G.numVert(), 0);
   

   std::vector<tCoste> costes = Dijkstra(G, origen, P);

   std::cout << "El resultado de Dijkstra es:" << std::endl;
   std::cout << "Coste\t|\tVértice" << std::endl;
   
   for( int i = 0; i < G.numVert(); ++i )
      if( costes[i] != GrafoP<tCoste>::INFINITO )
         std::cout << costes[i] << "\t\t|\t" << P[i] << std::endl;
      else
         std::cout << "INF\t\t|\t" << P[i] << std::endl;
   
   std::cout<<std::endl<<"-----------------------------------------------------------"<<std::endl;
   
   std::cout<<"Resultado de lo que devuelve djikstra inverso: "<<std::endl;
   for(auto i : custom_reverse_Dijkstra(P,0,3)){
      std::cout<< i << ", ";
   }
   std::cout<<std::endl<<"-----------------------------------------------------------"<<std::endl;

   std::cout<<std::endl<<"-----------------------------------------------------------"<<std::endl;
   std::cout << "DIJSTRA A TODO EL GRAFO"<<std::endl;
   pseudocentro(G);

return 0;   
}


/*
1) ni idea
Añadir una función genérica, llamada DijkstraInv, en el fichero 
alg_grafoPMC.h para resolver el problema inverso al de Dijkstra, con los mismos 
tipos de parámetros y de resultado que la función ya incluida para éste. La nueva 
función, por tanto, debe hallar el camino de coste mínimo hasta un destino desde cada 
vértice del grafo y su correspondiente coste.
*/
template<class tCoste>
vector<tCoste> DijkstraInv(const GrafoP<tCoste>& G,
                        typename GrafoP<tCoste>::vertice destino,
                        vector<typename GrafoP<tCoste>::vertice>& P)
// Calcula los caminos de coste mínimo entre todos los vértices
// del grafo G y destino. En el vector D de tamaño G.numVert()
// devuelve estos costes mínimos y P es un vector de tamaño
// G.numVert() tal que P[i] es el último vértice del camino
// de i a destino.
{
   typedef typename GrafoP<tCoste>::vertice vertice;
   vertice v, w;
   const size_t n = G.numVert();
   vector<bool> S(n, false);                  // Conjunto de vértices vacío.
   vector<tCoste> D(n);                          // Costes mínimos hacia destino.

   // Iniciar D y P con caminos directos hacia el vértice destino.
   for( size_t i = 0; i < n; ++i )
      D[i] = G[i][destino];
   D[destino] = 0;                             // Coste destino-destino es 0.
   P = vector<vertice>(n, destino);

   // Calcular caminos de coste mínimo desde cada vértice.
   S[destino] = true;                          // Incluir vértice destino en S.
   for (size_t i = 1; i <= n-2; i++) {
      // Seleccionar vértice w no incluido en S
      // con menor coste hacia destino.
      tCoste costeMin = GrafoP<tCoste>::INFINITO;
      for (v = 0; v < n; v++)
         if (!S[v] && D[v] <= costeMin) {
            costeMin = D[v];
            w = v;
         }
      S[w] = true;                          // Incluir vértice w en S.
      // Recalcular coste hasta cada v no incluido en S a través de w.
      for (v = 0; v < n; v++)
         if (!S[v]) {
            tCoste vwD = suma(D[w], G[v][w]);
            if (vwD < D[v]) {
               D[v] = vwD;
               P[v] = w;
            }
         }
   }
   return D;
}

template <class tCoste>
std::vector<int> custom_reverse_Dijkstra(std::vector<tCoste> p,const int& Origen, const int Destino){

   std::vector<int> camino;
   int i = p[Destino];
   std::cout<<"Valor de i inicial: "<< i << std::endl;
   while (i != Origen)
   {
      std::cout<<"valor de p["<<i<<"]"<<p[i]<<std::endl;
      camino.insert(camino.begin(),i);
      i=p[i];
   }
   
   //Insertamos el origen y el destino 
   camino.push_back(Destino);
   camino.insert(camino.begin(),Origen);

return camino;

}

//Ejercicio 2
/*
Definiremos el pseudocentro de un grafo conexo como el nodo del mismo que 
minimiza la suma de las distancias mínimas a sus dos nodos más alejados. Definiremos 
el diámetro del grafo como la suma de las distancias mínimas a los dos nodos más 
alejados del pseudocentro del grafo. 
 Dado un grafo conexo representado mediante matriz de costes, implementa un 
subprograma que devuelva la longitud de su diámetro.
*/

GrafoP<unsigned int>::vertice pseudocentro(GrafoP<unsigned int>& G){

   //obtenemos la lista de vertices
   int vertices = G.numVert();

   for(size_t i = 0; i < vertices;++i){

         //Imprimo Dijkstra 
         std::vector<GrafoP<unsigned int>::vertice> P(G.numVert(), 0);
   

         std::vector<unsigned int> costes = Dijkstra(G, i, P);

         std::cout << "El resultado de Dijkstra es:" << std::endl;
         std::cout << "Coste\t|\tVértice" << std::endl;
   
         for( int i = 0; i < G.numVert(); ++i )
            if( costes[i] != GrafoP<unsigned int>::INFINITO )
               std::cout << costes[i] << "\t\t|\t" << P[i] << std::endl;
            else
               std::cout << "INF\t\t|\t" << P[i] << std::endl;
   
         std::cout<<std::endl<<"-----------------------------------------------------------"<<std::endl;
         

   }

}
#include <iostream>
#include <vector>
#include <list>
#include "lib/alg_grafoPMC.h"
#include "lib/grafoPMC.h"

int main(){

    GrafoP<unsigned int>g("ejpmc.txt");
    GrafoP<unsigned int>v("ejpmc.txt");
    std::cout<<g<<std::endl;
    

return 0;   
}

/*
1)
Añadir una función genérica, llamada DijkstraInv, en el fichero 
alg_grafoPMC.h para resolver el problema inverso al de Dijkstra, con los mismos 
tipos de parámetros y de resultado que la función ya incluida para éste. La nueva 
función, por tanto, debe hallar el camino de coste mínimo hasta un destino desde cada 
vértice del grafo y su correspondiente coste.
*/
template <typename tCoste>
vector<tCoste> Dijkstra_inverso(const GrafoP<tCoste>& G,
                        typename GrafoP<tCoste>::vertice origen,
                        vector<typename GrafoP<tCoste>::vertice>& P)
// Calcula los caminos de coste mínimo entre origen y todos los
// vértices del grafo G. En el vector D de tamaño G.numVert()
// devuelve estos costes mínimos y P es un vector de tamaño
// G.numVert() tal que P[i] es el último vértice del camino
// de origen a i.
{
   typedef typename GrafoP<tCoste>::vertice vertice;
   vertice v, w;
   const size_t n = G.numVert();
   vector<bool> S(n, false);                  // Conjunto de vértices vacío.
   vector<tCoste> D(n);                          // Costes mínimos desde origen.

   // Iniciar D y P con caminos directos desde el vértice origen.
   for(int i = 0; i < n; ++i){
        D = G[i][origen];//obtenemos todas las columnas (ya que en las columnas se encuentran los costes de ir desde el destino al origen)    
   }
   

   D[origen] = 0;                             // Coste origen-origen es 0.
   P = vector<vertice>(n, origen);

   // Calcular caminos de coste mínimo hasta cada vértice.
   S[origen] = true;                          // Incluir vértice origen en S.
   for (size_t i = 1; i <= n-2; i++) {
      // Seleccionar vértice w no incluido en S
      // con menor coste desde origen.
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
            tCoste Owv = suma(D[w], G[w][v]);
            if (Owv < D[v]) {
               D[v] = Owv;
               P[v] = w;
            }
         }
   }
   return D;
}

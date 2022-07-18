#include <iostream>
//#include "lib/grafoPMC.h"
#include "lib/matriz.h"
#include "lib/alg_grafoPMC.h"

using namespace std;

/*
1)
Tu agencia de viajes “OTRAVEZUNGRAFO S.A.” se enfrenta a un curioso cliente. 
Es un personaje sorprendente, no le importa el dinero y quiere hacer el viaje 
más caro posible entre las ciudades que ofertas. 
Su objetivo es gastarse la mayor cantidad de dinero posible, no le importa el 
origen ni el destino del viaje.
Sabiendo que es imposible pasar dos veces por la misma ciudad, ya que casualmente 
el grafo de tu agencia de viajes resultó ser acíclico, devolver el coste, origen 
y destino de tan curioso viaje. 
Se parte de la matriz de costes directos entre las ciudades del grafo.

Para realizar este algoritmos deberemos:
En primer lugar modificar el algoritmo de Floyd, para obtener 
en vez de la matriz de costes mínimos, la matriz de costes "maximos".

*/

// usar std::max. En el caso donde (a == INF) ^ (b == INF), no debemos escoger
// INF, sino el valor que no sea INF (puesto que INF representa ausencia de
// arista, pero de a y b sabemos que uno de ellos sí existe arista... por lo que
// deberíamos de tomarlo)
template <typename tCoste> tCoste max_inf(tCoste a, tCoste b)
{
  static const tCoste INF = GrafoP<tCoste>::INFINITO;
  if (a == INF && b == INF)
    return INF;
  else if (a == INF)
    return b;
  else if (b == INF)
    return a;
  else
    return std::max(a, b);
}

//Algoritmo de Floyd para hallar los caminos de costes máximos
template<class tCoste>
matriz<tCoste> Floyd_Max(const GrafoP<tCoste>& G){
    size_t n = G.numVert();
    //typedef para evitar escribir mucho texto
    typedef typename GrafoP<tCoste>::vertice vertice;
    matriz<tCoste> A(n);

    //Inicializamos las filas iniciales
    for(vertice i = 0; i < n ; i++){
        A[i]=G[i];
        A[i][i]=0;
    }
        
    for(vertice i = 0 ; i < n; i++)
        for(vertice j=0 ; j < n; j++)
            for(vertice k=0 ; k < n ; k++){
                A[i][j] = max_inf(A[i][j],suma(A[i][k],A[k][j]));
            }
    return A;
}

//Funcion solucion al ejercicio 1
template <class tCoste> 
void solucion_ej1(GrafoP<tCoste> &G){
    typedef typename GrafoP<tCoste>::vertice vertice;
    matriz<tCoste> r = Floyd_Max(G);
    vertice o,des;
    tCoste Coste_viaje=0;
    //Recorremos la matriz de mayor coste
    for(vertice i = 0; i < G.numVert() ; i++){
        for(vertice j = 0; j < G.numVert(); j++){
            cout<<r[i][j]<<" ";
            if (r[i][j] > Coste_viaje && r[i][j] != GrafoP<tCoste>::INFINITO)
            {
                Coste_viaje = r[i][j];
                o = i;
                des= j;
            }
            
        }
        cout << endl;
    }
        
    cout << "El coste del viaje será : "<<Coste_viaje<<" y saldrá desde "<<o<<" hasta "<<des<<endl;
}


int main(){
    typedef unsigned int tCoste;
    //Creamos un grafo
    GrafoP<tCoste> G("lib/data/ejpmc.txt");
    std::cout << " ** Se rellena G ** " << std::endl;
    std::cout << G << std::endl;

    //solucion_ej1(G);

    
    return 0;
}

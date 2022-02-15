#include<vector>
#include "GrafoP.hpp"

/*
// Suma de costes
template <typename tCoste>
tCoste suma(tCoste x, tCoste y)
{
    const tCoste INFINITO = GrafoP<tCoste>::INFINITO;
    if (x == INFINITO || y == INFINITO)
        return INFINITO;
    else
        return x + y;
}*/

template<typename tCoste>
std::vector<tCoste> DijkstraL(GrafoPL<tCoste>& g, typename GrafoPL<tCoste>::vertice origen, std::vector<typename GrafoPL<tCoste>::vertice>& P) //Dijkstra aplicado a un grafo con listas de hijos
{
    //---Declaracion e inicializacion de variables necesarias---
    typename GrafoPL<tCoste>::vertice v, w;
    const size_t n=g.numVert();
    std::vector<bool> S(n, false); //Vector para controlar vertices procesados
    std::vector<tCoste> D(n,GrafoPL<tCoste>::INFINITO); //Costes minimos desde origen inicializados a INF -> return
    
    //Inicializar D con los costes desde origen a todos los nodos con conexion directa
    for(typename Lista<typename GrafoPL<tCoste>::vertice_coste>::posicion pos=g.adyacentes(origen).primera();pos!=g.adyacentes(origen).fin();pos=g.adyacentes(origen).siguiente(pos)) //Recorre la lista de nodos conectados con origen
    {
        D[g.adyacentes(origen).elemento(pos).v]=g.adyacentes(origen).elemento(pos).c;
    }
    D[origen]=0; //El coste de origen a origen es 0 porque es minimo

    P=std::vector<typename GrafoPL<tCoste>::vertice>(n, origen); //Se inicia el vector de caminos
        //con todos los valores a origen
        
    //Calcular los caminos de coste minimo hasta cada vertice
    S[origen]=true; //Vertice origen procesado

    for(size_t i=0;i<=n-2;++i) //1
    {
        //Localizar vertice w no incluido en S con menor coste desde origen (Hay que recorrer la lista de origen)
        tCoste costeMin=GrafoPL<tCoste>::INFINITO;
        for (v = 0; v <= n-1; v++) //Este bucle
            if (!S[v] && D[v] <= costeMin)
            {
                costeMin = D[v];
                w = v;
            }
        S[w]=true; //vertice w procesado
        //Recalcular coste hasta cada v no incluido en S a traves de w
        for (v = 0; v <= n-1; v++)
            if (!S[v])
            {
                typename GrafoPL<tCoste>::vertice_coste vc;
                vc.v=v;
                typename Lista<typename GrafoPL<tCoste>::vertice_coste>::posicion p=g.adyacentes(w).buscar(vc);
                if(p!=g.adyacentes(w).fin())
                {
                    tCoste Owv = suma(D[w], g.adyacentes(w).elemento(p).c);
                    if (Owv < D[v])
                    {
                        D[v] = Owv;
                        P[v] = w; //Se rellena el vector P
                    }
                }
            }
    } //fin 1

    return D;
}
#include <iostream>
#include "../grafos/libGrafos/grafoPMC.h"
#include "../grafos/libGrafos/grafoMA.h"
#include "../grafos/libGrafos/alg_grafoPMC.h"
using namespace std; // Avoid using std:: ....
/**
 * Un repartidor de una empresa de distribución de bebidas tiene que visitar a todos sus
clientes cada día. Pero, al comenzar su jornada de trabajo, no conoce qué cantidad de bebidas
tiene que servir a cada cliente, por lo que no puede planificar una ruta óptima para visitarlos a
todos. Por tanto, nuestro repartidor decide llevar a cabo la siguiente estrategia:
 El camión parte del almacén con la máxima carga permitida rumbo a su cliente más
próximo.
 El repartidor descarga las cajas de bebidas que le pide el cliente. Si no tiene suficientes
cajas en el camión, le entrega todas las que tiene. Este cliente terminará de ser servido en
algún otro momento a lo largo del día, cuando la estrategia de reparto vuelva a llevar al
repartidor hasta él.
 Después de servir a un cliente:
o Si quedan bebidas en el camión, el repartidor consulta su sistema de navegación
basado en GPS para conocer la ruta que le lleva hasta su cliente más próximo
pendiente de ser servido.
o Si no quedan bebidas en el camión, vuelve al almacén por el camino más corto y
otra vez carga el camión completamente.
 Después de cargar el camión, el repartidor consulta su sistema de navegación y se va por
el camino más corto a visitar al cliente pendiente de ser servido más próximo.

Implementa un subprograma que calcule y devuelva la distancia total recorrida en un
día por nuestro repartidor, a partir de lo siguiente:

1. Grafo representado mediante matriz de costes con las distancias de los caminos directos
entre los clientes y entre ellos y la central.

2. Capacidad máxima del camión (cantidad de cajas de bebidas).

3. Asumiremos que existe una función int Pedido() que devuelve el número de cajas que
quedan por servir al cliente en el que se encuentra el repartidor.==> Es un vector para que tire


 */

int &Pedido(int iCliente)
{
}
int iCentral = 0;

template <class T>
int distanciaRepartidor(GrafoP<double> grDistancias, int iCapacidadCamion) // Se asume que se recibe el nodo donde esta la central
{
    int iNodoActual = iCentral;
    int iCargaActual = iCapacidadCamion;
    int iDistanciaTotal = 0;
    // PRocesamos la matriz de costes para obtener el camino minimo de moverse entre cada par de vertices
    matriz<int> matrizMinimas = Floyd(grDistancias, matriz<int>());

    int iPedidosCompletados = 0; // Cuando valga n se han servido a todos los clientes
    while (iPedidosCompletados < grDistancias.numVert())
    {
        // Pillamos el nodo mas cercano
        if (iCargaActual == 0)
        {
            iDistanciaTotal += matrizMinimas[iNodoActual][iCentral];
            iNodoActual = iCentral;
            iCargaActual = iCapacidadCamion;
        }
        else
        {
            int iDistanciaMinima = GrafoP<int>::INFINITO;
            int iMejorNodo = iNodoActual;
            for (int i = 0; i < grDistancias.numvert(); ++i)
            {
                if (iDistanciaMinima > grDistancias[iNodoActual][i])
                {
                    iMejorNodo = i;
                    iDistanciaMinima = grDistancias[iNodoActual][i];
                }
            }
            // Hemos hallado el mejor nodo

            if (iCargaActual < Pedido(iMejorNodo))
            {
                Pedido(iMejorNodo) -= iCargaActual;
                iCargaActual = 0;
                iDistanciaTotal += matrizMinimas[iNodoActual][iMejorNodo];
                iNodoActual = iMejorNodo;
            }
            else
            {
                iCargaActual -= Pedido(iMejorNodo);
                Pedido(iMejorNodo) = 0;
                iPedidosCompletados++;
                iDistanciaTotal += matrizMinimas[iNodoActual][iMejorNodo];
                iNodoActual = iMejorNodo;
            }
        }
    }
    return iDistanciaTotal;
}
int main()
{

    return 0;
}
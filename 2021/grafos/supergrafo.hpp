/*
tren
(0) --------- (1) -------- (2)
      5             50

Matriz de costes tren
_  5  _
5  _  50
_  50  _

avion
(0) --------- (1) -------- (2)
       40            10

Matriz de costes avion
_  40  _
40  _  10
_  10  _


Coste del taxi = 20

tren                avion
(0)------------------(0)
 |        20          |
 | 5                  | 40
 |                    |
(1)------------------(1)
 |        20          |
 | 50                 | 10
 |                    |
(2)------------------(2)
          20

Para conseguir  esto se recurre a un supergrafo, colocando las matrices de costes en la diagonal
En la diagonal inversa se colocan los costes del taxi para poder cambiar de medio de circulacion en  una misma ciudad

_  5  _  20 _  _
5  _ 50  _  20 _
_  50 _  _  _  20
20 _  _  _  40 _
_  20 _  40 _  10
_  _  20 _  10 _

De esta manera se para viajar de 0 a 2 habria varios caminos diferentes:
 0tren-1tren-2tren
 0tren-1tren-2avion
 0tren-1avion-2tren
 0tren-1avion-2avion
 0avion-1tren-2tren
  ...
  Para que esto funcione con el supergrafo hay que tener en cuenta que el nodo 0 y el nodo numVert() se refieren a la misma ciudad
  El nodo 1 y el nodo numVert()+1 se refieren a la misma ciudad 
  etc...

  Si aplicamos Dijsktra a este supergrafo el vector que devuelve sera de tamaño 2*numVert() = 6 (en este caso)

  _  _  _  _  _  _
  0  1  2  3  4  5

  De la posicion 0 a la posicion 2 serian los costes minimos desde origen a cualquier ciudad en tren.
  De la posicion 3 a la posicion 5 (desde numVert() hasta 2*numVert()-1 ) serian los costes minimos desde origen
   hasta cualquier ciudad en avion.
*/
#include "GrafoP.hpp"
template<typename tCoste>
GrafoP<tCoste> SuperGrafo(GrafoP<tCoste>& g1, GrafoP<tCoste>& g2, tCoste taxi)
{
    int n = g1.numVert()+g2.numVert();
	GrafoP<tCoste> G(n);

    //Guardamos las ciudades de Fobos en el cuadrante 1 del supergrafo
	for (size_t i=0; i<g1.numVert(); i++)
		for (size_t j=0; j<g1.numVert(); j++)
			G[i][j] = g1[i][j];
    //Guardamos las ciudades de Deimos en el cuadrante 4 del supergrafo
	for (size_t i=0; i<g2.numVert(); i++)
		for (size_t j=0; j<g2.numVert(); j++)
			G[i+g1.numVert()][j+g1.numVert()] = g2[i][j];
    for(size_t i=0;i<g1.numVert();++i)
    {
            G[i][g1.numVert()+i]=taxi;
            G[g1.numVert()+i]=taxi;
    }
    return G;
}
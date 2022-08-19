#include <iostream>
#include <cmath>
#include <vector>

#include "lib/alg_grafoPMC.h"

using namespace std;//Avoid using std:: ....

int main(){
    
return 0;
}

/**
 /*
El archipiélago de Tombuctú, está formado por un número indeterminado de islas,
cada una de las cuales tiene, a su vez, un número indeterminado de ciudades. En
cambio, sí es conocido el número total de ciudades de Tombuctú (podemos llamarlo n,
por ejemplo).
Dentro de cada una de las islas existen carreteras que permiten viajar entre todas
las ciudades de la isla. Se dispone de las coordenadas cartesianas (x, y) de todas y cada
una de las ciudades del archipiélago. Se dispone de un grafo (matriz de adyacencia) en
el que se indica si existe carretera directa entre cualesquiera dos ciudades del
archipiélago. El objetivo de nuestro problema es encontrar qué ciudades de Tombuctú
pertenecen a cada una de las islas del mismo y cuál es el coste mínimo de viajar entre
cualesquiera dos ciudades de una misma isla de Tombuctú.
Así pues, dados los siguientes datos:
• Lista de ciudades de Tombuctú representada cada una de ellas por sus
coordenadas cartesianas,
• y matriz de adyacencia de Tombuctú, que indica las carreteras existentes en
dicho archipiélago,

implementa un subprograma que calcule y devuelva la distribución en islas de las
ciudades de Tombuctú, así como el coste mínimo de viajar entre cualesquiera dos
ciudades de una misma isla del archipiélago.

 */

//Con la matriz de adyacencia obtenemos que ciudades estan conectadas entre si, 
//y debemos calcular su distancia

/**
 * @brief Calcula la distancia a la que se en encuentran 
 * @param const pair<double,double> C1 , const pair<double,double> & C2
 * @return double
 */
double distancia_coordenadas(const pair<double,double> C1 , const pair<double,double> & C2){
    return sqrt( pow(C2.first - C1.first, 2 ) + pow(C2.second - C1.second, 2) );
}

matriz<double> tombuctu(GrafoP<bool> G, vector<pair<double,double>> Ciudades, Particion& P){

    //Recorremos el grafo de adyacencia para obtener las distancias 
    GrafoP<double>Distancias_entre_Ciudades(G.numVert());

    for(size_t i = 0 ; i < G.numVert() ; ++i){
        for (size_t j = 0; j < G.numVert(); j++)
        {
            //Si el par de ciudades estan conectadas entonces calculamos las distancias
            if(G[i][j]){
                
                //Metemos en la particion para obtener la distribucion
                if(P.encontrar(i) != P.encontrar(j)){//No estan en la misma particion, se incluyen
                    P.unir(i,j);
                }
                //Calculamos las distancias
                Distancias_entre_Ciudades[i][j] = distancia_coordenadas(Ciudades[i], Ciudades[j]);
            }

        }
        
    }

    //Calculo de los costes minimo de recorrer las ciudades
    matriz<typename GrafoP<double>::vertice > Caminos;
    auto caminos_minimos = Floyd(Distancias_entre_Ciudades, Caminos);

    return caminos_minimos;

}

/*
El archipiélago de Tombuctú está formado por un número desconocido de islas, cada
una de las cuales tiene, a su vez, un número desconocido de ciudades, las cuales tienen
en común que todas y cada una de ellas dispone de un aeropuerto.

Dentro de cada una de las islas existen carreteras que permiten viajar entre todas
las ciudades de la isla. No existen puentes que unan las islas y se ha decidido que la
opción de comunicación más económica de implantar será el avión.

Se dispone de las coordenadas cartesianas (x, y) de todas y cada una de las
ciudades del archipiélago. 

Se dispone de un grafo (matriz de adyacencia) en el que se indica si existe carretera directa 
entre cualesquiera dos ciudades del archipiélago. 

El objetivo de nuestro problema es encontrar qué líneas aéreas debemos implantar para
poder viajar entre todas las ciudades del archipiélago, siguiendo los siguientes criterios:

1) Se implantará una y sólo una línea aérea entre cada par de islas.
2) La línea aérea escogida entre cada par de islas será la más corta entre todas
las posibles.

Así pues, dados los siguientes datos:
• Lista de ciudades de Tombuctú representada cada una de ellas por sus
coordenadas cartesianas
• Matriz de adyacencia de Tombuctú que indica las carreteras existentes en
dicho archipiélago,

implementa un subprograma que calcule y devuelva las líneas aéreas necesarias para
comunicar adecuadamente el archipiélago siguiendo los criterios anteriormente
expuestos.
*/

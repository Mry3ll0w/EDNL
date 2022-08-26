#include <iostream>
//#include "lib/grafoPMC.h"
#include "lib/matriz.h"
#include "lib/alg_grafoPMC.h"
#include <numeric>
#include <cmath>
#include<string.h>

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
template <typename tCoste> 
tCoste max_inf(tCoste a, tCoste b)
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
            if (r[i][j] > Coste_viaje && r[i][j] != GrafoP<tCoste>::INFINITO && i != j)
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

//Funcion Ejercicio 2
/*
2. Se dispone de un laberinto de NxN casillas del que se conocen las casillas de entrada 
y salida del mismo. Si te encuentras en una casilla sólo puedes moverte en las siguientes 
cuatro direcciones (arriba, abajo, derecha, izquierda). Por otra parte, entre algunas de las 
casillas hay una pared que impide moverse entre las dos casillas que separa dicha pared 
(en caso contrario no sería un verdadero laberinto). 
Implementa un subprograma que dados 
    . N (dimensión del laberinto), 
    . la lista de paredes del laberinto, 
    . la casilla de entrada, y 
    . la casilla de salida, 
calcule el camino más corto para ir de la entrada a la salida y su longitud.
*/


/* Ejercicio 3
Eres el orgulloso dueño de una empresa de distribución. Tu misión radica en 
distribuir todo tu stock entre las diferentes ciudades en las que tu empresa dispone de 
almacén. 
Tienes un grafo representado mediante la matriz de costes, en el que aparece el coste 
(por unidad de producto) de transportar los productos entre las diferentes ciudades del 
grafo. 
Pero además resulta que los Ayuntamientos de las diferentes ciudades en las que 
tienes almacén están muy interesados en que almacenes tus productos en ellas, por lo 
que están dispuestos a subvencionarte con un porcentaje de los gastos mínimos de 
transporte hasta la ciudad. Para facilitar el problema, consideraremos despreciables los 
costes de volver el camión a su base (centro de producción). 
He aquí tu problema. Dispones de 
 el centro de producción, nodo origen en el que tienes tu producto (no tiene 
almacén), 
 una cantidad de unidades de producto (cantidad), 
 la matriz de costes del grafo de distribución con N ciudades, 
 la capacidad de almacenamiento de cada una de ellas, 
 el porcentaje de subvención (sobre los gastos mínimos) que te ofrece cada 
Ayuntamiento. 
Las diferentes ciudades (almacenes) pueden tener distinta capacidad, y además la 
capacidad total puede ser superior a la cantidad disponible de producto, por lo que 
debes decidir cuántas unidades de producto almacenas en cada una de las ciudades. 
Debes tener en cuenta además las subvenciones que recibirás de los diferentes 
Ayuntamientos, las cuales pueden ser distintas en cada uno y estarán entre el 0% y el 
100% de los costes mínimos. 
La solución del problema debe incluir las cantidades a almacenar en cada ciudad bajo 
estas condiciones y el coste mínimo total de la operación de distribución para tu 
empresa.
*/

//Se nos pide repartir el producto de la mejor forma posible entre las ciudades
template<class tCoste> 
matriz<tCoste> distribucion_productos(GrafoP<tCoste> & G, GrafoP<tCoste> & Subvencion, typename GrafoP<tCoste>::vertice origen,
float cantidad_disponible, GrafoP<tCoste>Almacenes){

    //Para realizar esto primero veremos cual seria el coste de movernos entre cada una de las ciudades
    //Para esto aplicamos Dijkstra
    typedef typename GrafoP<tCoste>::vertice vertice;
    vector<vertice> P;
    auto D = Dijkstra(G,origen,P);

    //Ahora restaremos el resultado de la subvencion al Coste
    for(vertice i = 0; i < G.numVert(); i++){
        D[i] = D[i] * (1. - Subvencion[origen][i] );
    }
    D[origen] = GrafoP<tCoste>::INFINITO;//Ya que no iremos al origen

    //Ordenamos segun el coste de distancia
    std::vector<int> vertices;//inicializamos el vector de vertices
    for (size_t i = 0; i < G.numVert(); i++)
    {
        vertices.push_back(i);
    }
    
    //Ordenamos para darle prioridad a los almacenes menos costosos
    for(size_t i = 0; i < G.numVert()-1; i++){

        if (D[i] > D[i+1])
        {
            swap(vertices[i],vertices[i+1]);//ordenamos los vertices en funcion del orden
        }
        

    }
    
    //Metemos en cada almacen la cantidad necesaria hasta quedarnos vacios
    //Nos piden el coste total, ademas de cuanta cantidad va en cada almacen

    matriz<tCoste> dado_almacenes(G.numVert(),0);//Guarda las cantidades dadas a cada almacen, inicialmente a 0
    float Coste_total_operaciones = 0;
    for (size_t i = 0; i < G.numVert() && cantidad_disponible > 0; i++)
    {
        //Actualizamos las cantidades
        if(cantidad_disponible - Almacenes[origen][vertices[i]] > 0){//usamos vertices como indice ya que esta ordendo segun a quien dar primero
            //Actualizamos lo almacenado en el almacen
            dado_almacenes[origen][vertices[i]] = Almacenes[origen][vertices[i]];
            cantidad_disponible -= Almacenes[origen][i];
        }
        else{
            dado_almacenes[origen][vertices[i]]=cantidad_disponible;
            cantidad_disponible =0;
        }

        //Actualizamos los costes totales de hacer la inversion
        Coste_total_operaciones += D[vertices[i]];
        
    }
    
    //Mostramos los costes por pantalla y devolvemos la matriz con lo guardado en los almacenes (se que se debe devolver por parametros pero pereza)
    cout<< "Los costes totales de realizar la operacion son de : "<<Coste_total_operaciones<<endl;

    return dado_almacenes;


}

/*
Eres el orgulloso dueño de la empresa “Cementos de Zuelandia S.A”. Empresa 
dedicada a la fabricación y distribución de cemento, sita en la capital de Zuelandia. 
Para la distribución del cemento entre tus diferentes clientes (ciudades de Zuelandia) 
dispones de una flota de camiones y de una plantilla de conductores zuelandeses. 
El problema a resolver tiene que ver con el carácter del zuelandés. El zuelandés es 
una persona que se toma demasiadas “libertades” en su trabajo, de hecho, tienes 
fundadas sospechas de que tus conductores utilizan los camiones de la empresa para 
usos particulares (es decir indebidos, y a tu costa) por lo que quieres controlar los 
kilómetros que recorren tus camiones. 

Todos los días se genera el parte de trabajo, en el que se incluyen el número de 
cargas de cemento (1 carga = 1 camión lleno de cemento) que debes enviar a cada 
cliente (cliente = ciudad de Zuelandia). Es innecesario indicar que no todos los días hay 
que enviar cargas a todos los clientes, y además, puedes suponer razonablemente que tu 
flota de camiones es capaz de hacer el trabajo diario. 
Para la resolución del problema quizá sea interesante recordar que Zuelandia es un 
país cuya especial orografía sólo permite que las carreteras tengan un sentido de 
circulación. 

Implementa una función que dado el grafo con las distancias directas entre las 
diferentes ciudades zuelandesas, el parte de trabajo diario, y la capital de Zuelandia, 
devuelva la distancia total en kilómetros que deben recorrer tus camiones en el día, para 
que puedas descubrir si es cierto o no que usan tus camiones en actividades ajenas a la 
empresa.
*/

//El parte tiene almacenado los costes totales dados por el empleado
template<class tCoste>
double repartir_carga(GrafoP<tCoste> & G, typename GrafoP<tCoste>::vertice capital,vector<int> cargas){

    //Al ser una grafo dirigido no tiene que valer lo mismo el camino de A -> B que de B -> A,
    //Por tanto debemos tener en cuenta la ida y la vuelta para los costes totales
    

    //Hacemos Floyd para hallar todos los caminos
    matriz<tCoste>P;
    auto coste_caminos = Floyd(G,P);

    double coste_total = 0.00;
    typedef typename GrafoP<tCoste>::vertice vertice;
    //Recorremos los costes de la capital, para hallar los costes de ida y vuelta
    for(vertice i = 0; i < G.numVert(); i++){

        if (coste_caminos[capital][i]!= GrafoP<tCoste>::INFINITO)//Si hay coste infinito significa que no se puede llegar
        {
            coste_total += cargas[i] * (coste_caminos[capital][i] + coste_caminos[i][capital]);//carga * (costes ida + costes vuelta)
        }
        

    }   

return coste_total;

}

/*

Se dispone de tres grafos que representan la matriz de costes para viajes en un 
determinado país pero por diferentes medios de transporte, por supuesto todos los grafos 
tendrán el mismo número de nodos. El primer grafo representa los costes de ir por 
carretera, el segundo en tren y el tercero en avión. Dado un viajero que dispone de una 
determinada cantidad de dinero, que es alérgico a uno de los tres medios de transporte, y 
que sale de una ciudad determinada, implementar un subprograma que determine las 
ciudades a las que podría llegar nuestro infatigable viajero

*/
template<class tCoste>
matriz<tCoste> viaje(GrafoP<tCoste>& avion, GrafoP<tCoste>& coche, GrafoP<tCoste> & tren, double dinero, string& alergico){

    typedef typename GrafoP<tCoste>::vertice vertice;
    //Primero vemos a que transporte es alergico
    GrafoP<tCoste> g1,g2;
    //Aplicamos Floyd al resto de los grafos para ver desde donde podemos ir con cada medio
    if (alergico == "avion")
    {
        g1 = Floyd(tren,g1);
        g2 = Floyd(coche,g2); 
    }
    else if(alergico == "tren"){
        g1 = Floyd(avion,g1);
        g2 = Floyd(coche,g2);
    }
    else{
        g1 = Floyd(avion,g1);
        g2 = Floyd(tren,g2);
    }
    int N = g1.numVert();
    
    //Una vez aplicado Floyd simplemente recorremos la matriz para ver si es posible viajar de un punto A -> B
    GrafoP<tCoste> res(N);
    int dinero_it =dinero;
    for (vertice i = 0; i < N; i++)
    {
        dinero_it =dinero;
        for (vertice j = 0; j < N; j++)
        {
            //Comprobamos cual es el minimo entre las opciones disponibles y lo restamos del dinero disp
            int coste = min(g1[i][j],g2[i][j]);
            if((dinero_it - coste) > 0){
                res[i][j]=coste;
            }
        }
        
    }
    
    return res;

}

/*Ejercicio 6

Al dueño de una agencia de transportes se le plantea la siguiente situación. La 
agencia de viajes ofrece distintas trayectorias combinadas entre N ciudades españolas 
utilizando tren y autobús. Se dispone de dos grafos que representan los costes (matriz de 
costes) de viajar entre diferentes ciudades, por un lado en tren, y por otro en autobús 
(por supuesto entre las ciudades que tengan línea directa entre ellas). Además coincide 
que los taxis de toda España se encuentran en estos momentos en huelga general, lo que 
implica que sólo se podrá cambiar de transporte en una ciudad determinada en la que, 
por casualidad, las estaciones de tren y autobús están unidas.

Implementa una función que calcule la tarifa mínima (matriz de costes mínimos) de 
viajar entre cualesquiera de las N ciudades disponiendo del grafo de costes en autobús, 
del grafo de costes en tren, y de la ciudad que tiene las estaciones unidas. 

*/

template<class tCoste>
matriz<tCoste> tarifa_minima(GrafoP<tCoste> & tren, GrafoP<tCoste>& autobus, GrafoP<bool>unidas){

    typedef typename GrafoP<tCoste>::vertice vertice;

    int N = tren.numVert();
    
    matriz<tCoste> P;
    
    GrafoP<tCoste> ftren(tren.numVert()), fautobus(tren.numVert()), tarifa{tren.numVert()};

    //Floyd para hallar los costes minimos
    ftren = Floyd(tren,P);
    fautobus = Floyd(autobus,P);

    //Hallamos el coste de la tarifa minima
    for(vertice i = 0; i < N; i++){
        
        for (vertice j = 0; j < N; j++)
        {
            if (unidas[i][j]==true)//Si estan unidas cogemos el minimo entre el tren o el autobus
            {
                tarifa[i][j]=min(ftren[i][j],fautobus[i][j]);
            }
            else if(ftren[i][j] == GrafoP<tCoste>::INFINITO){
                tarifa[i][j] = fautobus[i][j]; 
            }
            else{ //No tiene estacion de autobus
                tarifa[i][j]=ftren[i][j];
            }
        }
        
    }

    return tarifa;

}


int main(){
    typedef unsigned int tCoste;
    //Creamos un grafo
    GrafoP<tCoste> G("lib/data/ejpmc.txt");
    std::cout << " ** Se rellena G ** " << std::endl;
    std::cout << G << std::endl;

    solucion_ej1(G);



    
    return 0;
}


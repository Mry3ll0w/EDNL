#include <iostream>
#include <string>
#include "lib/alg_grafoPMC.h"
using namespace std;//Avoid using std:: ....

/**
 * Enunciado Ejercicio 5:
 * Se dispone de tres grafos que representan la matriz de costes para viajes en un 
 * determinado país pero por diferentes medios de transporte, por supuesto todos los 
 * grafos tendrán el mismo número de nodos. El primer grafo representa los costes de 
 * ir por carretera, el segundo en tren y el tercero en avión. 
 * Dado un viajero que 
 * dispone de una determinada cantidad de dinero, que es alérgico a uno de los tres 
 * medios de transporte, y que sale de una ciudad determinada, implementar un subprograma 
 * que determine las ciudades a las que podría llegar nuestro infatigable viajero.
 */
template <class T>
const Lista<typename GrafoP<T>::vertice> ej5(const double &Dinero,
    const typename GrafoP<T>::vertice Origen, const GrafoP<T> &Tren,
    const GrafoP<T> & Avion, const GrafoP<T>& Carretera, 
    const string& Alergia)
{
    //Primero Descartamos que alergia tiene el cliente
    GrafoP<T> G1, G2;
    if(Alergia == "Tren"){
        G1 = Carretera;
        G2 = Avion;
    }
    else if(Alergia == "Carretera"){
        G1 = Avion;
        G2 = Tren;
    }
    else
        G1 = Tren; G2 = Carretera;
    
    //Creamos un supergrafo, formados por los grafos de tren y avion, para mas tarde 
    //aplicarle Dijkstra

    

    //Inicializamos el grafo
    GrafoP<T> Final;

    for(size_t i = 0; i < N; ++i){
        
        for (size_t j = 0; j < N; j++)
        {
            //Metemos los datos del primer medio de transporte
            Final[i][j] = min(G1[i][j], G2[i][j]);
        }
        
    }

    //Una vez creado el superGrafo aplicamos Dijkstra para obtener el coste de viajar entre ellos
    vector<GrafoP<T>::vertice> P, CostesMinimos;
    CostesMinimos = Dijkstra(Final, Origen, P);

    //Tras Obtener Dijkstra y tener los caminos minimos partimos a comprobar que
    //A que ciudades puede ir el viajero

    Lista<GrafoP<T>::vertice> Destinos_Visitables;

    for(size_t i = 0; i < CostesMinimos.size(); ++i){
        
        if(CostesMinimos[i] < Dinero){
            Destinos_Visitables.insertar(i, Destinos_Visitables.fin());
        }

    }
return Destinos_Visitables;
}

/**ENUNCIADO PROBLEMA 6
 * 
 * Al dueño de una agencia de transportes se le plantea la siguiente situación. 
 * La agencia de viajes ofrece distintas trayectorias combinadas entre N ciudades 
 * españolas utilizando tren y autobús. 
 * Se dispone de dos grafos que representan 
 * los costes (matriz de costes) de viajar entre diferentes ciudades, por un lado en 
 * tren, y por otro en autobús (por supuesto entre las ciudades que tengan línea 
 * directa entre ellas). 
 * Además coincide que los taxis de toda España se encuentran en estos momentos en 
 * huelga general, lo que implica que sólo se podrá cambiar de transporte en una 
 * ciudad determinada en la que, por casualidad, las estaciones de tren y autobús 
 * están unidas.
 * 
 * Implementa una función que calcule la tarifa mínima (matriz de costes mínimos) 
 * de viajar entre cualesquiera de las N ciudades disponiendo del grafo de costes 
 * en autobús, del grafo de costes en tren, y de la ciudad que tiene las estaciones unidas.
 * 
 */

template<class T>
matriz<T> ej6(const GrafoP<T> & Tren, const GrafoP<T>& Bus, 
    const typename GrafoP<T>::vertice Cambio
){

    //Primero calculamos cuanto sale viajar como minimo usando únicamente bus
    vector<typename GrafoP<T>::vertice> P;
    GrafoP<T> f_bus, f_tren;
    f_bus = Floyd(f_bus, P);
    f_tren = Floyd(f_tren, P);

    //Recorremos las matrices para ver donde podemos hacer el cambio
    matriz<T> Tarifa(Tren.numVert());

    //Recorremos todos los elementos de Floyd para ver que nos resulta mas barato
    for(size_t i = 0; i< Tren.numVert(); ++i){
        for (size_t j = 0; j < Tren.numVert(); j++)
        {
            Tarifa[i][j] = min(
                f_tren[i][j], //Ir solo en tren
                f_bus[i][j], //Ir solo en bus
                f_tren[i][cambio] + f_bus[cambio][j],//Ir en tren y cambiar a bus
                f_bus[cambio][j] + f_tren[cambio][j]//Ir en bus y cambiar a tren
            )
        }
        
    }
    return Tarifa;
}

/**
 * Enuncjado Ejercicio 7
 * Se dispone de dos grafos (matriz de costes) que representan los costes de viajar entre 
 * N ciudades españolas utilizando el tren (primer grafo) y el autobús (segundo grafo). 
 * Ambos grafos representan viajes entre las mismas N ciudades.
 * Nuestro objetivo es hallar el camino de coste mínimo para viajar entre dos ciudades 
 * concretas del grafo, origen y destino, en las siguientes condiciones:
 * - La ciudad origen sólo dispone de transporte por tren.
 * - La ciudad destino sólo dispone de transporte por autobús.
 * - El sector del taxi, únicamente es posible cambiar de transporte en dos ciudades del grafo, 
 * cambio1 y cambio2, donde las estaciones de tren y autobús están unidas.
 * 
 * Implementa un subprograma que calcule la ruta y el coste mínimo para viajar entre 
 * las ciudades Origen y Destino en estas condiciones.
 */
template <class T>
pair<int, vector<typename GrafoP<T>::vertice>> ej7(
    const typename GrafoP<T>::vertice &Cambio1, const typename GrafoP<T>::vertice &Cambio2,
    const typename GrafoP<T>::vertice &Origen, const typename GrafoP<T>::vertice &Destino,
    const GrafoP<T> Tren, const GrafoP<T> Bus, const GrafoP<bool> Unidas
)
{
    //Al tratarse de un origen destino ==> Dijkstra

    //Mejores costesd de ir en tren solo y mejores costes de ir solo en bus
    GrafoP<T> d_bus, d_tren, 
    c1_destino_tren, d_c1_tren, ori_c1_tren, c1_ori_tren,
    c1_destino_bus, d_c1_bus, ori_c1_bus, c1_origen_Bus;
    vector<T> P;
    //Costes desde origen hasta destino directo
    d_bus = Dijkstra(Bus, Origen, P);//Cuanto vale coste directo desde o --> d
    d_tren = Dijkstra(Tren, Origen, P);        // Cuanto vale coste directo desde o --> d

    //Costes con los cambios
    c1_destino_bus = Dijkstra(Bus, Cambio1, P);//Coste desde C1 hasta D
    
    auto destino_bus_c1 = Dijkstra(Bus, Destino, P);//Costede desde D hasta C


    //Costes desde c1 hasta d usando bus
    c1_destino_bus = Dijkstra(Bus, Cambio1, P);
    destino_bus_c1 = Dijkstra(Bus,Cambio1, P);

    ori_c1_bus = Dijkstra(Bus, Cambio1, P);
    c1_origen_Bus = Dijkstra(Bus, Cambio1, P);

    //Coste minimo de ir en bus con el cambio 1 nada mas
    T CostesMinimosBus_cambio1 = c1_destino_bus[Destino] + destino_bus_c1[Cambio1] + ori_c1_bus[Cambio1] + c1_origen_Bus[Origen];


    //igual con tren y devolvemos el minimo


}

/**
 * “UN SOLO TRANSBORDO, POR FAVOR”. Este es el título que reza en tu flamante compañía de viajes.
 * Tu publicidad explica, por supuesto, que ofreces viajes combinados de TREN y/o AUTOBÚS 
 * (es decir, viajes en tren, en autobús, o usando ambos), entre N ciudades del país, 
 * en todos tus viajes COMO MÁXIMO 
 * se hará un solo transbordo (cambio de medio de transporte). 
 * Te explica que quiere viajar entre dos ciudades, Origen y Destino, y quiere saber cuánto 
 * le costará.
 * 
 * Para responder a esa pregunta dispones de dos grafos de costes directos 
 * (matriz de costes) de viajar entre las N ciudades del país, 
 * un grafo con los costes de viajar en tren y otro en autobús.
 * 
 * Implementa un subprograma que calcule la tarifa mínima en estas condiciones. 
 * 
 */
template<class T>
T ej8(const GrafoP<T> & Tren, const GrafoP<T>& Bus, const size_t & N,
    const typename GrafoP<T>::vertice Origen, const typename GrafoP<T>::vertice Destino
){

    //Calculamos cuanto vale ir directamente desde origen a destino directamente
    vector<GrafoP<T>::vertice>> P;
    auto O_D_Bus = Dijkstra(Bus, Origen, P);
    auto O_D_Tren = Dijkstra(Tren, Origen,P);

    //Hacemos Dijkstra para obtener el desde el destino al resto para comprobar donde hacer el 
    //cambio si lo hacemos

    auto D_Bus_resto = Dijkstra(Bus, Destino, P);
    auto D_Tren_resto = Dijkstra(Tren, Destino, P);


    //Calculamos el minimo y donde hacer el salto con transbordos
    T Tarifa_minima_con_cambio = 999999;
    for(size_t i = 0; i < N; ++i){

        Tarifa_minima_con_cambio = min(
            (O_D_Bus[i] + D_Tren_resto[i]),
            (O_D_Tren[i] + D_Bus_resto[i]),
            Tarifa_minima_con_cambio
        )

    }
    
    //Tras tener la tarifa minima con el cambio comprobaremos cual es el minimo
    //Sin cambios tren / bus o realizando un único cambio
    return min(Tarifa_minima_con_cambio, O_D_Bus[Destino], O_D_Tren[Destino]);
    //Ya que el cambio no es obligatorio que sea realizadoº
}

/**
 * Ejercicio 9 :
 * Se dispone de dos grafos que representan la matriz de costes para viajes en un 
 * determinado país, pero por diferentes medios de transporte (tren y autobús, por ejemplo). 
 * Por supuesto ambos grafos tendrán el mismo número de nodos, N. 
 * Dados:
 *  ambos grafos, 
 *  una ciudad de origen, 
 * una ciudad de destino y 
 * el coste del taxi para cambiar de una 
 * estación a otra dentro de cualquier ciudad (se supone constante e igual para todas las 
 * ciudades), 
 * 
 * Implementa un subprograma que calcule el camino y el coste mínimo para ir de 
 * la ciudad origen a la ciudad destino.
 */
template <class T>
T ej9(const GrafoP<T> & G1, const GrafoP<T> & G2, T Coste_Taxi, const int& N,
    const typename GrafoP<T>::vertice& Origen, const typename GrafoP<T>::vertice& Destino
)
{

    //Creamos un SuperGrafo para unificar los dos
    GrafoP<T> SuperGrafo(N);

    for(size_t i = 0; i < N+N ; ++i){

        //Costes del taxi añadidos en la unión
        SuperGrafo[i+N][i] = Coste_Taxi;
        SuperGrafo[i][i+N] = Coste_Taxi;

        for (size_t j = 0; j < N+N; j++)
        {
            if(i < N && j < N){
                SuperGrafo[i][j] = G1[i][j];
            }
            else if (
                i >= N && i <= G1.numVert() + G2.numVert() &&
                && j <= G1.numVert() + G2.numVert() &&
                j >= N)
            {
                SuperGrafo[i][j] = G2[i - G1.numVert()][j-G2.numVert()];
            }

            
        }
        
        

    }

    //Aplicamos Floyd para obtener costes minimos
    vector<GrafoP<T>::vertice> P;
    auto F_SuperGrafo = Floyd(SuperGrafo, P);

    return min(
        F_SuperGrafo[Origen][Destino],//Ir en unicamente en tren
        F_SuperGrafo[Origen+N][Destino], //Salir en autobus y llegar en tren
        F_SuperGrafo[Origen][Destino + N],//Salir en tren y llegar en autobus
        F_SuperGrafo[Origen + N][Destino + N]//Unicamente en Bus
    );

}



int main()
{

    return 0;
}
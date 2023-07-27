#ifndef PRACTICA7_HPP_
#define PRACTICA7_HPP_
#include "GrafoP.hpp"
#include "matriz.hpp"
#include "Dijkstra.hpp"
#include "Floyd.hpp"
#include<iostream>
template<typename tCoste>
GrafoP<tCoste> SuperGrafo(GrafoP<tCoste>& g1, GrafoP<tCoste>& g2)
{
    int n = g1.numVert()+g2.numVert();
	GrafoP<tCoste> G(n);

    //Guardamos las ciudades de Fobos en el cuadrante 1 del supergrafo
	for (int i=0; i<g1.numVert(); i++)
		for (int j=0; j<g1.numVert(); j++)
			G[i][j] = g1[i][j];
    //Guardamos las ciudades de Deimos en el cuadrante 4 del supergrafo
	for (int i=0; i<g2.numVert(); i++)
		for (int j=0; j<g2.numVert(); j++)
			G[i+g1.numVert()][j+g1.numVert()] = g2[i][j];
    return G;
}

/* 1.-
Tu agencia de viajes “OTRAVEZUNGRAFO S.A.” se enfrenta a un curioso cliente.
Es un personaje sorprendente, no le importa el dinero y quiere hacer el viaje más caro
posible entre las ciudades que ofertas. Su objetivo es gastarse la mayor cantidad de
dinero posible (ojalá todos los clientes fueran así), no le importa el origen ni el destino
del viaje.
Sabiendo que es imposible pasar dos veces por la misma ciudad, ya que casualmente
el grafo de tu agencia de viajes resultó ser acíclico, devolver el coste, origen y destino
de tan curioso viaje. Se parte de la matriz de costes directos entre las ciudades del grafo.
*/
template<typename tCoste> //Negar los valores de un grafo
GrafoP<tCoste> invertir(GrafoP<tCoste> g)
{
    for(size_t i=0;i<g.numVert();++i)
    {
        for(size_t j=0;j<g.numVert();++j)
        {
            if(g[i][j]!=GrafoP<tCoste>::INFINITO)
                g[i][j]=(-1)*g[i][j];
        }
    }
    return g;
}
template<typename tCoste> //Negar los valores de una matriz
matriz<tCoste> invertir(matriz<tCoste> m)
{
    for(size_t i=0;i<m.dimension();++i)
    {
        for(size_t j=0;j<m.dimension();++j)
        {
            m[i][j]=(-1)*m[i][j];
        }
    }
    return m;
}

template<typename tCoste>
struct viaje
{
    tCoste importe;
    typename GrafoP<tCoste>::vertice origen, destino;
};
template<typename tCoste>
viaje<tCoste> maximizar(GrafoP<tCoste> g)
{
    matriz<typename GrafoP<tCoste>::vertice> P;
    //Floyd calcula la matriz de costes minimos, para que calcule la matriz de costes maximos, negamos los costes
    //y a continuacion aplicamos Floyd
    g=invertir(g);
    matriz<tCoste> costes=Floyd(g, P);
    costes=invertir(costes);
    viaje<tCoste> viaje_caro;
    viaje_caro.importe=-GrafoP<tCoste>::INFINITO;
    //Buscamos el valor mas alto de la matriz de Floyd y nos vamos quedando con el origen y el destino
    for(size_t i=0;i<costes.dimension();++i)
    {
        for(size_t j=0;j<costes.dimension();++j)
        {
            if(costes[i][j]>viaje_caro.importe && costes[i][j]!=GrafoP<tCoste>::INFINITO)
            {
                viaje_caro.importe=costes[i][j];
                viaje_caro.origen=i;
                viaje_caro.destino=j;
            }
        }
    }
    return viaje_caro;
}
/* 2.-
Se dispone de un laberinto de n×n casillas del que se conocen las casillas de entrada
y salida del mismo. Si te encuentras en una casilla sólo puedes moverte en las siguientes
cuatro direcciones (arriba, abajo, derecha, izquierda). Por otra parte, entre algunas de las
casillas hay una pared que impide moverse entre las dos casillas que separa dicha pared
(si no, no sería un verdadero laberinto).
Implementa un subprograma que dados
• un laberinto de N×N casillas, representado mediante una matriz de n×n,
• la lista de paredes del laberinto,
• la casilla de entrada, y
• la casilla de salida,
calcule el camino más corto para ir de la entrada a la salida y su longitud.
*/
template<typename tCoste>
tCoste laberinto(matriz<bool> lab, typename GrafoP<tCoste>::vertice origen, typename GrafoP<tCoste>::vertice destino, matriz<bool> paredes)
{
    tCoste costeMin=GrafoP<tCoste>::INFINITO;
    Grafo laberinto(lab.dimension());
    //Pasar la matriz de nxn a un grafo no ponderado de n^2 x n^2
    for(size_t i=0;i<lab.dimension();++i)
    {
        for(size_t j=0;j<lab.dimension();++j)
        {
            
        }
    }
    //Cerramos los caminos donde hay una pared
    for(size_t i=0;i<paredes.dimension();++i)
    {
        for(size_t j=0;j<paredes.dimension();++j)
        {
            if(paredes[i][j]==true)
                g[i][j]=GrafoP<tCoste>::INFINITO;
        }
    }
    //Calcular los costes minimos del origen a todos los vertices
    std::vector<typename GrafoP<tCoste>::vertice> P;
    std::vector<tCoste> costes=Dijkstra(g, origen, P);
    //Devolver el coste minimo al destino
    return costes[destino];
}
/*3.-
3. Eres el orgulloso dueño de una empresa de distribución. Tu misión radica en
distribuir todo tu stock entre las diferentes ciudades en las que tu empresa dispone de
almacén.

Tienes un grafo representado mediante la matriz de costes, en el que aparece el coste
(por unidad de producto) de transportar los productos entre las diferentes ciudades del
grafo.
Pero además resulta que los Ayuntamientos de las diferentes ciudades en las que
tienes almacén están muy interesados en que almacenes tus productos en ellas, por lo
que están dispuestos a subvencionarte con un porcentaje de los gastos mínimos de
transporte hasta la ciudad.
He aquí tu problema. Dispones de
• el centro de producción, nodo origen en el que tienes tu producto (no tiene
almacén),
• una cantidad de unidades de producto (cantidad),
• la matriz de costes del grafo de distribución con n ciudades (almacenes),
• la capacidad de almacenamiento de cada una de ellas,
• el porcentaje de subvención (sobre los gastos mínimos) que te ofrece cada
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
template<typename tCoste>
double distribucion(GrafoP<tCoste>& g, typename GrafoP<tCoste>::vertice origen, int stock, std::vector<int> capacidad,
std::vector<double> subvenciones, std::vector<int>& productos)
{
    double costeTotal;
    //Calculamos los costes minimos desde origen al resto de las ciudades. Usamos Dijkstra
    std::vector<typename GrafoP<tCoste>::vertice> P;
    std::vector<tCoste> costes=Dijkstra(g, origen, P);
    //Vector para almacenar los costes finales una vez aplicadas las subvenciones y las unidades de producto
    std::vector<double> costesFinales(costes.size());
    //Aplicamos las subvenciones. Cada coste sera
    for(size_t i=0;i<subvenciones.size();++i)
        costesFinales[i]=((100-subvenciones[i])/100)*costes[i];

    //Ahora hay que hacer el reparto de todo el stock
    std::vector<bool> almacenes_llenos(costesFinales.size(),false);
    typename GrafoP<tCoste>::vertice destino;
    tCoste costeMin=GrafoP<tCoste>::INFINITO;
    while(stock>0)
    {
        for(typename GrafoP<tCoste>::vertice v=0;v<g.numVert();++v)
        {
            if(v!=origen)
            {
                //Buscamos el almacen donde resulta mas barato almacenar la mercancia
                if(costesFinales[v]<costeMin && !almacenes_llenos[v])
                {
                    costeMin=costesFinales[v];
                    destino=v;
                }
            }
        }
        //Hemos calculado el almacen donde cuesta menos almacenar
        if(capacidad[destino]<=stock)
        {
            stock=stock-capacidad[destino];
            productos[destino]=capacidad[destino];
        } 
        else
        {
            productos[destino]=stock;
            stock=0;
        }
        almacenes_llenos[destino]=true;
    }
    //Recorremos todos los almacenes que se han llenado y sumamos los costes de llegar hasta cada uno de ellos
    for(int i = 0 ; i < almacenes_llenos.size() ; i++){
		if(almacenes_llenos[i] == true)
			costeTotal += costesFinales[i];
	}
	//Devolvemos el coste total de llenar los almacenes hasta que no queda stock
    return costeTotal;
}
/* 4.-
Eres el orgulloso dueño de la empresa “Cementos de Zuelandia S.A”, empresa
dedicada a la fabricación y distribución de cemento, sita en la capital de Zuelandia. Para
la distribución del cemento entre tus diferentes clientes (ciudades de Zuelandia)
dispones de una flota de camiones y de una plantilla de conductores zuelandeses.
El problema a resolver tiene que ver con el carácter del zuelandés. Estos son
personas que se toman demasiadas “libertades” en su trabajo; de hecho, tienes fundadas
sospechas de que tus conductores utilizan los camiones de la empresa para usos
particulares (es decir indebidos, y a tu costa) por lo que quieres controlar los kilómetros
que recorren tus camiones.
Todos los días se genera el parte de trabajo, en el que se incluyen el número de
cargas de cemento (1 carga = 1 camión lleno de cemento) que debes enviar a cada
cliente (cliente = ciudad de Zuelandia). Es innecesario indicar que no todos los días hay
que enviar cargas a todos los clientes, y además, puedes suponer razonablemente que tu
flota de camiones es capaz de realizar el trabajo diario.
Para la resolución del problema quizá sea interesante recordar que Zuelandia es un
país cuya especial orografía sólo permite que las carreteras tengan un sentido de
circulación.
Implementa una función que dado el grafo con las distancias directas entre las
diferentes ciudades zuelandesas, el parte de trabajo diario, y la capital de Zuelandia,
devuelva la distancia total en kilómetros que deben recorrer tus camiones en el día, para
que puedas descubrir si es cierto o no que usan tus camiones en actividades ajenas a la
empresa.
*/
template<typename tCoste>
double cementos(GrafoP<tCoste>& g, std::vector<int> parte_diario, typename GrafoP<tCoste>::vertice capital)
{
    double totalKm;
    //Obtenemos los costes minimos desde la capital a cada ciudad
    matriz<typename GrafoP<tCoste>::vertice> Q;
    matriz<tCoste> costes=Floyd(g, Q);

    //Recorremos los pedidos diarios
    for(size_t i=0;i<parte_diario.size();++i)
    {
        if(parte_diario[i]>0)
        {
            //Calculamos para este pedido los km de ida y de vuelta
            if(capital!=i && costes[capital][i]!=GrafoP<tCoste>::INFINITO && costes[i][capital]!=GrafoP<tCoste>::INFINITO  )
                totalKm=(costes[capital][i]+costes[i][capital])*parte_diario[i];
        }
    }
    return totalKm;
}
/*
Disponemos de dos grafos que nos indican los precios de viajar entre diferentes ciudades por tren y por avion
Del coste del taxi para cambiar dentro de una misma ciudad de tren a avion y viceversa
Asumiendo que el coste del taxi es constante e igual para todas las ciudades,
implementa una función que calcule el camino y el coste mínimo para ir de la ciudad
origen a la ciudad destino.
*/
double supergrafo(GrafoP<double>& tren,GrafoP<double>& avion, typename GrafoP<double>::vertice origen,
typename GrafoP<double>::vertice destino)
{
    double precio_taxi_tren_avion=20.0;
    double costeMin=GrafoP<double>::INFINITO;
    size_t n=tren.numVert();
    /*Se usa Dijkstra para poder calcular los saltos intermedios de tren a avion y viceversa
    Pero para ello necesitamos que toda la informacion esté en un solo grafo
    Se crea un supergrafo:
    1.-El tamaño del supergrafo es numVert()*numero de grafos que hay
    2.-El cuadrante 0,0 es el grafo 1, el cuadrante 1,1 es el grafo 2, etc
    3.-El resto de cuadrantes se rellenan de INFINITO excepto la diagonal principal de cada uno que se rellena con
        el precio del cambio (taxi). El precio del taxi es el nexo de union entre los grafos
    */
    GrafoP<double> sG(n*2);
    for(size_t i=0;i<n;++i)
    {
        for(size_t j=0;j<n;++j)
        {
            //Rellenamos los cuadrantes 1 y 4
            sG[i][j]=tren[i][j];
            sG[i+n][j+n]=avion[i][j];
            //Rellenamos los cuadrantes 2 y 3
            sG[i][i+n] = precio_taxi_tren_avion;
			sG[i+n][i] = precio_taxi_tren_avion;
        }
    }
    //Realizamos Dijkstra con el supergrafo con la ciudad origen para el tren y para el avion
    std::vector<typename GrafoP<double>::vertice> PT, PA;

    std::vector<double> costes1=Dijkstra(sG, origen, PT); //Costes para ir solo en tren pos=0-2, solo en avion pos=3-5
    std::vector<double> costes2=Dijkstra(sG, origen+n, PA); //Costes para ir tren-avion pos=0-2, avion-tren pos=3-5

    //std::cout << costes1 << std::endl;
    //std::cout << costes2 << std::endl;
    //std::cout << "Caminos" << std::endl;
    //std::cout << PA << std::endl;

    //std::cout << sG << std::endl;
    //para ir solo en tren
    if(costes1[destino]<costeMin)
        costeMin=costes1[destino];
    //Para ir tren-avion
    if(costes1[destino+n]<costeMin)
        costeMin=costes1[destino+n];
    //para ir solo en avion
    if(costes2[destino+n]<costeMin)
        costeMin=costes2[destino+n];
    //para ir avion-tren
    if(costes2[destino]<costeMin)
        costeMin=costes2[destino];

    return costeMin;
}


void prueba_supergrafo()
{
    GrafoP<double> g1(3), g2(3);

    g1[0][1]=5.0;
    g1[1][2]=50.0;

    g2[0][1]=40.0;
    g2[1][2]=10.0;

    std::cout<< supergrafo(g1,g2,0,2) << std::endl;
}
/* 5.-
Se dispone de tres grafos que representan la matriz de costes para viajes en un
determinado país pero por diferentes medios de transporte, por supuesto todos los grafos
tendrán el mismo número de nodos.
El primer grafo representa los costes de ir por carretera,
el segundo en tren
y el tercero en avión.
Dado un viajero que dispone de una determinada cantidad de dinero, que es alérgico a uno de los tres medios
de transporte, y que sale de una ciudad determinada, implementar una función que determine las
ciudades a las que podría llegar nuestro infatigable viajero.
*/
template<typename tCoste>
std::vector<bool> infatigable(GrafoP<tCoste>& grafo1, GrafoP<tCoste>& grafo2,
typename GrafoP<tCoste>::vertice origen, double dinero)
{
    GrafoP<tCoste> grafo;
    std::vector<typename GrafoP<tCoste>::vertice> P1,P2;
    std::vector<bool> ciudades_visitables(grafo1.numVert(),false);
    //Obtenemos los costes para ir a cada ciudad por un medio diferente

    std::vector<tCoste> costes_g1=Dijkstra(grafo1, origen, P1);
    std::vector<tCoste> costes_g2=Dijkstra(grafo2, origen, P2);

    //Recorremos ambos vectores de costes y nos quedamo con los mas pequeños
    //Actualizamos el dinero y marcamos la ciudad como visitable
    for(size_t i=0;i<costes_g1.size();++i)
    {
        if(costes_g1[i]<costes_g2[i])
            dinero=dinero-costes_g1[i];
        else
            dinero=dinero-costes_g2[i];
        if(dinero>0)
            ciudades_visitables[i]=true;
    }
    return ciudades_visitables;
}
/* 6.-
Al dueño de una agencia de transportes se le plantea la siguiente situación. La
agencia de viajes ofrece distintas trayectorias combinadas entre n ciudades españolas
utilizando tren y autobús. Se dispone de dos grafos que representan los costes (matriz de
costes) de viajar entre diferentes ciudades, por un lado en tren, y por otro en autobús
(por supuesto entre las ciudades que tengan línea directa entre ellas). Además coincide
que los taxis de toda España se encuentran en estos momentos en huelga general, lo que
implica que sólo se podrá cambiar de transporte en una ciudad determinada en la que,
por casualidad, las estaciones de tren y autobús están unidas.
Implementa una función que calcule la tarifa mínima (matriz de costes mínimos) de
viajar entre cualesquiera de las n ciudades disponiendo del grafo de costes en autobús,
del grafo de costes en tren, y de la ciudad que tiene las estaciones unidas.
*/
template<typename tCoste>
matriz<tCoste> viajes(GrafoP<tCoste>& autobus, GrafoP<tCoste>& tren, typename GrafoP<tCoste>::vertice ciudad)
{
    tCoste tarifa_taxi=0;
    GrafoP<tCoste> viajes=SuperGrafo(autobus, tren);
    viajes[ciudad][ciudad+autobus.numVert()]=tarifa_taxi;
    viajes[ciudad+autobus.numVert()][ciudad]=tarifa_taxi;

    matriz<typename GrafoP<tCoste>::vertice> caminos;
    matriz<tCoste> costes=Floyd(viajes, caminos);

    return costes;
}
/* 7.-
Se dispone de dos grafos (matriz de costes) que representan los costes de viajar entre
n ciudades españolas utilizando el tren (primer grafo) y el autobús (segundo grafo).
Ambos grafos representan viajes entre las mismas n ciudades.
Nuestro objetivo es hallar el camino de coste mínimo para viajar entre dos ciudades
concretas del grafo, origen y destino, en las siguientes condiciones:
• La ciudad origen sólo dispone de transporte por tren.
• La ciudad destino sólo dispone de transporte por autobús.
• El sector del taxi, bastante conflictivo en nuestros problemas, sigue en huelga,
por lo que únicamente es posible cambiar de transporte en dos ciudades del
grafo, cambio1 y cambio2, donde las estaciones de tren y autobús están
unidas.
Implementa una función que calcule la ruta y el coste mínimo para viajar entre las
ciudades origen y destino en estas condiciones.
*/
template<typename tCoste>
void viajes(GrafoP<tCoste>& tren, GrafoP<tCoste>& autobus, typename GrafoP<tCoste>::vertice cambio1,
typename GrafoP<tCoste>::vertice cambio2, typename GrafoP<tCoste>::vertice origen, typename GrafoP<tCoste>::vertice destino)
{
    GrafoP<tCoste> SG(tren.numVert()+autobus.numVert());
    SG=supergrafo(tren, autobus);

    SG[cambio1][cambio1+tren.numVert()]=0;
    SG[cambio1+tren.numVert()][cambio1]=0;
    SG[cambio2][cambio2+tren.numVert()]=0;
    SG[cambio2+tren.numVert()][cambio2]=0;

    matriz<typename GrafoP<tCoste>::vertice> caminos;
    matriz<tCoste> costes=Floyd(SG, caminos);
    return costes[origen][destino];
}

/* 8.-
“UN SOLO TRANSBORDO, POR FAVOR”. Este es el título que reza en tu
flamante compañía de viajes. Tu publicidad explica, por supuesto, que ofreces viajes
combinados de tren y/o autobús (es decir, viajes en tren, en autobús, o usando ambos),
entre n ciudades del país, que ofreces un servicio inmejorable, precios muy
competitivos, y que garantizas ante notario algo que no ofrece ninguno de tus
competidores: Que en todos tus viajes como máximo se hará un solo transbordo
(cambio de medio de transporte).
Bien, hoy es 1 de Julio y comienza la temporada alta de viajes.
¡Qué suerte!. Acaba de aparecer un cliente en tu oficina. Te explica que quiere viajar
entre dos ciudades, origen y destino, y quiere saber cuánto le costará.
Para responder a esa pregunta dispones de dos grafos de costes directos (matriz de
costes) de viajar entre las n ciudades del país, un grafo con los costes de viajar en tren y
otro en autobús.
Implementa una función que calcule la tarifa mínima en estas condiciones.
Mucha suerte en el negocio, que la competencia es dura.
*/
template <typename tCoste>
tCoste un_solo_transbordo (GrafoP<tCoste> tren, GrafoP<tCoste> bus, typename GrafoP<tCoste>::vertice origen, typename GrafoP<tCoste>::vertice destino){
	vector<typename GrafoP<tCoste>::vertice> v1, v2, v3, v4;
	//Para el coste del trayecto solo en tren.
	vector<tCoste> soloTren = Dijkstra(tren, origen, v1);
	//Para el coste del trayecto solo en bus.
	vector<tCoste> soloBus = Dijkstra(bus, origen, v2);
	//Para el coste del trayecto saliendo en bus y llegando en tren.
	vector<tCoste> llegadaTren = DijkstraInverso(tren, destino, v3);
	//Para el coste del trayecto saliendo en bus y llegando en tren.
	vector<tCoste> llegadaBus = DijkstraInverso(bus, destino, v4);
	//Creamos una variable tipo tCoste para almacenar el valor del viaje más barato (Único o combinado
	//con un solo transbordo).
	tCoste costeMinimo = GrafoP<tCoste>::INFINITO;
	//Primero buscamos el viaje único más barato.
	if(soloTren[destino] < soloBus[destino])
		costeMinimo = soloTren[destino];
	else
		costeMinimo = soloBus[destino];
	//Miramos si existe un viaje más barato combinando tren-bus o bus-tren (Con un único transbordo).
	for(typename GrafoP<tCoste>::vertice i = 0 ; i < soloTren.size() ; i++){
		//Debemos de tener en cuenta los INFINITOS para no sumarlos y evitar desbordamientos.
		if(soloTren[i] + llegadaBus[i] < costeMinimo and soloTren[i] != GrafoP<tCoste>::INFINITO
		  											 and llegadaBus[i] != GrafoP<tCoste>::INFINITO)
			costeMinimo = soloTren[i] + llegadaBus[i];

		if(soloBus[i] + llegadaTren[i] < costeMinimo and soloBus[i] != GrafoP<tCoste>::INFINITO
		   											and llegadaTren[i] != GrafoP<tCoste>::INFINITO)
			costeMinimo = soloBus[i] + llegadaTren[i];
	}
	return costeMinimo;
}
/* 9.-
Se dispone de dos grafos que representan la matriz de costes para viajes en un
determinado país, pero por diferentes medios de transporte (tren y autobús, por
ejemplo). Por supuesto ambos grafos tendrán el mismo número de nodos, n. Dados
ambos grafos, una ciudad de origen, una ciudad de destino y el coste del taxi para
cambiar de una estación a otra dentro de cualquier ciudad (se supone constante e igual
para todas las ciudades), implementa un subprograma que calcule el camino y el coste
mínimo para ir de la ciudad origen a la ciudad destino.
*/
template<typename tCoste>
tCoste TrenBus(const GrafoP<tCoste>& tren, const GrafoP<tCoste>& bus, tCoste taxi, typename GrafoP<tCoste>::vertice origen,
    typename GrafoP<tCoste>::vertice destino, std::vector<typename GrafoP<tCoste>::vertice>& camino)
{
    size_t n=tren.numVert();
    //Creamos el supergrafo con los costes de bus y tren
    GrafoP<tCoste> G(n+n);
    G=SuperGrafo(tren, bus, taxi);
    //Aplicamos dijkstra para conocer el coste minimo desde origen a destino
   std::vector<tCoste> costes;
   costes=Dijkstra(G, origen, camino);
   return costes[destino];
}
/* 10.-
Se dispone de tres grafos que representan la matriz de costes para viajes en un
determinado país, pero por diferentes medios de transporte (tren, autobús y avión). Por
supuesto los tres grafos tendrán el mismo número de nodos, n.
Dados los siguientes datos:
• los tres grafos,
• una ciudad de origen,
• una ciudad de destino,
• el coste del taxi para cambiar, dentro de una ciudad, de la estación de tren a la
de autobús o viceversa (taxi-tren-bus) y
• el coste del taxi desde el aeropuerto a la estación de tren o a la de autobús, o
viceversa (taxi-aeropuerto-tren/bus)
y asumiendo que ambos costes de taxi son constantes e iguales para todas las ciudades,
implementa una función que calcule el camino y el coste mínimo para ir de la ciudad
origen a la ciudad destino.
*/
template<typename tCoste>
tCoste viajes(GrafoP<tCoste>& tren, GrafoP<tCoste>& bus, GrafoP<tCoste>& avion, typename GrafoP<tCoste>::vertice origen,
typename GrafoP<tCoste>::vertice destino)
{
    size_t n=tren.numVert();
    GrafoP<tCoste> SG(n*3);
    SG=SuperGrafo(tren, bus, avion);
    tCoste costeMin=GrafoP<tCoste>::INFINITO;
    std::vector<typename GrafoP<tCoste>::vertice> caminos1, caminos2, caminos3;
    std::vector<tCoste> costes1=Dijkstra(SG, origen, caminos1);
    std::vector<tCoste> costes2=Dijkstra(SG, origen+n, caminos2);
    std::vector<tCoste> costes3=Dijkstra(SG, origen+n*2, caminos3);

    if(costes1[destino]<costeMin)
        costeMin=costes1[destino];
    if(costes1[destino+n]<costeMin)
        costeMin=costes1[destino+n];
    if(costes1[destino+n*2]<costeMin)
        costeMin=costes1[destino+n*2];

    if(costes2[destino]<costeMin)
        costeMin=costes2[destino];
    if(costes2[destino+n]<costeMin)
        costeMin=costes2[destino+n];
    if(costes2[destino+n*2]<costeMin)
        costeMin=costes2[destino+n*2];

    if(costes3[destino]<costeMin)
        costeMin=costes3[destino];
    if(costes3[destino+n]<costeMin)
        costeMin=costes3[destino+n];
    if(costes3[destino+n*2]<costeMin)
        costeMin=costes3[destino+n*2];

    return costeMin;
}

/* 11.-
Disponemos de tres grafos (matriz de costes) que representan los costes directos de
viajar entre las ciudades de tres de las islas del archipiélago de las Huríes (Zuelandia).
Para poder viajar de una isla a otra se dispone de una serie de puentes que conectan
ciudades de las diferentes islas a un precio francamente asequible (por decisión del
Prefecto de las Huríes, el uso de los puentes es absolutamente gratuito).
Si el alumno desea simplificar el problema, puede numerar las N1 ciudades de la isla
1, del 0 al N1-1, las N2 ciudades de la isla 2, del N1 al N1+N2-1, y las N3 de la última, del
N1+ N2 al N1+N2+ N3-1.
Disponiendo de las tres matrices de costes directos de viajar dentro de cada una de
las islas, y la lista de puentes entre ciudades de las mismas, calculad los costes mínimos
de viajar entre cualesquiera dos ciudades de estas tres islas.
¡¡¡QUE DISFRUTÉIS DEL VIAJE!!!
*/


/* 12.-
El archipiélago de Grecoland (Zuelandia) está formado únicamente por dos islas,
Fobos y Deimos, que tienen N1 y N2 ciudades, respectivamente, de las cuales C1 y C2
ciudades son costeras. Se desea construir un puente que una ambas islas. Nuestro
problema es elegir el puente a construir entre todos los posibles, sabiendo que el coste
de construcción del puente se considera irrelevante. Por tanto, escogeremos aquel
puente que minimice el coste global de viajar entre todas las ciudades de las dos islas,
teniendo en cuenta las siguientes premisas:
1. Se asume que el coste viajar entre las dos ciudades unidas por el puente es 0.
2. Para poder plantearse las mejoras en el transporte que implica la construcción de
un puente frente a cualquier otro, se asume que se realizarán exactamente el
mismo número de viajes entre cualesquiera ciudades del archipiélago. Por
ejemplo, se considerará que el número de viajes entre la ciudad P de Fobos y la
Q de Deimos será el mismo que entre las ciudades R y S de la misma isla. Dicho
de otra forma, todos los posibles trayectos a realizar dentro del archipiélago son
igual de importantes.

Dadas las matrices de costes directos de Fobos y Deimos y las listas de ciudades
costeras de ambas islas, implementad una función que calcule las dos ciudades que
unirá el puente.

Tenemos:
2 islas Fobos (N1, C1) y Deimos (N2, C2)
Colocar un puente entre dos ciudades costeras que minimice el coste de viajar entre dos ciudades cualesquiera
El coste de usar el puente es 0
*/
template<typename T>
bool pertenece(T elem, std::vector<typename GrafoP<T>::vertice> v)
{
    return(std::find(v.begin(), v.end(), elem) != v.end());
}

template <typename tCoste>
void Grecoland(const GrafoP<tCoste>& F, const GrafoP<tCoste>& D, std::vector<typename GrafoP<tCoste>::vertice> C1, std::vector<typename GrafoP<tCoste>::vertice> C2, matriz<tCoste>& M) {
	//Creamos un supergrafo para todas las ciudades
	int n = F.numVert()+D.numVert();
	GrafoP<tCoste> G(n);

	//inicializamos el grafo a infinito
	for (int i=0; i<n; i++)
		for (int j=0; j<n; j++)
			G[i][j] = GrafoP<tCoste>::INFINITO;

    //Guardamos las ciudades de Fobos en el cuadrante 1 del supergrafo
	for (int i=0; i<F.numVert(); i++)
		for (int j=0; j<F.numVert(); j++)
			G[i][j] = F[i][j];
    //Guardamos las ciudades de Deimos en el cuadrante 4 del supergrafo
	for (int i=0; i<D.numVert(); i++)
		for (int j=0; j<D.numVert(); j++)
			G[i+F.numVert()][j+F.numVert()] = D[i][j];

    //Variables a usar
	typename GrafoP<tCoste>::vertice c1, c2;
	tCoste min = GrafoP<tCoste>::INFINITO;

    //Recorremos las conexiones entre las ciudades de Fobos y las de Deimos
	for (int i=0; i<F.numVert(); i++) { //Itera sobre las ciudades de Fobos
		for (int j=0; j<D.numVert(); j++) { //Itera sobre las ciudades de Deimos
			GrafoP<tCoste> aux = G;

			// comprobamos si las ciudades entre las que vamos a poner un puente son costeras o no
			if(pertenece(i, C1) && pertenece(j+F.numVert(), C2))
			{
                aux[i][j+F.numVert()] = 0;
                aux[j+F.numVert()][i] = 0;

                matriz<typename GrafoP<tCoste>::vertice> caminos;
                matriz<tCoste> costes = Floyd(aux, caminos);

                tCoste coste = 0;

                //Se suman todos los costes de la matriz de Floyd
                for (int x=0; x<n; x++)
                    for (int y=0; y<n; y++)
                        if (costes[x][y]!=GrafoP<tCoste>::INFINITO)
                            coste+=costes[x][y];
                //Nos quedamos con el coste si es minimo y con las ciudades que une el puente
                if (coste<min) {
                    min = coste;
                    c1 = i;
                    c2 = j+F.numVert();
                }
            }
        }
    }
    //Al salir del bucle tenemos las ciudades que une el puente y que hacen el coste minimo
    G[c1][c2] = 0;
    G[c2][c1] = 0;

    std::cout << G << std::endl;

    matriz<typename GrafoP<tCoste>::vertice> caminos;
    matriz<tCoste> costes = Floyd(G, caminos);
    M = costes;

    std::cout << "El puente se pone entre las ciudades " << c1 << " y " << c2 << std::endl;
}
/* 13.-
El archipiélago de las Huríes acaba de ser devastado por un maremoto de
dimensiones desconocidas hasta la fecha. La primera consecuencia ha sido que todos y
cada uno de los puentes que unían las diferentes ciudades de las tres islas han sido
destruidos. En misión de urgencia las Naciones Unidas han decidido construir el
mínimo número de puentes que permitan unir las tres islas. Asumiendo que el coste de
construcción de los puentes implicados los pagará la ONU, por lo que se considera
irrelevante, nuestro problema es decidir qué puentes deben construirse. Las tres islas de
las Huríes tienen respectivamente N1, N2 y N3 ciudades, de las cuales C1, C2 y C3 son
costeras. Nuestro problema es elegir los puentes a construir entre todos los posibles. Por
tanto, escogeremos aquellos puentes que minimicen el coste global de viajar entre todas
las ciudades de las tres islas, teniendo en cuenta las siguientes premisas:
1. Se asume que el coste viajar entre las ciudades que unan los puentes es 0.
2. La ONU subvencionará únicamente el número mínimo de puentes necesario
para comunicar las tres islas.
3. Para poder plantearse las mejoras en el transporte que implica la construcción de
un puente frente a cualquier otro, se asume que se realizarán exactamente el
mismo número de viajes entre cualesquiera ciudades del archipiélago. Dicho de
otra forma, todos los posibles trayectos a realizar dentro del archipiélago son
igual de importantes.
Dadas las matrices de costes directos de las tres islas y las listas de ciudades
costeras del archipiélago, implementad una función que calcule los puentes a construir
en las condiciones anteriormente descritas.
*/
template<typename tCoste>
void Huries(GrafoP<tCoste>& Isla1, GrafoP<tCoste>& Isla2, GrafoP<tCoste>& Isla3, std::vector<bool> C1,
 std::vector<bool> C2, std::vector<bool> C3 )
 {
        //Crear un supergrafo con los 3 grafos
        GrafoP<tCoste> Archipielago(Isla1.numVert()+Isla2.numVert()+Isla3.numVert());

        //Recorrer todas las posibles parejas de ciudades costeras entre C1, C2 y C3 y colocar puentes (2)
        //Quedarnos siempre con el puente que minimice el coste total
        for(size_t i=0;i<Isla1.numVert();++i)
        {
            for(size_t j=0;j<Isla2.numVert();++j)
            {
                //Colocamos un puente entre i y j
                Archipielago[i][j+Isla1.numVert()]=0;
                Archipielago[j+Isla1.numVert()][i]=0;
                Archipielago[i][i+Isla1.numVert()+Isla2.numVert()]=0;
                Archipielago[i+Isla1.numVert()+Isla2.numVert()][i]=0;


            }
        }

 }
#endif

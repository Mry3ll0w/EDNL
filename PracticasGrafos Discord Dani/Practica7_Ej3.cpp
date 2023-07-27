/*
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
std::vector<double> subvenciones)
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
        //costesFinales[i]=costes[i]-(costes[i]*subvenciones[i]/100);

    //Ahora hay que hacer el reparto de todo el stock
    std::vector<bool> almacenes_llenos( costesFinales.size(),false);
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
            stock=stock-capacidad[destino];
        else
            stock=0;
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
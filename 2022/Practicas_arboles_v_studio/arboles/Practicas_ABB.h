#include "abb.h"
#include <ostream>
#include <vector>
#include <list>

//Impresion del arbol
template<class t>
void imprime_arbol (const Abb<t>& a) {
	if (!a.vacio())
	{
		std::cout << a.elemento() << ", ";

		imprime_arbol(a.izqdo());
		imprime_arbol(a.drcho());

	}
	
}


//EJERCICIO 1


template<class t>
void podar_abb(const t& buscado, Abb<t>&A) {

	//Si esta vacio no hacemos nada, ya que o no lo encuentras o esta vacio
	Abb<t> arbol_temp = A.buscar(buscado);
	if (!arbol_temp.vacio())
	{

		A.buscar(buscado).~Abb();

	}

}

/*
Un árbol binario de búsqueda se puede equilibrar realizando el recorrido en inorden
del árbol para obtener el listado ordenado de sus elementos y a continuación, repartir
equitativamente los elementos a izquierda y derecha colocando la mediana en la raíz y
construyendo recursivamente los subárboles izquierdo y derecho de cada nodo.
Implementa este algoritmo para equilibrar un ABB.
*/

//Obtiene la lista de elementos de un arbol binario
template<class t>
std::list<t> elementos_abb(Abb<t> A,std::list<t>& l) {

	if (!A.vacio())
	{
		elementos_abb(A.izqdo(), l);
		l.push_back(A.elemento());
		elementos_abb(A.drcho(), l);
	}

	return l;
}

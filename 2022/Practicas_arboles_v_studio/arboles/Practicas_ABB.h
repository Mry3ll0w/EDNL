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
void elementos_abb(Abb<t> A,std::vector<t>& v) {

	if (!A.vacio())
	{
		elementos_abb(A.izqdo(), v);
		v.push_back(A.elemento());
		elementos_abb(A.drcho(), v);
	}

}


/*
Dados dos conjuntos representados mediante árboles binarios de búsqueda,
implementa la operación unión de dos conjuntos que devuelva como resultado otro
conjunto que sea la unión de ambos, representado por un ABB equilibrado.
	NO SE HACER EL EQUILIBRIO
*/
template<class t>
void conjunto_rec(const Abb<t>& A,const Abb<t>& B, Abb<t>&R) {

	if (!A.vacio()) {
		R.insertar(A.elemento());
		conjunto_rec(A.izqdo(), B, R);
		conjunto_rec(A.drcho(), B, R);
	}

	if (!B.vacio())
	{
		R.insertar(B.elemento());
		conjunto_rec(A, B.izqdo(), R);
		conjunto_rec(A, B.drcho(), R);
	}

}

template<class t>
Abb<t> union_arboles(Abb<t>& A, Abb<t>& B) {
	Abb<t>R;
	conjunto_rec(A, B, R);
	return R;
}

/*
Implementa el operador rombo para conjuntos definido como A  B = (A  B) - (A  B).
La implementación del operador  debe realizarse utilizando obligatoriamente la
operación pertenece, que nos indica si un elemento dado pertenece o no a un conjunto. La
representación del tipo Conjunto debe ser tal que la operación de pertenencia esté en el
caso promedio en O(log n).
*/
template <class t>
std::vector<t> iguales(const Abb<t>&A, const Abb<t>&B) {

	std::vector<t>va, vb,res;
	elementos_abb(A,va);
	elementos_abb(B,vb);

	//Insertamos los elementos coincidentes
	for (auto i : va) {
		for (auto j : vb) {
			if (i == j)
			{
				res.push_back(i);
			}
		}
	}

	return res;
}

template <class t>
const Abb<t> interseccion(const Abb<t>&A, const Abb<t>&B) {
	Abb<t> inter;

	//Insertamos los elementos coincidentes (la el 
	for (auto i : iguales(A, B))
		inter.insertar(i);
	
	return inter;

}

template<class t> 
Abb<t> operator - (const Abb<t>& A, const Abb<t>& B) {
	
	Abb<t> res;
	std::vector<t> va, vb;
	elementos_abb(A, va); elementos_abb(B, vb);

	

	//metemos los elementos no coincidentes
	for(auto i : va)
	{
		for (auto j : vb) {
			if (i != j)
			{
				res.insertar(i);
			}
		}
	}

	return res;
}

template <class t> 
Abb<t> rombo(Abb<t> &A, Abb<t>&B){

	return union_arboles(A, B) - interseccion(A, B);

}
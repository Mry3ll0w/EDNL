#include<iostream>
#include "Agen.h"

//Ejercicio 1:
/*
Implementa un subprograma que dado un árbol general nos calcule su grado.
Grado de un arbol es el maximo numero de hijos
*/
template <class t>
int hermanos_nodo(const Agen<t>&A, typename Agen<t>::nodo n) {

	if (n == Agen<t>::NODO_NULO)
	{
		return 0;
	}

	return 1 + hermanos_nodo(A,A.hermDrcho(n));
}

template<class t>
int grado_max_rec(const Agen<t>&A, typename Agen<t>::nodo n,int grado) {


	if (n == Agen<t>::NODO_NULO)
	{
		return grado;
	}

	int grado_actual = hermanos_nodo(A,n);

	if (grado < grado_actual) {
		grado = grado_actual;
	}

	grado_max_rec(A,A.hijoIzqdo(n),grado);
}

//Ejercicio 2
/*
Implementa un subprograma que dados un árbol y un nodo dentro de dicho árbol determine
la profundidad de éste nodo en el árbol.
*/

template <class t>
int profundidad_nodo(Agen<t> A, typename Agen<t>::nodo n) {

	if (n == Agen<t>::NODO_NULO)
	{
		return -1;
	}

	return 1 + profundidad_nodo(A, A.padre(n));
}

//Ejercicio 3
/*
Se define el desequilibrio de un árbol general como la máxima diferencia entre las alturas
de los subárboles más bajo y más alto de cada nivel. Implementa un subprograma que calcule
el grado de desequilibrio de un árbol general:
	
	a) obtener altura del mas pequeno del nivel
	b) obtener altura del mas altura del nivel
	desequilibrio = abs(a - b)
*/

template <class t>
int altura_nodo(Agen<t> A, typename Agen<t>::nodo n) {

	if (n == Agen<t>::NODO_NULO)
	{
		return -1;
	}
	return 1 + altura_nodo(A, A.hijoIzqdo(n));
}

template <class t>
void min_max_nivel(Agen<t> A, typename Agen<t>::nodo n, int& min, int& max) {

	if (n != Agen<t>::NODO_NULO)
	{
		
		int altura_act = altura_nodo(A, n);

		if (min > altura_act) 
		{
			min = altura_act;
		}

		if (max < altura_act)
		{
			max = altura_act;
		}
	
		min_max_nivel(A,A.hermDrcho(n),min,max);
	}

}

template<class t>
void desequilibrio_agen_rec(Agen<t> A, typename Agen<t>::nodo n, int& des,int min_n,int max_n) 
{
	if (n != Agen<t>::NODO_NULO)
	{

		min_max_nivel(A, n, min_n, max_n);
		
		if (des < std::abs(std::abs(min_n) - std::abs(max_n)))
		{
			des = std::abs(std::abs(min_n) - std::abs(max_n));
		}

		desequilibrio_agen_rec(A, A.hijoIzqdo(n), des, min_n, max_n);
	}

}

template <class t>
int desequilibrio_agen(Agen<t> A) 
{
	int m = 0, mx = 0, d = -1;
	desequilibrio_agen_rec(A, A.raiz(), d, -1, 0);

	return d;
}

//Ejercicio 4:
/*
Dado un árbol general de enteros A y un entero x, implementa un subprograma que realice
la poda de A a partir de x. Se asume que no hay elementos repetidos en A.
*/
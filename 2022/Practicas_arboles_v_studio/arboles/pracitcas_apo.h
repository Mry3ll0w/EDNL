#include "Agen.h"
#include "abin_enla.h"
#include <iostream>

//Ejercicio 4: Comprobar si un arbol es ternario: todos sus nodos tienen 3 hijos o son hojas

template<class t>
bool es_hoja(Agen<t>&A ,typename Agen<t>::nodo n) {
	
	bool token = false;
	
	//Si es nodo nulo entonces cumple la condicion
	if (n == Agen<t>::NODO_NULO)
	{
		token = true;
	}
	else
	{//No es nodo nulo pero sus hijos son hojas
		if (A.hijoIzqdo(n) == Agen<t>::NODO_NULO)
		{
			token = true;//Si el hijo izquierdo es nulo entonces simplemente no hay hijos, es hoja
		}
		
	}

	return token;
}

template <class t>
bool tiene_3_hijos(Agen<t>&A, typename Agen<t>::nodo n) {
	
	bool token = true;

	if (n != Agen<t>::NODO_NULO) {

		auto itera_hermanos = A.hijoIzqdo(n);
		int n_hijos=0;

		while (itera_hermanos != Agen<t>::NODO_NULO) {

			n_hijos++;
			itera_hermanos = A.hermDrcho(itera_hermanos);

		}

		if (n_hijos != 3)//Si tiene menos o mas hijos
			token = false;

	}

	return token;
}

template<class t> 
bool nodo_ternario(Agen<t>& A, typename Agen<t>::nodo n) {

	return tiene_3_hijos(A, n) || es_hoja(A,n);//Si es hoja o tiene 3 nodos es ternario
	
}

template  <class t>
bool ternario_rec(Agen<t> A, typename Agen<t>::nodo n) {

	if (n == Agen<t>::NODO_NULO)
	{
		return true;
	}
	else //Caso general 
	{
		return nodo_ternario(A, A.hijoIzqdo(n)) && nodo_ternario(A, A.hermDrcho(n));
	}

}

//Ejercicio 5


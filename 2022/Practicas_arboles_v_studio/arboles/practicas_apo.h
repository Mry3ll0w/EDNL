#include "Agen.h"
#include "abin_enla.h"
#include <iostream>
#include <vector>

template <class t>
std::ostream& operator << (std::ostream& os, std::vector<std::vector<t>>m) {

	for (auto i : m) {
		for (auto j : i) {
			os << j << " ";
		}
		os << std::endl;
	}
	return os;
}

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

//Ejercicio 5 ==> Se tiene que pasar de arbol a matriz, no a la inversa

struct cuadrante {
	unsigned x_in, x_fin, y_in, y_fin;
};

//Volcado_recursivo desde el arbol a la matriz
//Estoy usando el estilo de programacion de DLH, para evitarme futuros problemas
void volcado_rec(Agen<char>A, std::vector<std::vector<char>>&m, cuadrante c, typename Agen<char>::nodo n) {


	//Comprobamos que el arbol a tratar no este vacio
	if (n!=Agen<char>::NODO_NULO) {

		//Comprobamos el color del cuadrante en el arbol
		if (A.elemento(n) == 'M')//Si es mixto lo procesamos hasta llegar a un no mixto
		{

			//Iniciamos el procesado por cuadrantes
			auto hijos_der = A.hijoIzqdo(n);
			unsigned n_cuad = 1;

			//procesamos hijos derechos
			while (hijos_der != Agen<char>::NODO_NULO) {

				//Tratamos cada cuadrante en funcion al que estemos
				switch (n_cuad)
				{
				case 1:
					c.x_fin /= 2; 
					c.y_fin /= 2;
					break;

				case 2:

					c.x_in = c.x_fin + 1;
					c.x_fin = 2 * c.x_fin + 1;

					break;

				case 3:
					c.y_in = c.y_fin + 1;
					c.y_fin = 2 * c.y_fin + 1;

					break;

				case 4:
					
					c.x_in = 0;
					c.x_fin /= 2;

					break;

				default:
					break;
				}

				volcado_rec(A,m,c,A.hijoIzqdo(n));
				n_cuad++;//Cambiamos de cuadrante tras procesarlo
				hijos_der = A.hermDrcho(hijos_der);
			}


		}
		else { //En caso de que el nodo no sea mixto, simplemente lo metemos en la matriz

			for (unsigned i = c.x_in; i < c.x_fin; i++) {
				for (unsigned j = c.y_in; j < c.y_fin; j++) {
					m[i][j] = A.elemento(n);
				}
			}
			
		}

	}

}


//Los colores permitidos son Blanco, N egro y M(mixto), si aparece # es pq esta vacio 
std::vector<std::vector<char>> volcado(Agen<char>A) {
	
	//Creamos el vector de salida
	std::vector<std::vector<char>> m(8,std::vector<char>(8,'#'));

	//Inicializo el cuadrante
	cuadrante c;
	c.y_in = c.x_in = 0;
	c.x_fin = c.y_fin = 7;//la matriz es de 8*8 (n-1 =7)

	volcado_rec(A,m,c,A.raiz());

	return m;
}


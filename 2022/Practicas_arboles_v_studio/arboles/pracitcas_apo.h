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

//Ejercicio 5 ==> Pasar de matriz a arbol general, se asume que la matriz es correcta

//Calcula cuantos saltos puedes hacer
template<class t>
int n_saltos(std::vector<std::vector<t>> V) {

	int n = 0;
	for (int i = 0; i < V.size(); ++i) {
		//std::cout << V[i].size() << ", ";
		if ((V[i].size() % 2)==0)
		{
			++n;
		}
	}
	
	return n/2;//Ya que solo se saltan 2 veces
}

//Cuenta los cuadrantes (2*2) que tiene la matriz
template <class t>
int n_cuadrantes(std::vector<std::vector<t>> V) 
{
	
	return n_saltos(V) * (V[0].size()/2);

}


//Procesa el cuadrante y obtiene su color
//Devuelve el nodo donde se ha insertado el color1
template <class t>
typename Agen<t>::nodo color_cuadrante(std::vector<std::vector<t>> V, int f_inicio, int c_inicio,Agen<t>A, typename Agen<t>::nodo n) 
{
	Agen<t>::nodo nodo;
	//Color blanco
	if 
	(
		V[f_inicio][c_inicio] == V[f_inicio][c_inicio+1] 
		==
		V[f_inicio+1][c_inicio] == V[f_inicio+1][c_inicio+1] == 'B'
	)
	{
		A.insertarHermDrcho(n,'B');
		nodo = A.hermDrcho(n);
	}
	else 
	if 
		(
			V[f_inicio][c_inicio] == V[f_inicio][c_inicio + 1]
			==
			V[f_inicio + 1][c_inicio] == V[f_inicio + 1][c_inicio + 1] == 'N'
		)//Color negro 
	{
		A.insertarHijoIzqdo(n, 'N');
		nodo = A.hermDrcho(n);
	}
	else //MIXTO
	{
		A.insertarHijoIzqdo(n, 'M');
		auto iz = A.hijoIzqdo(n);
		
		//Insertamos los nodos sueltos en formato de reloj
		A.insertarHermDrcho(iz, V[f_inicio][c_inicio]);
		A.insertarHermDrcho(iz, V[f_inicio][c_inicio+1]);
		A.insertarHermDrcho(iz, V[f_inicio+1][c_inicio+1]);
		A.insertarHermDrcho(iz, V[f_inicio+1][c_inicio]);

		return iz;
	}

	return A.hijoIzqdo(n);//En casos normales devolvemos el hijo izquierdo donde iremos insertando
}

//Procesa matriz
template <class t>
Agen<t> procesa_matriz(std::vector<std::vector<t>> V)
{
	Agen<t> res;
	int f_in = 0, c_in = 0, cuad_fila=V[0].size()/2, it_cuad=0, c_fila=0;
	
	auto nodo = color_cuadrante(V, f_in, c_in, res, res.raiz());//En primera instancia metemos el elemento raiz
	

	while (it_cuad < n_cuadrantes(V)) {//ya que empieza en 1

		nodo = color_cuadrante(V,f_in,c_in,res,nodo);//Coloreamos e insertamos los nodos
		

		if (c_fila >= cuad_fila) {
			c_fila = 0;
			f_in += 2;//cambiamos de fila
			c_in = 0;//Cada vez que saltamos la columna vale 0
		}

		it_cuad++;
		c_fila++;
		c_in++;
	}

	return res;//devolvemos el arbol relleno
}



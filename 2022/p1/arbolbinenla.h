#ifndef ABIN_H
#define ABIN_H
#include <cassert>
#include <cmath>
/// THIS IS NOT MY OWN CODE, WAS IMPLEMENTED BY
template <typename T> 
class Abin {
	struct celda;   // declaración adelantada privada, celda se usa en parte publica y se implementa abajo
public:
	typedef celda* nodo;
	static const nodo NODO_NULO;
	Abin(); // constructor
	void insertarRaizB(const T& e);
	void insertarHijoIzqdoB(nodo n, const T& e);
	void insertarHijoDrchoB(nodo n, const T& e);
	void eliminarHijoIzqdoB(nodo n);
	void eliminarHijoDrchoB(nodo n);
	void eliminarRaizB();
	~Abin(); // destructor
	bool arbolVacioB() const;
	const T& elemento(nodo n) const; // acceso a elto, lectura
	T& elemento(nodo n);  // acceso a elto, lectura/escritura
	nodo raizB() const;
	nodo padreB(nodo n) const;
	nodo hijoIzqdoB(nodo n) const;
	nodo hijoDrchoB(nodo n) const;
    int altura_mia(nodo n)const;//ta bien
	int profundidad_nodo(nodo n)const;//handmade
	int profundidad_arbol(Abin<T>)const;
	unsigned node_counter()const;
	int desequilibrio(nodo n, int max)const;
	int altura(nodo n);
	Abin(const Abin<T>& a);  // ctor. de copia
	Abin<T>& operator =(const Abin<T>& a); //asignación de árboles

private:
	struct celda {
		T elto;
		nodo padre, hizq, hder;
		celda(const T& e, nodo p = NODO_NULO): elto(e),
		padre(p), hizq(NODO_NULO), hder(NODO_NULO) {}
	};
	nodo r; // nodo raíz del árbol
	void destruirNodos(nodo& n);
	nodo copiar(nodo n);
    unsigned node_counter_final(nodo n)const;
};

/* Definición del nodo nulo */
template <typename T>
const typename Abin<T>::nodo Abin<T>::NODO_NULO(0);


template <typename T>
int Abin<T>::altura(typename Abin<T>::nodo n)//Mejor implementacion
{
	if(n==NODO_NULO){
		return -1;
	}
	else{
		return fmax(1+altura(n->hizq),1+altura(n->hder));
	}
}

template <typename T>
inline Abin<T>::Abin() : r(NODO_NULO) {}

template <typename T>
inline void Abin<T>::insertarRaizB (const T& e)
{
	assert(r == NODO_NULO);  // árbol vacío
	r = new celda(e);
}

template <typename T>
inline void Abin<T>::insertarHijoIzqdoB(Abin<T>::nodo n,const T& e){
	assert(n != NODO_NULO);
	assert(n->hizq == NODO_NULO);  // no existe hijo

	n->hizq = new celda(e, n);
}

template <typename T> inline
void Abin<T>::insertarHijoDrchoB(Abin<T>::nodo n, const T& e){
	assert(n != NODO_NULO);
	assert(n->hder == NODO_NULO); // no existe hijo
	n->hder = new celda(e, n);
}

template <typename T>
inline void Abin<T>::eliminarHijoIzqdoB(Abin<T>::nodo n){
	assert(n != NODO_NULO);
	assert(n->hizq != NODO_NULO); // existe hijo izqdo.
	assert(n->hizq->hizq == NODO_NULO && // hijo izqdo. 
		   n->hizq->hder == NODO_NULO);  // es hoja
	
	delete(n->hizq);
	n->hizq = NODO_NULO;
}

template <typename T>
inline void Abin<T>::eliminarHijoDrchoB(Abin<T>::nodo n){
	assert(n != NODO_NULO);
	assert(n->hder != NODO_NULO); // existe hijo drcho.
	assert(n->hder->hizq == NODO_NULO && // hijo drcho.
		   n->hder->hder == NODO_NULO);  // es hoja
	
	delete(n->hder);
	n->hder = NODO_NULO;
}

template <typename T>
inline void Abin<T>::eliminarRaizB(){
	assert(r != NODO_NULO); // árbol no vacío
	assert(r->hizq == NODO_NULO &&
		   r->hder == NODO_NULO); // la raíz es hoja
	
	delete(r);
	r = NODO_NULO;
}

template <typename T> 
inline Abin<T>::~Abin(){destruirNodos(r);}

template <typename T> inline bool Abin<T>::arbolVacioB() const{ return (r == NODO_NULO); }

template <typename T>
inline const T& Abin<T>::elemento(Abin<T>::nodo n) const{
	assert(n != NODO_NULO);
	return n->elto;
}

template <typename T>
inline T& Abin<T>::elemento(Abin<T>::nodo n){
	assert(n != NODO_NULO);
	return n->elto;
}

template <typename T>
inline typename Abin<T>::nodo Abin<T>::raizB() const{
	return r;
}

template <typename T> inline
typename Abin<T>::nodo Abin<T>::padreB(Abin<T>::nodo n) const{
	assert(n != NODO_NULO);
	return n->padre;
}

template <typename T> inline
typename Abin<T>::nodo Abin<T>::hijoIzqdoB(Abin<T>::nodo n) const{
	assert(n != NODO_NULO);
	return n->hizq;
}

template <typename T> inline
typename Abin<T>::nodo Abin<T>::hijoDrchoB(Abin<T>::nodo n) const{
	assert(n != NODO_NULO);
	return n->hder;
}

template <typename T>
inline Abin<T>::Abin(const Abin<T>& a)
{
	r = copiar(a.r);
}

template <typename T>
Abin<T>& Abin<T>::operator =(const Abin<T>& a){
	if (this != &a) // evitar autoasignación
	{
		this->~Abin();// vaciar el árbol
		r = copiar(a.r);
	}
	return *this;
}

// Métodos privados
// Destruye un nodo y todos sus descendientes
template <typename T>
void Abin<T>::destruirNodos(Abin<T>::nodo& n){
	if (n != NODO_NULO)
	{
		destruirNodos(n->hizq);
		destruirNodos(n->hder);
		delete n;
		n = NODO_NULO;
	}
}

// Devuelve una copia de un nodo y todos sus descendientes
template <typename T>
typename Abin<T>::nodo Abin<T>::copiar(Abin<T>::nodo n){

	nodo m = NODO_NULO;
	if (n != NODO_NULO){
		m = new celda(n->elto);  // copiar n
		m->hizq = copiar(n->hizq); // copiar subárbol izqdo.
		if (m->hizq != NODO_NULO) m->hizq->padre = m;
		m->hder = copiar(n->hder); // copiar subárbol drcho.
		if (m->hder != NODO_NULO) m->hder->padre = m;
	}
	return m;
}

template<typename T>
unsigned Abin<T>::node_counter()const {
    return node_counter_final(raizB());
}

template<typename T>
unsigned Abin<T>::node_counter_final(Abin::nodo n)const {//Add el arbol para el resto de codigo
    if(n == NODO_NULO)
        return 0;
    else
        return node_counter_final(n->hder)+node_counter_final(n->hizq)+1 ;
}

template<typename T>
int Abin<T>::profundidad_nodo(Abin::nodo n)const {

    if(n == NODO_NULO)
        return -1;
    else
        return 1+profundidad_nodo(n->padre);
}

template<typename T>
int Abin<T>::altura_mia(nodo n) const {
    if(n == NODO_NULO)
        return -1;
    else
        return fmax(altura_mia(n->hder),altura_mia(n->hizq))+1 ;
}

template<typename T>
int Abin<T>::profundidad_arbol(Abin<T>a) const {
    return a.profundidad_nodo(a.raizB());//Calcula la altura del nodo raiz
}

template<typename T>
int Abin<T>::desequilibrio(nodo n,int max ) const {

    if(n == NODO_NULO)
        return max;
    else
        return max=fmax(abs(altura_mia(n)-altura_mia(n->hder)),abs(altura_mia(n)-altura_mia(n->hder)));

}

#endif
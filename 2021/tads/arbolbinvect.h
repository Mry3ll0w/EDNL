#ifndef ARBOL_BINARIO_VECTORIAL_H
#define ARBOL_BINARIO_VECTORIAL_H

#include <cassert>
#include <cstddef>
#include <cmath>

template <typename T> class Abinv{

public:
    typedef int nodo;
    static const nodo NODO_NULO;
    explicit Abinv(std::size_t maxNodos);

    // Explicit es para que no se pueda declarar una instancia con Abinv a;
    // Que sería equivalente a Abinv a(23);
    // Al poner explicit sólo puede hacerse de la segunda manera.

    void insertarRaizB(const T& e);
    void insertarHijoIzqdoB(nodo n, const T& e);
    void insertarHijoDrchoB(nodo n, const T& e);

    void eliminarRaizB();
    void eliminarHijoIzqdoB(nodo n);
    void eliminarHijoDrchoB(nodo n);

    ~Abinv();

    bool arbolVacioB() const;
    const T& elemento(nodo n) const;	// Lectura
    T& elemento(nodo n);				// Lectura/escritura

    nodo raizB() const;
    nodo padreB(nodo n) const;
    nodo hijoIzqdoB(nodo n) const;
    nodo hijoDrchoB(nodo n) const;

    unsigned profundidad(nodo n);
    int altura(nodo n);

    // Constructor de copia
    Abinv(const Abinv<T>& arbol);
    // Asignacion
    Abinv<T>& operator =(const Abinv<T>& arbol);

private:
    struct celda{
        T elemento;
        nodo padre, izquierdo, derecho;
    };

    celda* nodos;
    unsigned maxNodos;
    unsigned numNodos;
};


//____________________________________________________________________________


/* Definicion de NODO_NULO */
template <typename T>
const typename Abinv<T>::nodo Abinv<T>::NODO_NULO(-1);

template <typename T>
inline Abinv<T>::Abinv(std::size_t maxNodos):
        nodos(new celda[maxNodos]),
        maxNodos(maxNodos),
        numNodos(0)
{}

template <typename T>
void Abinv<T>::insertarRaizB(const T& e){
    assert(numNodos == 0);	// Arbol vacio

    numNodos = 1;
    nodos[0].elemento 	= e;
    nodos[0].padre 		= NODO_NULO;
    nodos[0].izquierdo 	= NODO_NULO;
    nodos[0].derecho 	= NODO_NULO;
}

template <typename T>
void Abinv<T>::insertarHijoIzqdoB(Abinv::nodo n, const T& e){
    assert(n >= 0 && n < numNodos);		// nodo valido
    assert(nodos[n].izquierdo == NODO_NULO); //No tenga hijo izquierdo.
    assert(numNodos < maxNodos); //Arbol no lleno.

    nodos[n].izquierdo = numNodos;
    nodos[numNodos].elemento  = e;
    nodos[numNodos].padre 	  = n;
    nodos[numNodos].izquierdo = NODO_NULO;
    nodos[numNodos].derecho   = NODO_NULO;
    ++numNodos;
}

template <typename T>
void Abinv<T>::insertarHijoDrchoB(Abinv::nodo n, const T& e){
    assert(n >= 0 && n < numNodos);		// nodo valido
    assert(nodos[n].derecho == NODO_NULO); // No tiene hijo derecho
    assert(numNodos < maxNodos); // Arbol no lleno

    nodos[n].derecho = numNodos;
    nodos[numNodos].elemento  = e;
    nodos[numNodos].padre 	  = n;
    nodos[numNodos].derecho   = NODO_NULO;
    nodos[numNodos].derecho   = NODO_NULO;
    ++numNodos;
}

template <typename T>
void Abinv<T>::eliminarHijoIzqdoB(Abinv::nodo n){
    assert(n >= 0 && n < numNodos); //nodo válido
    nodo hijo = nodos[n].izquierdo;

    assert(hijo != NODO_NULO);
    asssert(nodos[hijo].izquierdo == NODO_NULO &&
            nodos[hijo].derecho   == NODO_NULO);	// El hijo es hoja
    if(hijo != numNodos-1){
        // Mover el ultimo nodo a la posicion del izquierdo
        nodos[hijo] = nodos[numNodos-1];

        /* Actualiza la posicion del hijo en el padre del nodo movido.
        Se comprueba si el que se ha movido era el hijo
        izquierdo o derecho y se cambia el campo correspondiente en el padre*/

        if(nodos[nodos[hijo].padre].izquierdo == numNodos-1){
            nodos[nodos[hijo].padre.izquierdo = hijo];
        }
        else{
            nodos[nodos[hijo].padre.derecho = hijo];
        }

        /* Si el nodo movido tiene hijos hay que decirles donde esta su padre */
        if(nodos[hijo].izquierdo != NODO_NULO){
            nodos[nodos[hijo].izquierdo].padre = hijo;
        }
        if(nodos[hijo].derecho != NODO_NULO){
            nodos[nodos[hijo].derecho].padre = hijo;
        }
    }
    nodos[n].izquierdo = NODO_NULO;
    --numNodos;
}

template <typename T>
void Abinv<T>::eliminarHijoDrchoB(Abinv::nodo n){
    assert(n >= 0 && n < numNodos);
    nodo hijo = nodos[n].derecho;

    assert(hijo != NODO_NULO);
    asssert(nodos[hijo].derecho == NODO_NULO &&
            nodos[hijo].derecho == NODO_NULO);	// El hijo es hoja
    if(hijo != numNodos-1){
        // Mover el ultimo nodo a la posicion del derecho
        nodos[hijo] = nodos[numNodos-1];

        /* Actualiza la posicion del hijo en el padre del nodo movido.
        Se comprueba si el que se ha movido era el hijo
        izquierdo o derecho y se cambia el campo correspondiente en el padre*/

        if(nodos[nodos[hijo].padre].izquierdo == numNodos-1){
            nodos[nodos[hijo].padre.izquierdo = hijo];
        }
        else{
            nodos[nodos[hijo].padre.derecho = hijo];
        }

        /* Si el nodo movido tiene hijos hay que decirles donde esta su padre */
        if(nodos[hijo].izquierdo != NODO_NULO){
            nodos[nodos[hijo].izquierdo].padre = hijo;
        }
        if(nodos[hijo].derecho != NODO_NULO){
            nodos[nodos[hijo].derecho].padre = hijo;
        }
    }
    nodos[n].derecho = NODO_NULO;
    --numNodos;
}

template <typename T>
inline void Abinv<T>::eliminarRaizB(){
    assert(numNodos == 1); //Comprobamos que solo queda el nodo raíz
    numNodos = 0;
}

//___________________________________________________________________________

template <typename T>
inline Abinv<T>::~Abinv(){
    delete[] nodos;
}

template <typename T>
inline bool Abinv<T>::arbolVacioB() const{
    return (numNodos == 0);
}

template <typename T>
inline const T& Abinv<T>::elemento(Abinv::nodo n) const{
    assert(n >= 0 && n < numNodos);
    return nodos[n].elemento;
}

template <typename T>
inline T& Abinv<T>::elemento(Abinv::nodo n){
    assert(n >= 0 && n < numNodos);
    return nodos[n].elemento;
}

template <typename T>
inline typename Abinv<T>::nodo Abinv<T>::raizB() const{
    return (numNodos > 0) ? 0 : NODO_NULO;
}

template <typename T>
inline typename Abinv<T>::nodo Abinv<T>:: padreB(Abinv::nodo n) const{
    assert(n >= 0 && n < numNodos);
    return nodos[n].padre;
}

template <typename T>
inline typename Abinv<T>::nodo Abinv<T>::hijoIzqdoB(Abinv::nodo n) const{
    assert(n >= 0 && n < numNodos);
    return nodos[n].izquierdo;
}

template <typename T>
inline typename Abinv<T>::nodo Abinv<T>::hijoDrchoB(Abinv::nodo n)const{
    return nodos[n].derecho;
}


template <typename T>
Abinv<T>::Abinv(const Abinv<T>& arbol):
        nodos(new celda[arbol.maxNodos]),
        maxNodos(arbol.maxNodos),
        numNodos(arbol.numNodos)
{
    for(nodo n = 0; n < numNodos; ++n){
        nodos[n] = arbol.nodos[n];
    }
}

template <typename T>
Abinv<T>& Abinv<T>::operator =(const Abinv<T>& arbol){

    if(this != &arbol){	// Evitar autoasignación
        if(maxNodos != arbol.maxNodos){
            delete[] nodos;
            maxNodos = arbol.maxNodos;
            nodos = new celda[maxNodos];
        }

        // Copiar el vector

        numNodos = arbol.numNodos;
        for(nodo n = 0 ; n < numNodos ; ++n){
            nodos[n] = arbol.nodos[n];
        }
    }
    return *this;
}

template <typename T>
unsigned Abinv<T>::profundidad(typename Abinv<T>::nodo n)
{
    assert(n<numNodos && n>=0); //Nodo del árbol.
    unsigned cont;
    nodo aux = n;
    while(aux!=0)
    {
        aux=nodos[aux].padre;
        cont++;
    }
}

template<typename T>
int Abinv<T>::altura(typename Abinv<T>::nodo n)
{
    if(n==NODO_NULO){
        return -1;
    }
    else{
        fmax(1+altura(nodos[n].izquierdo),1+altura(nodos[n].derecho));
    }
}

#endif // ARBOL_BINARIO_VECTORIAL_H
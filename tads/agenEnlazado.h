#ifndef AGEN_H_
#define AGEN_H_

#include <cassert>
#include <iostream>

/*/
 * Definición:
 *	
 * Un árbol general se define como un árbol cuyos nodos son de cualquier grado, es
 * decir, pueden tener un número cualquiera de hijos. Los hijos de un nodo están
 * ordenados de izquierda a derecha, de tal forma que el primer hijo de un nodo se
 * llama hijo izquierdo, el segundo es el hermano derecho de éste, el tercero es el
 * hermano derecho del segundo y así sucesivamente.
/*/

template <typename T> class Agen{

    /* Declaración adelantada privada */
    struct celda;

public:

    typedef celda* nodo;
    static const nodo NODO_NULO;

    // Post: Construye un árbol vacío.
    explicit Agen();

    // Pre: El árbol está vacío.
    // Post: Inserta el nodo raíz de A cuyo contenido será e.
    void insertarRaiz(const T& e);

    // Pre: n es un nodo del árbol.
    // Post: Inserta el elemento e como hijo iquierdo del nodo n. Si ya existe
    //		 hijo izquierdo, éste se convierte en el hermano derecho del nuevo nodo
    void insertarHijoIzqdo(nodo n, const T& e);

    // Pre: n es un nodo del árbol y no es el nodo raíz.
    // Post: Inserta el elemento e como hermano derecho del nodo n del árbol.
    //		 Si ya existe hermano derecho, éste se convierte en el hermano derecho del nuevo nodo.
    void insertarHermDrcho(nodo n, const T& e);

    // Pre: n es un nodo del árbol. Tiene hijo izquierdo que es hoja.
    // Post: Destruye el hijo izquierdo del nodo n. El segundo hijo, si existe, se convierte en el
    //		 nuevo hijo izquierdo de n.
    void eliminarHijoIzqdo(nodo n);

    // Pre: n es un nodo del árbol. Tiene hermano derecho que es hoja.
    // Post: destruye el hermano derecho del nodo n. El siguiente hermano se convierte en el nuevo hermano derecho de n.
    void eliminarHermDrcho(nodo n);

    // Pre: El árbol tiene un único nodo.
    // Post: Destruye la raíz.
    void eliminarRaiz();

    // Post: Devuelve true si el árbol está vacío y false en caso contrario.
    bool arbolVacio() const;

    // Pre: n es un nodo del árbol.
    // Post: Devuelve el elemento del nodo n.
    const T& elemento(nodo n) const;
    T& elemento(nodo n);

    // Post: Devuelve el nodo raíz del árbol. Si el árbol está vacío, devuelve NODO_NULO.
    nodo raiz() const;

    // Pre: n es un nodo del árbol.
    // Post: Devuelve el padre del nodo n. Si n es el nodo raíz, devuelve NODO_NULO.
    nodo padre(nodo n) const;

    // Pre: n es un nodo del árbol.
    // Post: Devuelve el hijo izquierdo de n. Si no existe devuelve NODO_NULO.
    nodo hijoIzqdo(nodo n) const;

    // Pre: n es un nodo del árbol.
    // Post: Devuelve el hermano derecho de n. Si no existe devuelve NODO_NULO.
    nodo hermDrcho(nodo n) const;

    Agen(const Agen<T>& A);
    Agen<T>& operator =(const Agen<T>& A);

    ~Agen();


private:

    struct celda
    {
        T elto;
        nodo padre, hijo, hermano;
        celda(const T& e, nodo p = NODO_NULO):
                elto(e),
                padre(p),
                hijo(NODO_NULO),
                hermano(NODO_NULO)
        {}
    };

    /* Nodo raíz del árbol */
    nodo r;

    void destruirNodos(nodo& n);
    nodo copiar(nodo n);
};

template <typename T>
const typename Agen<T>::nodo Agen<T>::NODO_NULO(0);

template <typename T>
inline Agen<T>::Agen(): r(NODO_NULO) {}

template <typename T>
inline void Agen<T>::insertarRaiz(const T& e)
{
    assert(r == NODO_NULO);	// Árbol vacío

    r = new celda(e);
}

template <typename T>
inline void Agen<T>::insertarHijoIzqdo(Agen<T>::nodo n, const T& e)
{
    assert(n != NODO_NULO);

    /* hijo izquierdo actual */
    nodo izquierdo = n->hijo;
    n->hijo = new celda(e, n);

    /* El actual hijo izquierdo pasa a ser el hermano derecho del nuevo hijo */
    n->hijo->hermano = izquierdo;
}

template <typename T>
inline void Agen<T>::insertarHermDrcho(Agen<T>::nodo n, const T& e)
{
    assert(n != NODO_NULO);
    assert(n != r);				// n no es la raíz

    /* Hermano derecho actual */
    nodo derecho = n->hermano;
    n->hermano = new celda(e, n->padre);

    /* El actual hermano derecho pasa a ser el hermano derecho del nuevo */
    n->hermano->hermano = derecho;
}

template <typename T>
inline void Agen<T>::eliminarHijoIzqdo(Agen<T>::nodo n)
{
    nodo izquierdo;

    assert(n != NODO_NULO);

    izquierdo = n->hijo;

    assert(izquierdo != NODO_NULO);			// Existe hijo izquierdo.
    assert(izquierdo->hijo == NODO_NULO);	// Hijo izquierdo es hoja.

    /* El hermano derecho pasa a ser el nuevo hijo izquierdo */
    n->hijo = izquierdo->hermano;
    delete izquierdo;
}

template <typename T>
inline void Agen<T>::eliminarHermDrcho(Agen<T>::nodo n)
{
    nodo derecho;

    assert(n != NODO_NULO);

    derecho = n->hermano;

    assert(derecho != NODO_NULO);		// Existe hermano derecho.
    assert(derecho->hijo == NODO_NULO);	// Hermano derecho es hoja.

    /* El hermano del hermano se convierte en el nuevo hermano de n*/
    n->hermano = derecho->hermano;
    delete derecho;
}

template <typename T>
inline void Agen<T>::eliminarRaiz()
{
    assert(r != NODO_NULO);			// Árbol no vacío.
    assert(r->hijo == NODO_NULO); 	// La raíz es hoja.

    delete r;
    r = NODO_NULO;
}

template <typename T>
inline bool Agen<T>::arbolVacio() const
{
    return r == NODO_NULO;
}

template <typename T>
inline const T& Agen<T>::elemento(Agen<T>::nodo n) const
{
    assert(n != NODO_NULO);

    return n->elto;
}

template <typename T>
inline T& Agen<T>::elemento(Agen<T>::nodo n)
{
    assert(n != NODO_NULO);

    return n->elto;
}

template <typename T>
inline typename Agen<T>::nodo Agen<T>::raiz() const
{
    return r;
}

template <typename T>
inline typename Agen<T>::nodo Agen<T>::padre(Agen<T>::nodo n) const
{
    assert(n != NODO_NULO);

    return n->padre;
}

template <typename T>
inline typename Agen<T>::nodo Agen<T>::hijoIzqdo(Agen<T>::nodo n) const
{
    assert(n != NODO_NULO);

    return n->hijo;
}

template <typename T>
inline typename Agen<T>::nodo Agen<T>::hermDrcho(Agen<T>::nodo n) const
{
    assert(n != NODO_NULO);

    return n->hermano;
}

template <typename T>
Agen<T>::Agen(const Agen<T>& A)
{
    r = copiar(A.r);
}

template <typename T>
Agen<T>& Agen<T>::operator =(const Agen<T>& A)
{
    /* Evitar autoasignación */
    if(this != &A)
    {
        /* Vaciar el árbol */
        this->~Agen();
        r = copiar(A.r);
    }

    return *this;
}

template <typename T>
inline Agen<T>::~Agen()
{
    destruirNodos(r);	// Vacía el árbol.
}

/* Métodos privados ____________________________________________________________________________________________*/

template <typename T>
void Agen<T>::destruirNodos(Agen<T>::nodo& n)
{
    if(n != NODO_NULO)
    {
        /* destruir hermanos del hijo izquierdo */
        if(n->hijo != NODO_NULO)
        {
            nodo derecho = n->hijo->hermano;

            while(derecho != NODO_NULO)
            {
                n->hijo->hermano = derecho->hermano;
                destruirNodos(derecho);
                derecho = n->hijo->hermano;
            }

            /* Destruye el hijo izquierdo */
            destruirNodos(n->hijo);
        }

        delete n;
        n = NODO_NULO;
    }
}

template <typename T>
typename Agen<T>::nodo Agen<T>::copiar(Agen<T>::nodo n)
{
    nodo m = NODO_NULO;

    if(n != NODO_NULO)
    {
        m = new celda(n->elto);

        if(n->hijo != NODO_NULO)
        {
            /* Copiar el primer subárbol */
            m->hijo = copiar(n->hijo);
            m->hijo->padre = m;

            /* Copiar el resto de subárboles */
            nodo hijo = m->hijo;
            nodo derecho = n->hijo->hermano;

            while(derecho != NODO_NULO)
            {
                hijo = hijo->hermano = copiar(derecho);
                hijo->padre = m;

                derecho = derecho->hermano;
            }
        }
    }

    return m;
}

#endif // AGEN_H_
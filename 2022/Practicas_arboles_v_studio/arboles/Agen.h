#ifndef AGEN_H_
#define AGEN_H_

#include <cassert>
#include <iostream>

/*/
 * Definici�n:
 *
 * Un �rbol general se define como un �rbol cuyos nodos son de cualquier grado, es
 * decir, pueden tener un n�mero cualquiera de hijos. Los hijos de un nodo est�n
 * ordenados de izquierda a derecha, de tal forma que el primer hijo de un nodo se
 * llama hijo izquierdo, el segundo es el hermano derecho de �ste, el tercero es el
 * hermano derecho del segundo y as� sucesivamente.
/*/

template <typename T> class Agen {

    /* Declaraci�n adelantada privada */
    struct celda;

public:

    typedef celda* nodo;
    static const nodo NODO_NULO;

    // Post: Construye un �rbol vac�o.
    explicit Agen();

    // Pre: El �rbol est� vac�o.
    // Post: Inserta el nodo ra�z de A cuyo contenido ser� e.
    void insertaRaiz(const T& e);

    // Pre: n es un nodo del �rbol.
    // Post: Inserta el elemento e como hijo iquierdo del nodo n. Si ya existe
    //		 hijo izquierdo, �ste se convierte en el hermano derecho del nuevo nodo
    void insertarHijoIzqdo(nodo n, const T& e);

    // Pre: n es un nodo del �rbol y no es el nodo ra�z.
    // Post: Inserta el elemento e como hermano derecho del nodo n del �rbol.
    //		 Si ya existe hermano derecho, �ste se convierte en el hermano derecho del nuevo nodo.
    void insertarHermDrcho(nodo n, const T& e);

    // Pre: n es un nodo del �rbol. Tiene hijo izquierdo que es hoja.
    // Post: Destruye el hijo izquierdo del nodo n. El segundo hijo, si existe, se convierte en el
    //		 nuevo hijo izquierdo de n.
    void eliminarHijoIzqdo(nodo n);

    // Pre: n es un nodo del �rbol. Tiene hermano derecho que es hoja.
    // Post: destruye el hermano derecho del nodo n. El siguiente hermano se convierte en el nuevo hermano derecho de n.
    void eliminarHermDrcho(nodo n);

    // Pre: El �rbol tiene un �nico nodo.
    // Post: Destruye la ra�z.
    void eliminarRaiz();

    // Post: Devuelve true si el �rbol est� vac�o y false en caso contrario.
    bool arbolVacio() const;

    // Pre: n es un nodo del �rbol.
    // Post: Devuelve el elemento del nodo n.
    const T& elemento(nodo n) const;
    T& elemento(nodo n);

    // Post: Devuelve el nodo ra�z del �rbol. Si el �rbol est� vac�o, devuelve NODO_NULO.
    nodo raiz() const;

    // Pre: n es un nodo del �rbol.
    // Post: Devuelve el padre del nodo n. Si n es el nodo ra�z, devuelve NODO_NULO.
    nodo padre(nodo n) const;

    // Pre: n es un nodo del �rbol.
    // Post: Devuelve el hijo izquierdo de n. Si no existe devuelve NODO_NULO.
    nodo hijoIzqdo(nodo n) const;

    // Pre: n es un nodo del �rbol.
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
        celda(const T& e, nodo p = NODO_NULO) :
            elto(e),
            padre(p),
            hijo(NODO_NULO),
            hermano(NODO_NULO)
        {}
    };

    /* Nodo ra�z del �rbol */
    nodo r;

    void destruirNodos(nodo& n);
    nodo copiar(nodo n);
};

template <typename T>
const typename Agen<T>::nodo Agen<T>::NODO_NULO(0);

template <typename T>
inline Agen<T>::Agen() : r(NODO_NULO) {}

template <typename T>
inline void Agen<T>::insertaRaiz(const T& e)
{
    assert(r == NODO_NULO);	// �rbol vac�o

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
    assert(n != r);				// n no es la ra�z

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
    assert(r != NODO_NULO);			// �rbol no vac�o.
    assert(r->hijo == NODO_NULO); 	// La ra�z es hoja.

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
    /* Evitar autoasignaci�n */
    if (this != &A)
    {
        /* Vaciar el �rbol */
        this->~Agen();
        r = copiar(A.r);
    }

    return *this;
}

template <typename T>
inline Agen<T>::~Agen()
{
    destruirNodos(r);	// Vac�a el �rbol.
}

/* M�todos privados ____________________________________________________________________________________________*/

template <typename T>
void Agen<T>::destruirNodos(Agen<T>::nodo& n)
{
    if (n != NODO_NULO)
    {
        /* destruir hermanos del hijo izquierdo */
        if (n->hijo != NODO_NULO)
        {
            nodo derecho = n->hijo->hermano;

            while (derecho != NODO_NULO)
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

    if (n != NODO_NULO)
    {
        m = new celda(n->elto);

        if (n->hijo != NODO_NULO)
        {
            /* Copiar el primer sub�rbol */
            m->hijo = copiar(n->hijo);
            m->hijo->padre = m;

            /* Copiar el resto de sub�rboles */
            nodo hijo = m->hijo;
            nodo derecho = n->hijo->hermano;

            while (derecho != NODO_NULO)
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
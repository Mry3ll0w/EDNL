#ifndef ABB_H_
#define ABB_H_

#include <cassert>

/*/
 * Definición:
 *
 * Un árbol binario de búsqueda es un árbol binario en el que los nodos almacenan elementos de un conjunto.
 * La propiedad que define a estos árboles es que todos los elementos almacenados en el subárbol izquierdo de cualquier nodo n
 * son menores que el elemento de n, y todos los elementos almacenados en el subárbol derecho de n son mayores que el elemento de n.
 *
 * Consideramos que existe un orden lineal definido sobre el tipo de los elementos dado por el operador < .
 *
/*/

template <typename T> class Abb
{
public:

    // Post: Construye un árbol binario de búsqueda vacío.
    Abb();

    // Post: Si el elemento e pertenece al árbol, devuelve el subárbol en cuya
    //		 raíz se encuentra e. En caso contrario devuelve un árbol vacío.
    const Abb& buscar(const T& e) const;

    // Post: Si e no pertenece al árbol, lo inserta. En caso contrario, el árbol no se modifica.
    void insertar(const T& e);

    // Post: Elimina el elemento e del árbol. Si e no se encuentra, el árbol no se modifica.
    void eliminar(const T& e);

    // Devuelve true si el árbol está vacío y false en caso contrario.
    bool vacio() const;

    // Pre: Árbol no vacío
    // Post: Devuelve el elemento de la raíz de un árbol binario de búsqueda.
    const T& elemento() const;

    // Pre: Árbol no vacío.
    // Post: Devuelve el subárbol izquierdo.
    const Abb& izqdo() const;

    // Pre: Árbol no vacío.
    // Post: Devuelve el subárbol derecho.
    const Abb& drcho() const;

    /* Constructor de copia */
    Abb(const Abb& A);

    /* Operador de asignación */
    Abb& operator =(const Abb& A);

    /* Destructor */
    ~Abb();

private:

    struct arbol
    {
        T elto;
        Abb izq, der;
        arbol(const T& e) : elto(e) {}
    };

    /* Raíz del árbol */
    arbol* r;

    T borrarMin();
    void copiar(const Abb& A);
};

/* Métodos públicos ________________________________________________________________________________________*/

template <typename T>
inline Abb<T>::Abb() : r(0) {}

template <typename T>
inline bool Abb<T>::vacio() const
{
    return r == 0;
}

template <typename T>
const Abb<T>& Abb<T>::buscar(const T& e) const
{
    /* Árbol vacío: e no encontrado. */
    if (r == 0)
        return *this;

    /* Buscar en el subárbol izquierdo */
    else if (e < r->elto)
        return r->izq.buscar(e);

    /* Buscar en el subárbol derecho */
    else if (r->elto < e)
        return r->der.buscar(e);

    /* Encontrado e en la raíz */
    else
        return *this;
}

template <typename T>
void Abb<T>::insertar(const T& e)
{
    /* Árbol vacío */
    if (r == 0)
        r = new arbol(e);

    /* Insertar en el subárbol izquierdo */
    else if (e < r->elto)
        r->izq.insertar(e);

    /* Insertar en el subárbol derecho */
    else if (r->elto < e)
        r->der.insertar(e);
}

template <typename T>
void Abb<T>::eliminar(const T& e)
{
    /* Árbol no vacío */
    if (r != 0)
    {
        /* Eliminar e del subárbol izquierdo */
        if (e < r->elto)
            r->izq.eliminar(e);

        /* Eliminar e del subárbol derecho */
        else if (r->elto < e)
            r->der.eliminar(e);

        /* Eliminar e de la raíz si la raíz es hoja*/
        else if (r->izq.r == 0 && r->der.r == 0)
        {
            delete(r);
            r = 0;
        }

        /* Eliminar e de la raíz si tiene sólo hijo izquierdo */
        else if (r->der.r == 0)
        {
            arbol* a = r->izq.r;

            /* Impide destruir el subárbol izquierdo */
            r->izq.r = 0;

            delete(r);
            r = a;
        }

        /* Eliminar e de la raíz si tiene sólo hijo derecho */
        else if (r->izq.r == 0)
        {
            arbol* a = r->der.r;

            /* Impide destruir el subárbol derecho */
            r->der.r = 0;

            delete(r);
            r = a;
        }

        /* Eliminar e de la raíz si tiene dos hijos. */
        else
        {
            /* Se elimina el mínimo del subárbol derecho y sustituye el elemento
                de la raíz por éste. */

            r->elto = r->der.borrarMin();
        }
    }
}

template <typename T>
inline const T& Abb<T>::elemento() const
{
    assert(r != 0);
    return r->elto;
}

template <typename T>
inline const Abb<T>& Abb<T>::izqdo() const
{
    assert(r != 0);
    return r->izq;
}

template <typename T>
inline const Abb<T>& Abb<T>::drcho() const
{
    assert(r != 0);
    return r->der;
}

template <typename T>
inline Abb<T>::Abb(const Abb<T>& A) : r(0)
{
    copiar(A);
}

template <typename T>
Abb<T>& Abb<T>::operator =(const Abb<T>& A)
{
    /* Evitar autoasignación */
    if (this != &A)
    {
        this-> ~Abb();
        copiar(A);
    }

    return *this;
}

template <typename T>
Abb<T>::~Abb()
{
    /* Árbol no vacío */
    if (r != 0)
    {
        /* Internamente llama a r->izq.~Abb() y a r->der.~Abb() */
        delete r;

        /* El árbol queda vacío */
        r = 0;
    }
}

/* Métodos privados ________________________________________________________________________________________*/

/* Elimina el nodo que almacena el menor elemento del árbol. Devuelve el elemento del nodo eliminado */
template <typename T>
T Abb<T>::borrarMin()
{
    /* Subárbol izquierdo vacío */
    if (r->izq.r == 0)
    {
        T e = r->elto;
        arbol* hd = r->der.r;

        /* Impide destruir el subárbol derecho */
        r->der.r = 0;
        delete(r);

        /* Sustituye r por el subárbol derecho */
        r = hd;

        return e;
    }

    else
    {
        return r->izq.borrarMin();
    }
}


/* Copiar el árbol A en *this */
template <typename T>
void Abb<T>::copiar(const Abb<T>& A)
{
    /* Árbol no vacío */
    if (A.r != 0)
    {
        /* Copiar raíz */
        r = new arbol(A.r->elto);

        /* Copiar subárbol izquierdo */
        r->izq.copiar(A.r->izq);

        /* Copiar subárbol derecho */
        r->der.copiar(A.r->der);
    }
}

/*__________________________________________________________________________________________________________*/

#endif // ABB_H_
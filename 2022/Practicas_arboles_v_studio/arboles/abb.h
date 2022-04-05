#ifndef ABB_H_
#define ABB_H_

#include <cassert>

/*/
 * Definici�n:
 *
 * Un �rbol binario de b�squeda es un �rbol binario en el que los nodos almacenan elementos de un conjunto.
 * La propiedad que define a estos �rboles es que todos los elementos almacenados en el sub�rbol izquierdo de cualquier nodo n
 * son menores que el elemento de n, y todos los elementos almacenados en el sub�rbol derecho de n son mayores que el elemento de n.
 *
 * Consideramos que existe un orden lineal definido sobre el tipo de los elementos dado por el operador < .
 *
/*/

template <typename T> class Abb
{
public:

    // Post: Construye un �rbol binario de b�squeda vac�o.
    Abb();

    // Post: Si el elemento e pertenece al �rbol, devuelve el sub�rbol en cuya
    //		 ra�z se encuentra e. En caso contrario devuelve un �rbol vac�o.
    const Abb& buscar(const T& e) const;

    // Post: Si e no pertenece al �rbol, lo inserta. En caso contrario, el �rbol no se modifica.
    void insertar(const T& e);

    // Post: Elimina el elemento e del �rbol. Si e no se encuentra, el �rbol no se modifica.
    void eliminar(const T& e);

    // Devuelve true si el �rbol est� vac�o y false en caso contrario.
    bool vacio() const;

    // Pre: �rbol no vac�o
    // Post: Devuelve el elemento de la ra�z de un �rbol binario de b�squeda.
    const T& elemento() const;

    // Pre: �rbol no vac�o.
    // Post: Devuelve el sub�rbol izquierdo.
    const Abb& izqdo() const;

    // Pre: �rbol no vac�o.
    // Post: Devuelve el sub�rbol derecho.
    const Abb& drcho() const;

    /* Constructor de copia */
    Abb(const Abb& A);

    /* Operador de asignaci�n */
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

    /* Ra�z del �rbol */
    arbol* r;

    T borrarMin();
    void copiar(const Abb& A);
};

/* M�todos p�blicos ________________________________________________________________________________________*/

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
    /* �rbol vac�o: e no encontrado. */
    if (r == 0)
        return *this;

    /* Buscar en el sub�rbol izquierdo */
    else if (e < r->elto)
        return r->izq.buscar(e);

    /* Buscar en el sub�rbol derecho */
    else if (r->elto < e)
        return r->der.buscar(e);

    /* Encontrado e en la ra�z */
    else
        return *this;
}

template <typename T>
void Abb<T>::insertar(const T& e)
{
    /* �rbol vac�o */
    if (r == 0)
        r = new arbol(e);

    /* Insertar en el sub�rbol izquierdo */
    else if (e < r->elto)
        r->izq.insertar(e);

    /* Insertar en el sub�rbol derecho */
    else if (r->elto < e)
        r->der.insertar(e);
}

template <typename T>
void Abb<T>::eliminar(const T& e)
{
    /* �rbol no vac�o */
    if (r != 0)
    {
        /* Eliminar e del sub�rbol izquierdo */
        if (e < r->elto)
            r->izq.eliminar(e);

        /* Eliminar e del sub�rbol derecho */
        else if (r->elto < e)
            r->der.eliminar(e);

        /* Eliminar e de la ra�z si la ra�z es hoja*/
        else if (r->izq.r == 0 && r->der.r == 0)
        {
            delete(r);
            r = 0;
        }

        /* Eliminar e de la ra�z si tiene s�lo hijo izquierdo */
        else if (r->der.r == 0)
        {
            arbol* a = r->izq.r;

            /* Impide destruir el sub�rbol izquierdo */
            r->izq.r = 0;

            delete(r);
            r = a;
        }

        /* Eliminar e de la ra�z si tiene s�lo hijo derecho */
        else if (r->izq.r == 0)
        {
            arbol* a = r->der.r;

            /* Impide destruir el sub�rbol derecho */
            r->der.r = 0;

            delete(r);
            r = a;
        }

        /* Eliminar e de la ra�z si tiene dos hijos. */
        else
        {
            /* Se elimina el m�nimo del sub�rbol derecho y sustituye el elemento
                de la ra�z por �ste. */

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
    /* Evitar autoasignaci�n */
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
    /* �rbol no vac�o */
    if (r != 0)
    {
        /* Internamente llama a r->izq.~Abb() y a r->der.~Abb() */
        delete r;

        /* El �rbol queda vac�o */
        r = 0;
    }
}

/* M�todos privados ________________________________________________________________________________________*/

/* Elimina el nodo que almacena el menor elemento del �rbol. Devuelve el elemento del nodo eliminado */
template <typename T>
T Abb<T>::borrarMin()
{
    /* Sub�rbol izquierdo vac�o */
    if (r->izq.r == 0)
    {
        T e = r->elto;
        arbol* hd = r->der.r;

        /* Impide destruir el sub�rbol derecho */
        r->der.r = 0;
        delete(r);

        /* Sustituye r por el sub�rbol derecho */
        r = hd;

        return e;
    }

    else
    {
        return r->izq.borrarMin();
    }
}


/* Copiar el �rbol A en *this */
template <typename T>
void Abb<T>::copiar(const Abb<T>& A)
{
    /* �rbol no vac�o */
    if (A.r != 0)
    {
        /* Copiar ra�z */
        r = new arbol(A.r->elto);

        /* Copiar sub�rbol izquierdo */
        r->izq.copiar(A.r->izq);

        /* Copiar sub�rbol derecho */
        r->der.copiar(A.r->der);
    }
}

/*__________________________________________________________________________________________________________*/

#endif // ABB_H_
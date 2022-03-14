//Implementacion vector de posiciones relativas
#ifndef APO_H
#define APO_H
#include <cassert>

template <typename T> class Apo {
public:
    explicit Apo(size_t maxNodos); // constructor
    void insertar(const T& e);
    void suprimir();
    const T& cima() const;
    bool vacio() const;
    Apo(const Apo<T>& A); // ctor. de copia
    Apo<T>& operator =(const Apo<T>& A); // asignación de apo
    ~Apo(); // destructor
    void mostrar();
private:
    typedef int nodo; // índice del vector entre 0 y maxNodos-1
    T* nodos; // vector de nodos
    int maxNodos; // tamaño del vector
    nodo ultimo; // último nodo del árbol

    nodo padre(nodo i) const { return (i-1)/2; }
    nodo hIzq(nodo i) const { return 2*i+1; }
    nodo hDer(nodo i) const { return 2*i+2; }
    void flotar(nodo i);
    void hundir(nodo i);
};
template <typename T>
inline Apo<T>::Apo(size_t maxNodos) :nodos(new T[maxNodos]),maxNodos(maxNodos),ultimo(-1){}

template <typename T>
inline const T& Apo<T>::cima() const
{
    assert(ultimo > -1); // Apo no vacío
    return nodos[0];
}
template <typename T>
inline bool Apo<T>::vacio() const
{
    return (ultimo == -1);
}
template <typename T>
inline void Apo<T>::insertar(const T& e)
{
    assert(ultimo < maxNodos-1); // Apo no lleno
    nodos[++ultimo] = e;
    if (ultimo > 0)
    flotar(ultimo); // Reordenar
}

template <typename T>
void Apo<T>::flotar(nodo i)
{
    T e = nodos[i];
    while (i > 0 && e < nodos[padre(i)])
    {
        nodos[i] = nodos[padre(i)];
        i = padre(i);
    }
    nodos[i] = e;
}
template <typename T>
inline void Apo<T>::suprimir()
{
    assert(ultimo > -1); // Apo no vacío
    if (--ultimo > -1) // Apo no queda vacío
    {
        nodos[0] = nodos[ultimo+1];
        if (ultimo > 0) // Quedan dos o más elementos.
            hundir(0); // Reordenar
    }
}
template <typename T>
void Apo<T>::hundir(nodo i)
{
    bool fin = false;
    T e = nodos[i];
    while (hIzq(i) <= ultimo && !fin) // hundir e
    {
        nodo hMin; // hijo menor del nodo i
        if (hIzq(i) < ultimo && nodos[hDer(i)] < nodos[hIzq(i)])
            hMin = hDer(i);
        else
            hMin = hIzq(i);
        if (nodos[hMin] < e) { // subir el hijo menor
            nodos[i] = nodos[hMin];
            i = hMin;
        }
        else // e <= hijos
            fin = true;
    }
    nodos[i] = e; // colocar e
}
template <typename T>
inline Apo<T>::~Apo()
{
    delete[] nodos;
}
template <typename T>
Apo<T>::Apo(const Apo<T>& A) :nodos(new T[A.maxNodos]),maxNodos(A.maxNodos),ultimo(A.ultimo)
{
    // copiar el vector
    for (nodo n = 0; n <= ultimo; n++)
        nodos[n] = A.nodos[n];
}
template <typename T>
Apo<T>& Apo<T>::operator =(const Apo<T>& A)
{
    if (this != &A) { // evitar autoasignación
    // Destruir el vector y crear uno nuevo si es necesario
        if (maxNodos != A.maxNodos) {
            delete[] nodos;
            maxNodos = A.maxNodos;
            nodos = new T[maxNodos];
        }
        ultimo = A.ultimo;
        // Copiar el vector
        for (nodo n = 0; n <= ultimo; n++)
            nodos[n] = A.nodos[n];
    }
    return *this;
}
template <typename T>
void Apo<T>::mostrar()
{
    for(int i=0;i<=ultimo;i++)
        std::cout << nodos[i] << ",";
    std::cout << std::endl;
}

template class Apo<int>;
#endif // APO_H

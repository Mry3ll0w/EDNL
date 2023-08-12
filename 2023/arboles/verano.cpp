#include <iostream>
#include "arbolbinenla.h"
#include "agenEnlazado.h"
#include "abb.h"
using namespace std; // Avoid using std:: ....

/**
 * Practica 1 Arboles
 * Implementa un subprograma que calcule el número de nodos de un árbol binario.
 */

template <class T>
int numNodosAbin(Abin<T> &abArbol, typename Abin<T>::nodo nd)
{
    if (nd == Abin<T>::NODO_NULO)
        return 0;

    return 1 + numNodosAbin(abArbol, abArbol.hijoDrcho(nd)) + numNodosAbin(abArbol, abArbol.hijoIzqdo(nd));
}

/**
 * Ejercicio 2:
 * Implementa un subprograma que calcule la altura de un árbol binario.
 * La altura de un arbol binario se mide por el maximo de niveles de ambos hijos
 */

template <class T>
int alturaArbolBinario(Abin<T> &abArbol, typename Abin<T>::nodo nd)
{
    if (nd == Abin<T>::NODO_NULO)
        return -1;

    return 1 +
           fmax(alturaArbolBinario(abArbol, abArbol.hijoDrcho(nd)),
                alturaArbolBinario(abArbol, abArbol.hijoIzqdo(nd)));
}

/**
 * Ejercicio 3 :
 * Implementa un subprograma que, dados un árbol binario y un nodo del mismo, determine la
 * profundidad de este nodo en dicho árbol.
 */
template <class T>
int profundidadNodoAbin(Abin<T> &abArbol, typename Abin<T>::nodo nd)
{
    if (nd == Abin<T>::NODO_NULO)
        return 0;
    return 1 + profundidadNodoAbin(abArbol, abArbol.padre(nd));
}

/**
 * Ejercicio 6
 * Implementa un subprograma que determine el nivel de desequilibrio de un árbol binario,
 * definido como el máximo desequilibrio de todos sus nodos. El desequilibrio de un nodo
 * se define como la diferencia entre las alturas de los subárboles del mismo.
 */

int diferenciaAlturas(Abin<int> abArbol, typename Abin<int>::nodo nd)
{
    return std::abs(alturaArbolBinario(abArbol, abArbol.hijoDrcho(nd)) - alturaArbolBinario(abArbol, abArbol.hijoIzqdo(nd)));
}

int desequilibrioMaximoRec(Abin<int> abArbol, typename Abin<int>::nodo nd)
{
    if (nd == Abin<int>::NODO_NULO)
    {
        return 0;
    }
    return std::fmax(
        std::fmax(desequilibrioMaximoRec(abArbol, abArbol.hijoDrcho(nd)),
                  desequilibrioMaximoRec(abArbol, abArbol.hijoIzqdo(nd))),
        diferenciaAlturas(abArbol, nd));
}

int desequilibrioAbin(Abin<int> abArbol)
{
    if (abArbol.arbolVacio())
        return 0;
    else
        return desequilibrioMaximoRec(abArbol, abArbol.raiz());
}

// ####################################################################################

// Practica 2 Arboles binarios
/**
 * Ejercicio 1:
 * Dos árboles binarios son similares cuando tienen idéntica estructura de ramificación,
 * es decir, ambos son vacíos, o en caso contrario, tienen subárboles izquierdo y
 * derecho similares.
 * Implementa un subprograma que determine si dos árboles binarios son similares
 */

template <class T>
bool arbolesSimilaresAbin(const Abin<T> abArbol1, const Abin<T> abArbol2,
                          typename Abin<T>::nodo nd1, typename Abin<T>::nodo nd2)
{
    if (nd1 == Abin<T>::NODO_NULO && nd2 == Abin<T>::NODO_NULO)
    {
        return true; // Si cuando sale del bucle ambos no son nulos tiene != ramificacion
    }
    else if (nd1 != Abin<T>::NODO_NULO && nd2 != Abin<T>::NODO_NULO)
    {
        return arbolesSimilaresAbin(abArbol1, abArbol2, abArbol1.hijoIzqdo(nd1), abArbol2.hijoIzqdo(nd2)) &&
               arbolesSimilaresAbin(abArbol1, abArbol2, abArbol1.hijoDrcho(nd1), abArbol2.hijoDrcho(nd2));
    }
    return false;
    // Comprobamos que pasa al salir
}

/**
 * Ejercicio 2
 * Para un árbol binario B, podemos construir el árbol binario reflejado BR cambiando los
 * subárboles izquierdo y derecho en cada nodo.
 * Implementa un subprograma que devuelva el árbol binario reflejado de uno dado.
 */

template <class T>
void arbolReflejadoAbin(const Abin<T> &abArbolOriginal, Abin<T> abArbolDestino, typename Abin<T>::nodo nd1,
                        typename Abin<T>::nodo nd2)
{
    if (nd1 != Abin<T>::NODO_NULO)
    {

        if (abArbolOriginal.hijoIzqdo(nd1) != Abin<T>::NODO_NULO)
        {
            abArbolDestino.insertarhijoDrcho(nd2, abArbolOriginal.elemento(abArbolOriginal.hijoIzqdo(nd1)));
            arbolReflejadoAbin(abArbolOriginal, abArbolDestino, abArbolOriginal.hijoIzqdo(nd1), abArbolDestino.hijoDrcho(nd2));
        }
        if (abArbolOriginal.hijoDrcho(nd1) != Abin<T>::NODO_NULO)
        {
            abArbolDestino.insertarhijoIzqdo(nd2, abArbolOriginal.elemento(abArbolOriginal.hijoDrcho(nd1)));
            arbolReflejadoAbin(abArbolOriginal, abArbolDestino, abArbolOriginal.hijoDrcho(nd1), abArbolDestino.hijoIzqdo(nd2));
        }
    }
}

/**Ejercicio 3
 * El TAD árbol binario puede albergar expresiones matemáticas mediante un árbol de expresión.
 * Dentro del árbol binario los nodos hojas contendrán los operandos, y el resto de los nodos
 * los operadores.
 *
 *      a) Define el tipo de los elementos del árbol para que los nodos puedan almacenar
 *          operadores y operandos.
 *
 *      b) Implementa una función que tome un árbol binario de expresión (aritmética) y
 *         devuelva el resultado de la misma. Por simplificar el problema se puede asumir
 *         que el árbol representa una expresión correcta. Los operadores binarios posibles
 *         en la expresión aritmética serán suma, resta, multiplicación y división.
 */

double procesaPostfijo(Abin<std::string> A, typename Abin<std::string>::nodo n)
{
    std::string strElemento = A.elemento(n);

    if (strElemento == "+")
    {
        return (procesaPostfijo(A, A.hijoIzqdo(n)) + procesaPostfijo(A, A.hijoDrcho(n)));
    }
    else if (strElemento == "-")
    {
        return (procesaPostfijo(A, A.hijoIzqdo(n)) + procesaPostfijo(A, A.hijoDrcho(n)));
    }
    else if (strElemento == "*")
    {
        return (procesaPostfijo(A, A.hijoIzqdo(n)) * procesaPostfijo(A, A.hijoDrcho(n)));
    }
    else if (strElemento == "/")
    {
        return (procesaPostfijo(A, A.hijoIzqdo(n)) / procesaPostfijo(A, A.hijoDrcho(n)));
    }
    else
    {
        return std::stof(strElemento);
    }
}

template <class T>
void printAbin(Abin<T> ab, typename Abin<T>::nodo nd)
{
    if (nd != Abin<T>::NODO_NULO)
    {
        printAbin(ab, ab.hijoDrcho(nd));
        std::cout << ab.elemento(nd) << ", ";
        printAbin(ab, ab.hijoIzqdo(nd));
    }
}

// ###################################################################################
/**
 * Practica 3 de Arboles Generales
 */

/**
 * Ejercicio 1: Contar los nodos en un arbol general.
 */
template <class T>
int numNodosAgen(Agen<T> &agArbol, typename Agen<T>::nodo nd)
{
    int iNumNodos = 0;
    if (nd != Agen<T>::NODO_NULO)
    {
        nd = agArbol.hijoIzqdo(nd);
        while (nd != Agen<T>::NODO_NULO)
        {
            numNodosAgen(agArbol, nd);
            iNumNodos++;
            nd = agArbol.hermDrcho(nd);
        }
    }
    return iNumNodos;
}

template <class T>
int gradoAgenRec(Agen<T> agArbol, typename Agen<T>::nodo nd)
{
    int iGradoAgen = -1;
    if (nd != Agen<T>::NODO_NULO)
    {
        nd = agArbol.hijoIzqdo(nd);
        while (nd != Agen<T>::NODO_NULO)
        {
            iGradoAgen = std::max(iGradoAgen, gradoAgen(agArbol, nd));
            nd = agArbol.hermDrcho(nd);
        }
    }
}

/**
 * Ejercicio 2
 * Implementa un subprograma que dados un árbol y un nodo dentro de dicho árbol
 * determine la profundidad de éste nodo en el árbol.
 */

template <class T>
int profundidadNodoAgen(typename Agen<T>::NODO nd, Agen<T> &agArbol)
{
    if (nd == agArbol.raiz())
    {
        return 0;
    }
    else
        return 1 + profundidadNodoAgen(agArbol.padre(nd), agArbol);
}

/**
* Enunciado:
*   3. Se define el desequilibrio de un árbol general como la máxima diferencia entre las alturas
    de los subárboles más bajo y más alto de cada nivel. Implementa un subprograma que calcule
    el grado de desequilibrio de un árbol general. ==> Se puede hallar haciendo la diferencia entre la rama mas larga del arbol y la mas pequeña.
    1) Necesitamos la altura maxima del arbol, en consecuencia se trata de la altura de la raiz
    2) Iterar todos y cada uno de los subArboles a ver cual tiene la menor

*/

// Definimos la altura como
template <class T>
int alturaNodoAgen(typename Agen<T>::nodo nd, Agen<T> agArbol)
{
    int iAlturaNodo = -1;
    if (nd != Agen<T>::NODO_NULO)
    {
        nd = agArbol.hijoIzqdo(nd);
        while (nd != Agen<T>::NODO_NULO)
        {
            // Proceso la altura en inorden
            iAlturaNodo = std::max(iAlturaNodo, alturaNodoAgen(nd, agArbol)); // Hundimiento en recursividad
            nd = agArbol.hermDrcho(nd);
        }
    }
    return 1 + iAlturaNodo; // Hacemos 1 + puesto que cada vez que pueda la funcion hundirse significa que hemos bajado de nivel ==> +1 altura
}

template <class T>
int desequilibrioAgenRec(Agen<T> agArbol, typename Agen<T>::nodo nd, int iAlturaRaiz)
{
    int iAlturaMinima = iAlturaRaiz;
    if (nd != Agen<T>::NODO_NULO)
    {
        nd = agArbol.hijoIzqdo(nd);
        while (nd != Agen<T>::NODO_NULO)
        {
            desequilibrioAgenRec(agArbol, nd, iAlturaRaiz);
            iAlturaMinima = std::min(iAlturaMinima, alturaNodoAgen(nd, agArbol));
            nd = agArbol.hermDrcho(nd);
        }
    }
    // Cuando salimos del bucle simplemente devolcemos la diferencia entre la altura de la raiz
    return iAlturaRaiz - iAlturaMinima;
}

template <class T>
int desequilibrioAgen(Agen<T> agArbol)
{
    if (agArbol.arbolVacio())
        return 0;
    else
        return desequilibrioAgenRec(agArbol, agArbol.raiz(), alturaNodoAgen(agArbol.raiz(), agArbol));
}

/**
 * Ejercicio 4:
 * Dado un árbol general de enteros A y un entero x, implementa un subprograma que realice
 * la poda de A a partir de x. Se asume que no hay elementos repetidos en A.
 */

template <class T>
void eliminarDescendenciaNodo(Agen<T> &agArbol, typename Agen<T>::nodo nd)
{
    // Voy eliminando el hijoIzquierdo hasta que me quede sin descendientes, hay que hacerlo en postorden
    while (agArbol.hijoIzqdo(nd) != Agen<T>::NODO_NULO)
    {
        eliminarDescendenciaNodo(agArbol, agArbol.hijoIzqdo(nd));
        std::cout << "ESTOY ELIMINANDO: " << agArbol.elemento(nd) << std::endl;
        agArbol.eliminarHijoIzqdo(nd);
    }
}

template <class T>
void podaArbolAgenRec(Agen<T> &agArbol, typename Agen<T>::nodo nd, const T &elementoBuscado)
{
    if (nd != Agen<T>::NODO_NULO)
    {

        nd = agArbol.hijoIzqdo(nd);
        while (nd != Agen<T>::NODO_NULO)
        {
            podaArbolAgenRec(agArbol, nd, elementoBuscado);
            if (agArbol.elemento(nd) == elementoBuscado)
            {
                eliminarDescendenciaNodo(agArbol, nd);
            }
            nd = agArbol.hermDrcho(nd);
        }
    }
}

template <class T>
void podaAgen(Agen<T> &agArbol, const T &elementoBuscado)
{
    if (!agArbol.arbolVacio())
    {

        // Caso general
        podaArbolAgenRec(agArbol, agArbol.raiz(), elementoBuscado);
        printAgen(agArbol.raiz(), agArbol);
    }
}

/**
 * Examen "nodos verdes"
 * Cuenta todos los nodos con exactamente 3 nietos
 */

// Podemos decir que es nieto de un nodo cuando la altura de un nodo dado sea igual a
//  su altura - 2
template <class T>
int cuentaNietos(Agen<T> agArbol, typename Agen<T>::nodo nd, int alturaNodoPadre)
{
    int numNietos = 0;
    if (nd != Agen<T>::NODO_NULO)
    {
        nd = agArbol.hijoIzqdo(nd);
        while (nd != Agen<T>::NODO_NULO)
        {
            if (std::abs(alturaNodoAgen(nd, agArbol) - alturaNodoPadre) == 2)
            {
                numNietos++;
            }
            nd = agArbol.hermDrcho(nd);
        }
    }
    return numNietos;
}

template <class T>
int cuenta3Nietos(Agen<T> agArbol, typename Agen<T>::nodo nd)
{
    int i3Nietos = 0;
    if (nd != Agen<T>::NODO_NULO)
    {
        nd = agArbol.hijoIzqdo(nd);
        while (nd != Agen<T>::NODO_NULO)
        {

            if (cuentaNietos(agArbol, nd, alturaNodoAgen(agArbol, nd)) == 3)
                i3Nietos++;

            nd = agArbol.hermDrcho(nd);
        }
    }
    return i3Nietos;
}

template <class T>
int nodos3Nietos(Agen<T> agArbol)
{
    if (agArbol.arbolVacio())
        return 0;
    else
    {
        return cuenta3Nietos(agArbol, agArbol.raiz());
    }
}

// PrintAgen
template <typename T>
void printAgen(typename Agen<T>::nodo n, const Agen<T> &A)
// Recorrido en preorden del subárbol cuya raíz es el nodo n
// perteneciente al árbol A. Cada nodo visitado se procesa mediante // la función procesar().
{
    if (n != Agen<T>::NODO_NULO)
    {

        n = A.hijoIzqdo(n);
        while (n != Agen<T>::NODO_NULO)
        {
            printAgen(n, A);
            std::cout << A.elemento(n) << ", ";
            n = A.hermDrcho(n);
        }
        std::cout << std::endl;
    }
}

// Practica 4 de Arboles
/**
 * Ejercicio 1
 * Implementa una nueva operación del TAD Abb que tomando un elemento del mismo
 * elimine al completo el subárbol que cuelga de él.
 */

template <class T>
void podarAbb(Abb<T> &ab, T &elemento)
{
    if (!ab.buscar(elemento).vacio())
    {
        ab.buscar(elemento).~Abb();
    }
}

/**
 * Ejercicio 2 P4 Arboles
 * Un árbol binario de búsqueda se puede equilibrar realizando el recorrido en inorden
 * del árbol para obtener el listado ordenado de sus elementos y a continuación, repartir
 * equitativamente los elementos a izquierda y derecha colocando la mediana en la raíz y
 * construyendo recursivamente los subárboles izquierdo y derecho de cada nodo.
 * Implementa este algoritmo para equilibrar un ABB.
 */

template <class T>
std::vector<T> recorreAbbInorden(Abb<T> &ab)
{
    std::vector<T> vEltos;
    if (!ab.vacio())
    {
        recorreAbbInorden(ab.izqdo());
        vEltos.push_back(ab.elemento());
        recorreAbbInorden(ab.drcho());
    }
    return vEltos;
}

template <class T>
void equilibrarAbbRec(std::vector<T> eltos, Abb<T> &A, int ini, int fin) // Se inserta de forma sencilla mediante el usa de la insercion binaria
{
    if (fin != ini)
    {
        int pos = (fin - ini) / 2 + ini;
        A.insertar(eltos[pos]);
        equilibrarRec(eltos, A, ini, pos);
        equilibrarRec(eltos, A, pos + 1, fin);
    }
}

template <class T>
void equilibrarAbb(Abb<T> &ab)
{

    if (!ab.vacio())
    {
        auto eltos = recorreAbbInorden(ab);
        equilibrarAbbRec(eltos, ab, 0, eltos.size());
    }
}

/**
 * Ejercicio 3
 * Dados dos conjuntos representados mediante árboles binarios de búsqueda,
implementa la operación unión de dos conjuntos que devuelva como resultado otro
conjunto que sea la unión de ambos, representado por un ABB equilibrado.
 */

template <class T>
void unionAbbRec(Abb<T> &abDestino, Abb<T> &abOr)
{
    if (!abOr.vacio())
    {
        abDestino.insertar(abOr.elemento());
        unionAbbRec(abDestino, abOr.izqdo());
        unionAbbRec(abDestino, abOr.drcho());
    }
}

template <class T>
Abb<T> unionAbb(Abb<T> &ab1, Abb<T> &ab2)
{
    Abb<T> abDestino = ab1;
    unionAbbRec(abDestino, ab2);
    equilibrarAbb(abDestino);
    return abDestino;
}

/**
 * Ejercicio 4 Interseccion
 * Dados dos conjuntos representados mediante árboles binarios de búsqueda,
implementa la operación intersección de dos conjuntos, que devuelva como resultado
otro conjunto que sea la intersección de ambos. El resultado debe quedar en un árbol
equilibrado.
 */

template <class T>
Abb<T> interseccionAbb(Abb<T> ab1, Abb<T> ab2)
{
    std::vector<T> v1 = recorreAbbInorden(ab1);
    std::vector<T> v2 = recorreAbbInorden(ab2);

    Abb<T> abDestino;
    std::vector<T> vInterseccion;
    for (auto i : v1)
    {
        int j = 0;
        bool bFound = false;
        while (!bFound && j < v2.size())
        {
            bFound = i == v2[j];
            j++;
        }
        if (!bFound)
            vInterseccion.push_back(i);
    }
    for (auto i : v2)
    {
        int j = 0;
        bool bFound = false;
        while (!bFound && j < v1.size())
        {
            bFound = i == v1[j];
            j++;
        }
        if (!bFound)
            vInterseccion.push_back(i);
    }

    equilibrarAbbRec(vInterseccion, abDestino, 0, v1.size() + v2.size());
    return abDestino;
}

/**
 * Practica 5 Popurri de problemas de arboles
 */

/**
 * Ejercicio 1: Dado un árbol binario de enteros donde el valor de cada nodo es menor
 * que el de sus hijos,  implementa  un  subprograma  para  eliminar  un  valor  del
 * mismo  preservando  la propiedad  de  orden  establecida.
 * Explica  razonadamente  la  elección  de  la  estructura  de datos
 */
template <class T>
void reordenaAbin(Abin<T> &abin, typename Abin<T>::nodo nd)
{
    if (nd != Abin<T>::NODO_NULO)
    {

        if (abin.elemento(abin.hijoIzqdo(nd)) != Abin<T>::NODO_NULO)
        {
            if (abin.elemento(abin.hijoIzqdo(nd)) < abin.elemento(nd))
            {
                std::swap(abin.elemento(nd), abin.elemento(abin.hijoIzqdo(nd)));
            }
        }
        if (abin.elemento(abin.hijoDrcho(nd)) != Abin<T>::NODO_NULO)
        {
            if (abin.elemento(abin.hijoDrcho(nd)) < abin.elemento(nd))
            {
                std::swap(abin.elemento(nd), abin.elemento(abin.hijoDrcho(nd)));
            }
        }
        reordenaAbin(abin, abin.hijoDrcho(nd));
        reordenaAbin(abin, abin.hijoIzqdo(nd));
    }
}

template <class T>
void eliminaElementoAbin(Abin<T> &abin, typename Abin<T>::nodo nd, const int &elemento)
{
    bool bEliminado = false;
    if (nd != Abin<T>::NODO_NULO && !bEliminado)
    {
        eliminaElementoAbin(abin, abin.hijoDrcho(nd), elemento);
        eliminaElementoAbin(abin, abin.hijoIzqdo(nd), elemento);

        // Caso el nodo a eliminar es hijo de nd
        if (abin.elemento(abin.hijoIzqdo(nd)) == elemento)
        {
            abin.eliminarhijoIzqdo(nd);
            bEliminado = true;
        }

        if (abin.elemento(abin.hijoDrcho(nd)) == elemento)
        {
            abin.eliminarhijoIzqdo(nd);
            bEliminado = true;
        }

        if (abin.elemento(nd) == elemento)
        {
            if (nd == abin.raiz())
            {
                abin.eliminarraiz();
                bEliminado = true;
            }
            else
            {
                auto nodoPadre = abin.padre(nd);
                if (abin.hijoDrcho(nodoPadre) == nd)
                {
                    abin.eliminarhijoDrcho(nodoPadre);
                    bEliminado = true;
                }
                if (abin.hijoIzqdo(nodoPadre) == nd)
                {
                    abin.eliminarhijoIzqdo(nodoPadre);
                    bEliminado = true;
                }
            }
        }
    }
    if (bEliminado)
        reordenaAbin(abin, abin.raiz());
}

/**
 * Primer Parcial EDNL 2022
 * Dado un árbol binario de un tipo genérico T calcular el número de nodos que siendo hermanos entre
 * sí tienen misma raíz y sus subárboles son reflejados (respecto a sus elementos)
 */

template <class T>
bool sonReflejados(Abin<T> abin, typename Abin<T>::nodo n1, typename Abin<T>::nodo n2) //! La clave esta en comprobar los nodos actuales y sus subarboles a la vez.
{
    // Base case: If both trees are empty, they are mirrors
    if (n1 == Abin<T>::NODO_NULO && n2 == Abin<T>::NODO_NULO)
        return true;

    // If only one tree is empty, they are not mirrors
    if (n1 == Abin<T>::NODO_NULO || n2 == Abin<T>::NODO_NULO)
        return false;

    // If both trees are not empty, they are mirrors if:
    // 1: The roots contain the same value
    // 2: The right subtree of the first tree is mirror of the left subtree of the second tree
    // 3: The left subtree of the first tree is mirror of the right subtree of the second tree
    return (abin.elemento(n1) == abin.elemento(n2) &&
            sonReflejados(abin, abin.hijoIzqdo(n1), abin.hijoDrcho(n2)) &&
            sonReflejados(abin, abin.hijoDrcho(n1), abin.hijoIzqdo(n2)));
}

template <class T>
void cuentaReflejadosRec(Abin<T> abin, typename Abin<T>::nodo nd, int &iReflejados)
{
    if (nd != Abin<T>::NODO_NULO)
    {
        if (sonReflejados(abin, abin.hijoIzqdo(nd), abin.hijoDrcho(nd)))
            iReflejados += 2;
        cuentaReflejadosRec(abin, abin.hijoDrcho(nd), iReflejados);
        cuentaReflejadosRec(abin, abin.hijoIzqdo(nd), iReflejados);
    }
}

template <class T>
int cuentaNodosReflejados(Abin<T> abin, typename Abin<T>::nodo nd)
{
    if (abin.arbolVacio())
        return 0;
    else
    {
        int iReflejados = 0;
        cuentaReflejadosRec(abin, abin.raiz(), iReflejados);
        return iReflejados;
    }
}

/**
 * Examen Septiembre 2022
 * Construye una función que, dado un Árbol Binario, devuelva true si es un AVL y false en el caso contrario
 */

// Un avl: es un abb con un factor de desequilibrio de valor absoluto 0 o 1

// Un abb es abin solo que hijo izquierdo < padre < hijoDerecho

template <class T>
bool abinEsAbb(Abin<T> &abin, typename Abin<T>::nodo nd)
{
    bool bCumplePropiedad = true;
    if (nd != Abin<T>::NODO_NULO && bCumplePropiedad)
    {
        if (abin.hijoDrcho(nd) != Abin<T>::NODO_NULO)
        {
            bCumplePropiedad = abin.elemento(nd) < abin.elemento(abin.hijoDrcho(nd));
        }
        if (abin.hijoIzqdo(nd) != Abin<T>::NODO_NULO)
        {
            bCumplePropiedad = abin.elemento(nd) > abin.elemento(abin.hijoIzqdo(nd));
        }
        return bCumplePropiedad && abinEsAbb(abin, abin.hijoDrcho(nd)) && abinEsAbb(abin, abin.hijoIzqdo(nd));
    }
    else
    {
        return bCumplePropiedad;
    }
}

// Desequilibrio: maxima diferencias entre las alturas del nodo

template <class T>
int alturaNodoAbin(Abin<T> abin, typename Abin<T>::nodo nd)
{
    if (nd == Abin<T>::NODO_NULO)
    {
        return -1;
    }
    else
    {
        return 1 + std::max(alturaNodoAbin(abin, abin.hijoDrcho(nd)), alturaNodoAbin(abin, abin.hijoIzqdo(nd)));
    }
}

template <class T>
int difAlturaAbin(Abin<T> abin, typename Abin<T>::nodo nd)
{
    return std::abs(alturaNodoAbin(abin, abin.hijoIzqdo(nd)), alturaNodoAbin(abin, abin.hijoDrcho(nd)));
}

template <class T>
int desequilibrioAbinRec(Abin<T> abin, typename Abin<T>::nodo nd)
{
    if (nd == Abin<T>::NODO_NULO)
    {
        return 0;
    }
    else
    {
        return std::max(difAlturaAbin(abin, nd), difAlturaAbin(abin, abin.hijoIzqdo(nd)), difAlturaAbin(abin, abin.hijoDrcho(nd)));
    }
}

// COMPROBAR DESEQUILIBRIO Y CUERPO DE LA FUNCION

template <class T>
bool compruebaDesequilibrio(Abin<T> abin, typename Abin<T>::nodo nd)
{
    if (nd == Abin<T>::NODO_NULO)
    {
        return true;
    }
    else
    {
        int iDesequilibrioNodo = desequilibrioAbinRec(abin, nd);

        return (desequilibrioAbin == 0 || iDesequilibrioNodo == 1) && compruebaDesequilibrio(abin, abin.hijoIzqdo(nd)) && compruebaDesequilibrio(abin, abin.hijoDrcho(nd));
    }
}

template <class T>
bool abinEsAVL(Abin<T> abin)
{
    if (abin.arbolVacio())
        return true;
    else
        return abinEsAbb(abin, abin.raiz()) && compruebaDesequilibrio(abin, abin.raiz()); // Comprobamos que se cumplan ambos casos
}

int main()
{
    Agen<int> A;
    A.insertaRaiz(1);
    A.insertarHijoIzqdo(A.raiz(), 2);
    A.insertarHermDrcho(A.hijoIzqdo(A.raiz()), 3);
    auto n = A.hermDrcho(A.hijoIzqdo(A.raiz()));
    A.insertarHijoIzqdo(A.hijoIzqdo(A.raiz()), 39);
    auto n2 = A.hijoIzqdo(A.hijoIzqdo(A.raiz()));

    // insertamos 4 hermanos
    for (int i = 4; i < 7; ++i)
        A.insertarHermDrcho(n, i);
    n = A.hermDrcho(n);

    for (int i = 9; i < 15; ++i)
        A.insertarHermDrcho(n2, i);
    n2 = A.hermDrcho(n2);

    Abin<char> abin;
    abin.insertaRaiz('a');
    abin.insertarhijoIzqdo(abin.raiz(), 'b');
    abin.insertarhijoDrcho(abin.raiz(), 'b');

    abin.insertarhijoIzqdo(abin.hijoIzqdo(abin.raiz()), 'c');

    return 0;
}
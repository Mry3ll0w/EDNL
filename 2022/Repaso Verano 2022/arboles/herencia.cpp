#include <iostream>
#include "Agen.h"
using namespace std;//Avoid using std:: ....

struct heredero{
    double dinero;
    bool muerto;
    heredero(const double& d = 100, const bool& m = false ):muerto(m), dinero(d){}
    
    /**
     * @brief Mata al hereder, pone su dinero a 0 y el booleano a true 
     * */
    void matar(){
        dinero = 0;
        muerto = true;
    }

};

/**
 * @brief Cuenta el numero de nodos vivos en el subarbol del nodo dado
 * @param const Agen<heredero> A,  Agen<heredero>::nodo n
 * @return void
 */
void cuenta_vivos( Agen<heredero>::nodo n, const Agen<heredero> &A, int& vivos)
{

    if (n != Agen<heredero>::NODO_NULO)
    {

         Agen<heredero>::nodo hijo = A.hijoIzqdo(n); // Comenzamos con el hijo izq

        while (hijo != Agen<heredero>::NODO_NULO)
        { // Procesamos los hermanos derechos
            cuenta_vivos(hijo, A,vivos);
            hijo = A.hermDrcho(hijo);
        }
        //Contamos el numero de 
        if(!A.elemento(n).muerto){
            vivos ++;
        }

    }

}

/**
 * @brief Reparte la herencia entre el nodo y mata al nodo dado
 *
 * @param const  Agen<heredero>::nodo n_muerto,
     Agen<heredero>::nodo n, Agen<heredero>A, const int& nodos_vivos
 *
 * @return none (void)
 */
void reparte_herencia(const  Agen<heredero>::nodo n_muerto, 
     Agen<heredero>::nodo n, Agen<heredero>A, const int& nodos_vivos)
{
    if (n != Agen<heredero>::NODO_NULO)
    {

         Agen<heredero>::nodo hijo = A.hijoIzqdo(n); // Comenzamos con el hijo izq

        while (hijo != Agen<heredero>::NODO_NULO)
        { // Procesamos los hermanos derechos
            reparte_herencia(n_muerto,hijo, A, nodos_vivos);
            hijo = A.hermDrcho(hijo);
        }
        // Contamos el numero de
        if (!A.elemento(n).muerto)
        {
            A.elemento(n).dinero += A.elemento(n_muerto).dinero/nodos_vivos;
        }

    }
}

/**
 * @brief Algoritmo principal para repartir la herencia del nodo dado
 * @param const  Agen<heredero>::nodo n_muerto,  Agen<heredero>::nodo n ,
    Agen<heredero>& A
 * @return none(void)
 */
void herencia(const  Agen<heredero>::nodo n_muerto,  Agen<heredero>::nodo n ,
    Agen<heredero>& A)
{
    int nodos_vivos = 0;
    
    cuenta_vivos(n_muerto, A, nodos_vivos);

    reparte_herencia(n_muerto, n_muerto, A, nodos_vivos);
    //Tras hacer la reparticion de la herencia matamos al nodo
    A.elemento(n_muerto).matar();

}

    int main()
{

    return 0;
}
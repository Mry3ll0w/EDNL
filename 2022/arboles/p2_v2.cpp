#include <iostream>
#include "arbolbinenla.h"
using namespace std;//Avoid using std:: ....

template<class t>
bool similares(Abin<t>&A, Abin<t>&B);

int main(){
    Abin<int> a,b;
    a.insertaRaiz(1);
    b.insertaRaiz(1);

    a.insertarhijoDrcho(a.raiz(),2);
    b.insertarhijoDrcho(b.raiz(),2);

    std::cout<< similares(a,b)<<std::endl;

return 0;
}

template<class t>
bool similares_rec(typename Abin<t>::nodo na, typename Abin<t>::nodo nb, Abin<t>& A,Abin<t>& B){
    if (na== Abin<t>::NODO_NULO && nb != Abin<t>::NODO_NULO)
    {
        return true;
    }
    
    //Caso distinción estructural de los hijos derechos de ambos árboles
    if 
    (
        (A.hijoDrcho(na) != Abin<t>::NODO_NULO && B.hijoDrcho(nb) == Abin<t>::NODO_NULO)
        ||
        (A.hijoDrcho(na) == Abin<t>::NODO_NULO && B.hijoDrcho(nb) != Abin<t>::NODO_NULO)    
    )
    {
        return false;
    }

    //Caso distinción estructural de los hijos izquierdos
    else if
    (
        (A.hijoIzqdo(na) != Abin<t>::NODO_NULO && B.hijoDrcho(nb)==Abin<t>::NODO_NULO)
        ||
        (A.hijoIzqdo(na) == Abin<t>::NODO_NULO && B.hijoDrcho(nb)!=Abin<t>::NODO_NULO)
    )
    {
        return false;
    }
    else{

        return similares_rec(A.hijoIzqdo(na), B.hijoIzqdo(na),A,B)&& similares_rec(A.hijoDrcho(na),B.hijoDrcho(na),A,B);

    }
    
}

template<class t>
bool similares(Abin<t>&A, Abin<t>&B)
{
    return similares_rec(A.raiz(),B.raiz(),A,B);
}
#include <iostream>
#include "arbolbinenla.h"
using namespace std;//Avoid using std:: ....

template<class t>
bool similares(Abin<t>&A, Abin<t>&B);

int main(){
    Abin<int> a,b;
    a.insertarRaizB(1);
    b.insertarRaizB(1);

    a.insertarHijoDrchoB(a.raizB(),2);
    b.insertarHijoDrchoB(b.raizB(),2);

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
        (A.hijoDrchoB(na) != Abin<t>::NODO_NULO && B.hijoDrchoB(nb) == Abin<t>::NODO_NULO)
        ||
        (A.hijoDrchoB(na) == Abin<t>::NODO_NULO && B.hijoDrchoB(nb) != Abin<t>::NODO_NULO)    
    )
    {
        return false;
    }

    //Caso distinción estructural de los hijos izquierdos
    else if
    (
        (A.hijoIzqdoB(na) != Abin<t>::NODO_NULO && B.hijoDrchoB(nb)==Abin<t>::NODO_NULO)
        ||
        (A.hijoIzqdoB(na) == Abin<t>::NODO_NULO && B.hijoDrchoB(nb)!=Abin<t>::NODO_NULO)
    )
    {
        return false;
    }
    else{

        return similares_rec(A.hijoIzqdoB(na), B.hijoIzqdoB(na),A,B)&& similares_rec(A.hijoDrchoB(na),B.hijoDrchoB(na),A,B);

    }
    
}

template<class t>
bool similares(Abin<t>&A, Abin<t>&B)
{
    return similares_rec(A.raizB(),B.raizB(),A,B);
}
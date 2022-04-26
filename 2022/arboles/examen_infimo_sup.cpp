#include <iostream>
#include <limits>
#include "abb.h"

template<class t>
t maximo_rec(Abb<t>A);

template<class t>
t minimo_rec(Abb<t>A);

template<class t>
void infimo_rec(Abb<t>A, t& infimo, const t x);

template<class t>
void supremo_rec(Abb<t>A,const t x,  t& supremo);

template <class t>
void infimo_supremo(Abb<t>& A,  t& x);

int main(){
    Abb<int> a;
    a.insertar(12);
    a.insertar(7);
    a.insertar(123);
    a.insertar(1);
    int x =7;
    infimo_supremo(a,x);

return 0;
}

//Nos piden encontrar el infimo y el supremo, en caso de no existir se deben devolver el elemento
//minimo para el infimo y el maximo para el supremo

//Para obtener el maximo deberemos acudir al elemento mas a la derecha, ya que por propiedad de los Abb
//el elemento hoja mas a la derecha será el mas grande del arbol
template<class t>
t maximo_rec(Abb<t>A){

    if (A.drcho().vacio())//Bajamos hasta que se llegue a una hoja por la derecha
    {
        return A.elemento();//Devolvemos el maximo
    }
    
    return maximo_rec(A.drcho());
}

//Se realiza de forma análoga al maximo, solo que en este caso debemos observar únicamente la rama izquierda
template<class t>
t minimo_rec(Abb<t>A){
    //Bajamos hasta una hoja
    if (A.izqdo().vacio())
    {
        return A.elemento();
    }

    return minimo_rec(A.izqdo());
}

//se define el inifimo de un numero como el numero <= x
//ej 4 5 6 12 23, si x = 6 el infimo es el mayor de los menores, inf = 5
template<class t>
void infimo_rec(Abb<t>A, t& infimo, t x){

    if(!A.vacio()){
        
        if (A.elemento() == x )
        {
            infimo=x;
        }
        else if(A.elemento() < x){
            
            if(infimo < A.elemento()){
                infimo = A.elemento();
            }

        }
        
        infimo_rec(A.izqdo(),infimo,x);   
        infimo_rec(A.drcho(),infimo,x); 
    }

}

template<class t>
void supremo_rec(Abb<t>A,const t x,  t& supremo){
    if(!A.vacio()){
        
        if (A.elemento() == x )
        {
            supremo=x;
        }
        else if(A.elemento() > x){
            
            if(supremo > A.elemento()){
                supremo = A.elemento();
            }

        }
        
        infimo_rec(A.izqdo(),supremo,x);   
        infimo_rec(A.drcho(),supremo,x);   
    }
}

template <class t>
void infimo_supremo(Abb<t>& A, t& x){

    t infimo=std::numeric_limits<t>::max();
    t supremo= std::numeric_limits<t>::min();

    infimo_rec(A,infimo,x);
    supremo_rec(A,supremo,x);

    //si supremo/minimo no han variado su valor devuelve el maximo/minimo del arbol
    if (infimo == std::numeric_limits<t>::max())
    {
        infimo = minimo_rec(A);
    }
    else if(supremo == std::numeric_limits<t>::min()){
        supremo = maximo_rec(A);
    }

    std::cout<<"El infimo: "<<infimo<<"\t Supremo: "<<supremo<<std::endl;    
}
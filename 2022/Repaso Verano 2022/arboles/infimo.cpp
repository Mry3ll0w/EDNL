#include <iostream>
#include "abb.h"
using namespace std;//Avoid using std:: ....

template<class T>
void infimo_rec(const Abb<T> &A,const T& x, T& inf, T& min ){
    if(!A.vacio()){

        if(A.elemento() < x){
            
            //ACTUALIZAMOS EL MINIMO
            if(min > A.elemento())
                min = A.elemento();
            
            //ACTUALIZAMOS EL INFIMO
            if(inf < A.elemento()){
                inf = A.elemento();
            }

            //Nos hundimos en el arbol
            //infimo_rec(A.izqdo(), x, inf, min);
            infimo_rec(A.drcho(), x, inf,min);
        }
        else{//Hemos descartado ya que sean iguales por tanto es mayor
            
            //Actualizamos el minimo
            if(A.elemento() < min ){
                min = A.elemento();
            }
            infimo_rec(A.izqdo(),x,inf,min);
        }

    }
}



template<class T>
const T infimo(const Abb<T>&A, const T& x){
    auto a = A.buscar(x);
    if(!a.vacio()){
        return a.elemento();
    }
    else{
        T minimo = A.elemento();
        T infimo = -1;
        
        infimo_rec(A,x,infimo, minimo);

        //Llamo a infimo, en caso de no existir uno no se actualiza.
        if(infimo == -1){
            return minimo;
        }
        else
            return infimo;

    }
} 

/**
 * @brief Calcula el Supremo del arbol
 * 
 * @param const Abb<T> &A, T& supremo, T& maximo
 * 
 * @return T
 */
template <class T>
void supremo_rec(const Abb<T> &A, const T &x, T &sup, T &max)
{
    if (!A.vacio())
    {
        if (A.elemento() > x)
        {

            // ACTUALIZAMOS EL maximo
            if (max < A.elemento())
                max = A.elemento();

            // ACTUALIZAMOS EL supremo
            if (sup < A.elemento())
            {
                sup = A.elemento();
            }

            // Nos hundimos en el arbol
            supremo_rec(A.izqdo(), x, sup, max);
            supremo_rec(A.drcho(), x, sup, max);
        }
        else
        { // Hemos descartado ya que sean iguales por tanto es menor

            // Actualizamos el minimo
            if (A.elemento() > max)
            {
                max = A.elemento();
            }

            supremo_rec(A.izqdo(), x, sup, max);
        }
    }
}
template <class T>
T supremo(const Abb<T>& A, const T& x){
    auto t = A.buscar(x);
    if(!A.vacio()){

        T max = A.elemento();
        T sup = 99999;

        supremo_rec(A,x,sup,max);
        //cout<<sup<<endl;
        if(sup == 99999){
            return max;
        }
        else
            return sup;
    }
    else
        return x;
}

int main(){

    Abb<int> A;
    A.insertar(7);
    A.insertar(8);
    A.insertar(11);
    A.insertar(1);
    A.insertar(4);
    A.insertar(3);
    A.insertar(89);
    
    cout<< "Valor supremo: " << supremo(A,10)<<endl;
    
return 0;
}
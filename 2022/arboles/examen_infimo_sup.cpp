#include <iostream>
#include "abb.h"
using namespace std;//Avoid using std:: ....

//cabeceras wuolah
template<class T>
void supremo_rec(const Abb<T>& arbol,T& x, T& sup,T& max){
if(!arbol.vacio()){
    if(arbol.elemento()==x){
        sup = x;
    }
    if(arbol.elemento()>x){
        
        if(arbol.elemento()>max)
            max=arbol.elemento();

        if(sup>arbol.elemento()){
            sup=arbol.elemento();
        }

        supremo_rec(arbol.izqdo(),x,sup,max);
        supremo_rec(arbol.drcho(),x,sup,max);
    }
        if(arbol.elemento()<x){
            if(arbol.elemento()>max)
                max=arbol.elemento();

            supremo_rec(arbol.izqdo(),x,sup,max);
        }
}
}

template<class T>
T supremo(Abb<T>& arbol,T & x){
    T sup=9999;
    T max=arbol.elemento();
    supremo_rec(arbol,x,sup,max);

    if(sup==9999)
        return max;
    else
        return sup;
}

template<class T>
void infimo_rec(const Abb<T>& arbol,T& x, T& inf,T& min){
    if(!arbol.vacio()){
        if(arbol.elemento()==x){
            inf = x;
        }
        if(arbol.elemento()<x){
            if(arbol.elemento()<min)
                min=arbol.elemento();
                if(inf<arbol.elemento()){
                    inf=arbol.elemento();
                    //cout<<"Cambio de infimo,vale:"<<inf<<endl;
                }
                infimo_rec(arbol.izqdo(),x,inf,min);
                infimo_rec(arbol.drcho(),x,inf,min);
        }
        if(arbol.elemento()>x){
            if(arbol.elemento()<min)
                min=arbol.elemento();
        infimo_rec(arbol.izqdo(),x,inf,min);
        }
    }
}

template<class T>
T infimo(Abb<T>& arbol,T & x){
    T inf=-1;
    T min=arbol.elemento();
    infimo_rec(arbol,x,inf,min);
    if(inf==-1){
        return min;
    }
    else
        return inf;
}


int main(){
Abb<int> arbol;
arbol.insertar(5);

arbol.insertar(1);
arbol.insertar(3);
arbol.insertar(2);
arbol.insertar(8);
arbol.insertar(9);
// equilibrar(arbol);
int x=4;
cout<<"El supremo es "<<supremo(arbol,x);
cout<<"El infimo es: "<<infimo(arbol,x)<<endl;

return 0;
}
#include <iostream>
#include "abb.h"

template<class t>
t maximo_rec(Abb<t>A);

int main(){
    Abb<int> a;
    a.insertar(12);
    a.insertar(7);
    a.insertar(123);
    a.insertar(1);

    std::cout<<maximo_rec(a)<<std::endl;

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

    return minimo_rec(A.izqdo()));
}
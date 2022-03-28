#include <iostream>
#include "arbolbinenla.h"
using namespace std;//Avoid using std:: ....

template<class t>
typename Abin<t>::NODO_NULO NULO;//No escribir toda la llamada 



int main(){
    
return 0;
}

/*
Dado un árbol binario, calcular el número de nodos que tienen exactamente 3 nietos.
Si necesitamos conocer el número total de nodos que tienen 3 nietos, el nodo en el 
que me encuentro situada debe tener obligatoriamente dos hijos, para que la suma de 
los hijos de ellos sea 3. Esta sería la primera condición que debería cumplirse para 
poder obtener el resultado deseado.
Luego, se ha comprobar si de esos hijos (el hijo izquierdo y el hijo derecho del nodo 
en el que estoy) al menos uno tiene sí o sí dos hijos. Si esta condición se cumple, 
solo nos quedaría comprobar si el otro hijo tiene solamente un hijo, para que la suma sea 3.
*/

//hay que restarle uno al conteo ya que mete la raiz y ademas restarle 2 ya que se cuentan los nietos solo
template<class t>
bool tiene_3_nietos(typename Abin<t>::nodo n, const Abin<t>&A){

    

    //Tenemos que comprobar en primer caso si tiene 2 descendientes directos 
    if 
    (
        //Comprobamos que al menos uno de los hijos tenga un descendiente
        A.hijoDrchoB(n) = NULO && A.hijoDrchoB(n) = NULO 
        &&
        //Comprobacion nietos
        (

            //1) Hijo izquierdo
            (
                A.hijoIzqdoB(A.hjoIzqdoB(n))!=  NULO && A.hijoDrchoB(A.hjoIzqdoB(n))== NULO 
                ||
                A.hijoIzqdoB(A.hjoIzqdoB(n))==  NULO && A.hijoDrchoB(A.hjoIzqdoB(n))!= NULO
            )
        
            ||

            //2) Hijo Derecho
            (
                A.hijoDrchoB(A.hjoDrchoB(n))== NULO && A.hijoIzqdoB(A.hjoDrchoB(n))!= NULO
                ||
                A.hijoDrchoB(A.hjoDrchoB(n))!= NULO && A.hijoIzqdoB(A.hjoDrchoB(n))== NULO
            
            )
        
        )
    )
    {
      return true;  
    }
    else
        return false;
    

}

//simplemente recorremos el arbol que nos den, para asi comprobar cualquier nodo dado
template<class t>
int cuenta_3_nietos_rec(typename Abin<t>::nodo n,const Abin<t>&A){

    if ( n == NULO )//Base 
    {
    
        return 0;

    }
    else//general
    {

        if (tiene_3_nietos(n,A))
        {
            return 1 + cuenta_3_nietos(A.hijoIzqdoB(n),A) + cuenta_3_nietos(A.hijoDrchoB(n),A);
        }
        else
            return cuenta_3_nietos(A.hijoIzqdoB(n),A) + cuenta_3_nietos(A.hijoDrchoB(n),A);
        
    }
    

}


template <class t> 
int numero_3_nietos(const Abin<t>&A)
{
    return cuenta_3_nietos_rec(A.raizB(),A);
}
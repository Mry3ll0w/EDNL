#include <iostream>
#include "arbolbinenla.h"
using namespace std;//Avoid using std:: ....

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
bool es_verde(typename Abin<t>::nodo n, const Abin<t>&a){

    typename Abin<t>::NODO_NULO NULO;

    //Tenemos que comprobar en primer caso si tiene 2 descendientes directos 
    if 
    (
        //Comprobamos que al menos uno de los hijos tenga un descendiente
        a.hijoDrchoB(n) != NULO && a.hijoDrchoB(n) != NULO 
        &&
        //Comprobacion nietos
        (

            //1) Hijo izquierdo
            (
                a.hijoIzqdoB(a.hijoIzqdoB(n)) !=  NULO && a.hijoDrchoB(a.hijoIzqdoB(n)) == NULO 
                || 
                a.hijoIzqdoB(a.hijoIzqdoB(n)) ==  NULO && a.hijoDrchoB(a.hijoIzqdoB(n)) != NULO
            )
        
            ||

            //2) Hijo Derecho
            (
                a.hijoDrchoB(a.hijoDrchoB(n)) == NULO && a.hijoIzqdoB(a.hijoDrchoB(n)) != NULO
                ||
                a.hijoDrchoB(a.hijoDrchoB(n)) != NULO && a.hijoIzqdoB(a.hijoDrchoB(n)) == NULO
            
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
int cuenta_verdes(const Abin<t>&a, typename Abin<t>::nodo n){

    if ( n != Abin<t>::NODO_NULO )
    {
        
        if (es_verde(a, n))
        {
            return 1 + cuenta_verdes(a, a.hijoIzqdoB(n)) + cuenta_verdes(a, a.hijoDrchoB(n));
        }
        else
            return cuenta_verdes(a, a.hijoIzqdoB(n)) + cuenta_verdes(a, a.hijoDrchoB(n));
        

    }
    

}

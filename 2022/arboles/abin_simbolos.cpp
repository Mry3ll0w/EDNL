#include <iostream>
#include <cassert>
#include <string>
#include "arbolbinenla.h"
using namespace std;//Avoid using std:: ....

struct expresion {

    bool valor_verdad;
    string expr;
    expresion(string ex, bool v=false):expr(ex),valor_verdad(v){}

};
bool procesa_expression(Abin<expresion>& a);

int main(){
    
    expresion s1("s1",true), s2("s2",false), s3("s3",true), Y("&&"),OR("||"),NOT("not");

    Abin<expresion>a;
    
    a.insertaRaiz(Y);
    a.insertarhijoDrcho(a.raiz(),s1);
    a.insertarhijoDrcho(a.raiz(),s2);

    std::cout << procesa_expression(a) << std::endl;

return 0;
}

//* Para crear el arbol necesitaremos una estructura para almacenar:
//* Expresion ==> S1, S2, .. o expresiones logicas && || NO
//* En caso de ser una espresión Si que valor de verdad tiene



//Recibe un arbol con una expresion CORRECTA para evaluar
bool procesa_expresion_rec(typename Abin<expresion>::nodo n, Abin<expresion>& a){
    
    if (a.hijoIzqdo(n)!=Abin<expresion>::NODO_NULO){
        //Evaluar las expresiones
        if (a.elemento(n).expr == "&&")
        {
            return procesa_expresion_rec(a.hijoIzqdo(n),a) and procesa_expresion_rec(a.hijoDrcho(n),a);
        }
        else if (a.elemento(n).expr == "||")
        {
            return procesa_expresion_rec(a.hijoIzqdo(n),a) or procesa_expresion_rec(a.hijoDrcho(n),a);
        }
        else if (a.elemento(n).expr == "NO")
        {
            return not procesa_expresion_rec(a.hijoIzqdo(n),a);//Asumimos que la negacion solo se aplicará al hijo izquierdo
        }
    
    }
    else{
        return a.elemento(n).valor_verdad;
    }
    

}

bool procesa_expression(Abin<expresion>& a){
    return procesa_expresion_rec(a.raiz(),a);
}
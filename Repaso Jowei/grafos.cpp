#include <iostream>
#include "../2023/grafos/libGrafos/alg_grafoPMC.h"
using namespace std; // Avoid using std:: ....

/**
 * INDICACIONES BASICAS:
 *
 * 1) MIRAR MUY BIEN EL ENUNCIADO ==> Datos que me dan, caso laberinto EJEMPLO CLARO
 *  EJ: Laberinto de NXN ==> grafo de nxn ==> matriz de costes/adyacencia ==> n2 x n2
 *
 * 2) OBJETIVO DE LA PREGUNTA
 *      a) Te piden ir de A -> B, caminos minimos ==> Dijsktra ==> Laberinto, Reparto, Viajero Alergico
 *      b) Implica conocer todos los caminos ==> Floyd
 *
 * 3) RESULTADO de pregunta
 *
 *
 * Matriz de costes ==> Indica CUANTO vale ir de A -> B
 * Matriz de Adyacencia ==> Indica SI ESTA CONECTADO , ¿Es posible ir de A -> B?
 *
 * A ----------> B
 * ^
 * |
 * |
 * C
 *    A     B      C
 * A  1     1      0
 *
 * B  0     1      0
 *
 * C  1     0      1
 *
 * Lista de Adyacencia del mismo grafo anterior =>= Mas sencilla detectar adyacentes
 * { A , B, C}
 *
 * A => {B}
 * B => {}
 * C => {A}
 */

// Preguntar Ej3 practica 2 de grafos a Paco cuando empieza y cuando acaba.

int main()
{

    return 0;
}
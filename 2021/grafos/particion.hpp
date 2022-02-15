#ifndef PARTICION_H
#define PARTICION_H
#include<iostream>
#include <vector>

class Particion {
    public:
        Particion(int n): padre(n, -1) {}
        void unir(int a, int b);
        int encontrar(int x) const;
        int mostrar() const;
        void mostrarVector() const;
        int tam(){return padre.size();}
    private:
        mutable std::vector<int> padre;
};


void Particion::unir(int a, int b) //une los elementos a y b y sus subarboles 
{
    // El árbol con mayor altura se convierte en subárbol del otro.
    if (padre[b] < padre[a])
        padre[a] = b;
    else {
        if (padre[a] == padre[b])
            padre[a]--; // El árbol resultante tiene un nivel más.
        padre[b] = a;
    }
}
int Particion::encontrar(int x) const //devuelve la posicion del subarbol donde se encuentra x
{
    int y, raiz = x;

    while (padre[raiz] > -1)
        raiz = padre[raiz];
    // Compresión del camino de x a raíz: Los nodos
    // del camino se hacen hijos de la raíz.
    while (padre[x] > -1) {
        y = padre[x];
        padre[x] = raiz;
        x = y;
    }
    return raiz;
}
/*
Vector padre

 0   1   2   3   4
(-1)(-1)(-1)(-1)(-1)

     a b
unir(0,1)

0   1   2   3   4
(-2)(0)(-1)(-1)(-1)

     a b
unir(3,4)

0   1   2   3   4
(-2)(0)(-1)(-2)(3)

unir(0,3)
0   1   2   3   4
(-3)(0)(-1)(0)(3)



*/

int Particion::mostrar() const
{
    int cont=0; //cuenta el numero de conjuntos
    //int niveles=-1;
    //int father;
    std::vector<bool> visitados(padre.size(), false);
    for(size_t i=0;i<padre.size();++i)
        std::cout << "(" << padre[i] << ")";
    std::cout << std::endl;
    for(size_t i=0;i<padre.size();++i){
        std::cout << "posicion " << i << ":";
        if(padre[i]<0)
        {
            std::cout << i << " ";
            ++cont;
        }
        for(size_t j=0;j<padre.size();++j)
        {
                if(padre[j]==i)
                {
                    if(padre[i]<0)
                        std::cout << j << " ";
                    else
                    {
                        int aux=padre[j];
                        if(aux>=0)
                        {
                            while(padre[aux]>=0)
                                aux=padre[aux];
                            if(aux==i)
                                std::cout << j << " ";
                        }
                    }
                }
                else
                {
                    int aux=padre[j];
                    if(aux>=0)
                    {
                        while(padre[aux]>=0)
                            aux=padre[aux];
                        if(aux==i)
                            std::cout << j << " ";
                    }
                }
        }
        std::cout << std::endl;
    }
    return cont;
}

void Particion::mostrarVector() const
{
    for(size_t i=0;i<padre.size();++i)
    {
        if(padre[i]<0)
            std::cout << "[ " << i << "]";
        else
            std::cout << "[" << i << "]";
    }
    std::cout << std::endl;    
    for(size_t i=0;i<padre.size();++i)
        std::cout << "(" << padre[i] << ")";
    std::cout << std::endl; 
}
#endif // PARTICION_H

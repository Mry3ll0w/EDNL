#ifndef MATRIZ_HPP_
#define MATRIZ_HPP_
#include<vector>
#include<iostream>
#include "Grafo.hpp"
template <typename T> class matriz {
    public:
        matriz() {}
        explicit matriz(size_t n, const T& x = T()): m(n, std::vector<T>(n, x)) {}
        size_t dimension() const { return m.size(); }
        const std::vector<T>& operator [](size_t i) const { return m[i]; }
        std::vector<T>& operator [](size_t i) { return m[i]; }
    private:
        std::vector<std::vector<T>> m;
};
template<typename T>
std::ostream& operator<<(std::ostream& os,const matriz<T>& m)
{
    for(typename GrafoP<T>::vertice i=0;i<m.dimension();++i){
        for (typename GrafoP<T>::vertice j=0;j<m.dimension();++j){
            if(m[i][j]==GrafoP<T>::INFINITO)
                os << " ~ ";
            else
                os << m[i][j] << " ";
            }
        os << std::endl;
    }
    return os;
}
std::ostream& operator<<(std::ostream& os,const matriz<bool>& m)
{
    for(typename Grafo::vertice i=0;i<m.dimension();++i){
        for (typename Grafo::vertice j=0;j<m.dimension();++j){
            if(m[i][j]==true)
                os << " 1 ";
            else
                os << " 0 ";
            }
        os << std::endl;
    }
    return os;
}
template<typename T> void mostrar_matriz(const matriz<T>& m)
{
    for(size_t i=0;i<m.dimension();++i)
    {
        for(size_t j=0;j<m.dimension();++j)
        {
            if (m[i][j])
                std::cout << " T ";
            else
                std::cout << " F ";
        }
        std::cout<<std::endl;
    }
}

#endif

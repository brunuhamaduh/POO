#include "Coordenadas.h"
#include "Terminal.h"
#include <random>
#include <algorithm>

Coordenadas::Coordenadas(const int &x, const int &y)
{
    this->x = x;
    this->y = y;
}
Coordenadas::Coordenadas()
{
    std::random_device random;
    std::mt19937 generator(random());
    std::uniform_int_distribution <> distr(0, 100);
    x = distr(generator);
    y = distr(generator);
}
Coordenadas::~Coordenadas() = default;
int Coordenadas::getX() const {return x;}
int Coordenadas::getY() const {return y;}
#ifndef POO_COORDENADAS_H
#define POO_COORDENADAS_H
#include <vector>
#include "Terminal.h"

class Coordenadas
{
    int x, y;
public:
    Coordenadas(const int &x, const int &y);
    Coordenadas();
    ~Coordenadas();
    int getX() const;
    int getY() const;
    friend term::Window & operator<<(term::Window & o, const Coordenadas &coordenadas);
};

term::Window & operator<<(term::Window & o, const Coordenadas &coordenadas);
term::Window & operator<<(term::Window & o, const std::vector<Coordenadas> &n);

#endif //POO_COORDENADAS_H

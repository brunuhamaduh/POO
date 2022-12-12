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
};

#endif //POO_COORDENADAS_H

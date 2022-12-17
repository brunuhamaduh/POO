#ifndef POO_COORDENADAS_H
#define POO_COORDENADAS_H
#include <vector>
#include "Terminal.h"

class Coordenadas
{
    int x, y;
public:
    Coordenadas(const int &x, const int &y);
    ~Coordenadas();
    int getX() const;
    int getY() const;
    void setX(const int &num);
    void setY(const int &num);
    void setPos(int &direction, int &num, const int &tamanho);
};

#endif //POO_COORDENADAS_H

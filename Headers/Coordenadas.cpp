#include "Coordenadas.h"
#include "Terminal.h"
#include <random>
#include <algorithm>

Coordenadas::Coordenadas(const int &x, const int &y)
{
    this->x = x;
    this->y = y;
}
Coordenadas::~Coordenadas() = default;
int Coordenadas::getX() const {return x;}
int Coordenadas::getY() const {return y;}
void Coordenadas::setPos(int &direction, int &num, const int &tamanho)
{
    while(true)
    {
        if(direction == 1) //UP
        {
            if(y - num >= 0)
            {
                y = y - num;
                break;
            }
        }

        else if(direction == 2) //UPRIGHT
        {
            if(y - num >= 0 && x + num <= tamanho)
            {
                x = x + num;
                y = y - num;
                break;
            }
        }

        else if(direction == 3) //RIGHT
        {
            if(x + num <= tamanho)
            {
                x = x + num;
                break;
            }
        }

        else if(direction == 4) //DOWNRIGHT
        {
            if(y + num <= tamanho && x + num <= tamanho)
            {
                x = x + num;
                y = y + num;
                break;
            }
        }

        else if(direction == 5) //DOWN
        {
            if(y + num <= tamanho)
            {
                y = y + num;
                break;
            }
        }

        else if(direction == 6) //DOWNLEFT
        {
            if(y + num <= tamanho && x - num >= 0)
            {
                x = x - num;
                y = y + num;
                break;
            }
        }

        else if(direction == 7) //LEFT
        {
            if(x - num >= 0)
            {
                x = x - num;
                break;
            }
        }

        else if(direction == 8) //UPLEFT
        {
            if(x - num >= 0 && y - num >= 0)
            {
                x = x - num;
                y = y - num;
                break;
            }
        }

        num--;
        if(num == 0)
        {
            break;
        }
    }
}
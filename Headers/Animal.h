#ifndef POO_ANIMAL_H
#define POO_ANIMAL_H

#include "Coordenadas.h"

class Animal
{
    int ID, HP, campoVisao, moveDistance, lifeTick, hunger;
    double Peso;
    char moveDirection, especie;
    Coordenadas Location;

protected:
    Animal(const int &id, const int &x, const int &y, const char &especie = 'D');

public:
    ~Animal();
    int getX() const;
    int getY() const;
    int getID() const;
    char getEspecie() const;
    double getPeso() const;
    int getRange() const;
    int getHP() const;
};

class Coelho: public Animal
{
public:
    Coelho(const int &id, const int &x, const int &y);
    ~Coelho();
};

#endif //POO_ANIMAL_H

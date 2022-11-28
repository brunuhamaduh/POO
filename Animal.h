#ifndef POO_ANIMAL_H
#define POO_ANIMAL_H

#include "Coordenadas.h"

class Animal
{
    static int count;
    int ID;
protected:
    //double Peso;
    char Especie;
    int HP;
    Coordenadas Location;
public:
    Animal(const int &x, const int &y);
    ~Animal();
    int getX() const;
    int getY() const;
    int getID() const;
    char getEspecie() const;
    int getHP() const;
};

#endif //POO_ANIMAL_H

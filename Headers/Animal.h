#ifndef POO_ANIMAL_H
#define POO_ANIMAL_H

#include "Coordenadas.h"

class Animal
{
    int ID, HP, hunger, campoVisao, lifeTick;
    double Peso;
    char especie;
    std::string Nome;
    Coordenadas Location;

protected:
    Animal(const int &id, const int &x, const int &y);
    void InitEspecie(const char &chara);
    void InitCampoVisao(const int &num);
    void InitPeso(const double &num);

public:
    ~Animal();
    int getX() const;
    int getY() const;
    int getID() const;
    char getEspecie() const;
    int getHP() const;
    int getHunger() const;
    int getcampoVisao() const;
    double getPeso() const;
    void setHP(const int &num);
    void setLifeTick(const int &num);
};

class Coelho: public Animal
{
public:
    Coelho(const int &id, const int &x, const int &y);
    ~Coelho();
};

class Ovelha: public Animal
{
public:
    Ovelha(const int &id, const int &x, const int &y);
    ~Ovelha();
};

class Lobo: public Animal
{
public:
    Lobo(const int &id, const int &x, const int &y);
    ~Lobo();
};

#endif //POO_ANIMAL_H

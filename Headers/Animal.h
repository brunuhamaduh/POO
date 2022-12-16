#ifndef POO_ANIMAL_H
#define POO_ANIMAL_H

#include "Coordenadas.h"

class BaseAnimal
{
    int ID;
    int HP;
    int campoVisao;
    double Peso;
    std::string Nome;
    Coordenadas Location;
    char especie;

public:
    BaseAnimal(const int &id, const int &x, const int &y);
    ~BaseAnimal();
    void InitEspecie(const char &chara);
    void InitCampoVisao(const int &num);
    void InitPeso(const double &num);
    int getX() const;
    int getY() const;
    int getID() const;
    void setPos(int &direction, int &num, const int &tamanho);
    char getEspecie() const;
    int getcampoVisao() const;
    double getPeso() const;
    int getHP() const;
    void setHP(const int &num);
    virtual int getHunger() const;
    virtual void setLifeTick(const int &num);
    virtual void Move(const int &tamanho);
};

class AnimalH: virtual public BaseAnimal
{
    int hunger;

public:
    AnimalH(const int &id, const int &x, const int &y);
    ~AnimalH();
    int getHunger() const override;
};

class AnimalL: virtual public BaseAnimal
{
    int lifeTick;

public:
    AnimalL(const int &id, const int &x, const int &y);
    ~AnimalL();
    void setLifeTick(const int &num) override;
};

class CompleteAnimal: public AnimalH, public AnimalL
{
public:
    CompleteAnimal(const int &id, const int &x, const int &y);
    ~CompleteAnimal();
};

class Coelho: public CompleteAnimal
{
public:
    Coelho(const int &id, const int &x, const int &y);
    ~Coelho();
    void Move(const int &tamanho) override;
};

class Ovelha: public CompleteAnimal
{
public:
    Ovelha(const int &id, const int &x, const int &y);
    ~Ovelha();
};

class Lobo: public AnimalH
{
public:
    Lobo(const int &id, const int &x, const int &y);
    ~Lobo();
};

class Canguru: public AnimalL
{
public:
    Canguru(const int &id, const int &x, const int &y);
    ~Canguru();
};

#endif //POO_ANIMAL_H

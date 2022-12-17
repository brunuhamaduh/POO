#ifndef POO_ANIMAL_H
#define POO_ANIMAL_H

#include "Coordenadas.h"

class BaseAnimal
{
    int ID;
    int HP;
    int campoVisao;
    int instante;
    double Peso;
    std::string Nome;
    Coordenadas Location;
    char especie;

public:
    BaseAnimal();
    BaseAnimal(const int &x, const int &y, const int &hp);
    BaseAnimal(const int &x, const int &y);
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
    void setPeso(const int &num);
    int getHP() const;
    void setHP(const int &num);
    int getInstante() const;
    void incInstante();

    virtual void InitLifeTick(const int &num);
    virtual void LifeTick();
    virtual void Move(const int &tamanho);
    virtual int getLifeTick() const;
    virtual int getHunger() const;
    virtual void setHunger(const int &num);
    virtual void Hunger();
    virtual BaseAnimal* Child();
    virtual bool checkChild();
};

class AnimalH: virtual public BaseAnimal
{
    int hunger;

public:
    AnimalH();
    ~AnimalH();
    int getHunger() const override;
    void setHunger(const int &num) override;
    virtual void Hunger();
};

class AnimalL: virtual public BaseAnimal
{
    int lifeTick;

public:
    AnimalL();
    ~AnimalL();
    void InitLifeTick(const int &num) override;
    void LifeTick() override;
    int getLifeTick() const override;
};

class CompleteAnimal: public AnimalH, public AnimalL
{
public:
    CompleteAnimal();
    ~CompleteAnimal();
};

class Coelho: public CompleteAnimal
{
public:
    Coelho();
    Coelho(const int &x, const int &y);
    ~Coelho();
    void Move(const int &tamanho) override;
    void Hunger() override;
    Coelho* Child() override;
    bool checkChild() override;
};

class Ovelha: public CompleteAnimal
{
public:
    Ovelha();
    Ovelha(const int &x, const int &y);
    Ovelha(const int &x, const int &y, const int &hp);
    ~Ovelha();
    void Move(const int &tamanho) override;
    void Hunger() override;
    Ovelha* Child() override;
    bool checkChild() override;
};

class Lobo: public AnimalH
{
public:
    Lobo();
    Lobo(const int &x, const int &y);
    ~Lobo();
    void Move(const int &tamanho) override;
    void Hunger() override;
    //Lobo* Child() override;
    //bool checkChild() override;
};

class Canguru: public AnimalL
{
public:
    Canguru();
    Canguru(const int &x, const int &y);
    ~Canguru();
    void Move(const int &tamanho) override;
    //Canguru* Child() override;
    //bool checkChild() override;
};

#endif //POO_ANIMAL_H

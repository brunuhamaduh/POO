#ifndef POO_ANIMAL_H
#define POO_ANIMAL_H

#include "Alimento.h"
#include "History.h"

class BaseAnimal
{
    int ID;
    int HP;
    int campoVisao;
    int instante;
    double Peso;
    Coordenadas Location;
    std::string Description;
    char especie;
    bool kill;

protected:
    int getInstante() const;
    void setPeso(const int &num);
    int getcampoVisao() const;
    void InitEspecie(const char &chara);
    void InitCampoVisao(const int &num);
    void InitPeso(const double &num);
    BaseAnimal();
    BaseAnimal(const int &x, const int &y, const int &hp);
    BaseAnimal(const int &x, const int &y);

public:
    virtual ~BaseAnimal();
    int getX() const;
    int getY() const;
    void setX(const int &num);
    void setY(const int &num);
    int getID() const;
    void setPos(int &direction, int &num, const int &tamanho);
    char getEspecie() const;
    double getPeso() const;
    int getHP() const;
    void setHP(const int &num);
    void incInstante();
    void setDescription(const std::string &str);
    std::string getDescription() const;
    static std::vector<BaseAnimal*> checkAroundAnimais(const std::vector<BaseAnimal*> &animais, const int &visionRange, const int &x, const int &y, const int &id) ;
    static std::vector<BaseAlimento*> checkAroundAlimentos(const std::vector<BaseAlimento*> &alimentos, const int &visionRange, const int &x, const int &y, const int &id) ;
    void Kill();
    bool getKill() const;
    //wolf doesn't have this
    virtual int getLifeTick() const;
    virtual void LifeTick();
    //canguru doesn't have this
    virtual int getHunger() const;
    virtual void setHunger(const int &num);
    virtual void Hunger();
    virtual void Eat(std::vector<BaseAnimal*> &animais, std::vector<BaseAlimento*> &alimentos);
    virtual std::string getFoodHistory() const;
    virtual void addFood(History *food);
    //all classes have it
    virtual void Move(const int &tamanho, const std::vector<BaseAnimal*> &animais, const std::vector<BaseAlimento*> &alimentos) = 0;
    virtual BaseAnimal* Child() const = 0;
    virtual bool checkChild() = 0;
    virtual BaseAlimento* Die() = 0;
    //only canguru has this
    virtual bool getHide() const;
};

class AnimalH: virtual public BaseAnimal
{
    int hunger;
    History **FoodHistory;
    int eatenfood;

public:
    AnimalH();
    ~AnimalH() override;
    int getHunger() const override;
    void setHunger(const int &num) override;
    void Hunger() override;
    void addFood(History *food) override;
    std::string getFoodHistory() const override;
};

class AnimalL: virtual public BaseAnimal
{
    int lifeTick;

public:
    AnimalL();
    ~AnimalL() override;
    void InitLifeTick(const int &num);
    void LifeTick() override;
    int getLifeTick() const override;
};

class CompleteAnimal: public AnimalH, public AnimalL
{
public:
    CompleteAnimal();
    ~CompleteAnimal() override;
};

class Coelho: public CompleteAnimal
{
public:
    Coelho();
    Coelho(const int &x, const int &y);
    ~Coelho() override;
    void Move(const int &tamanho, const std::vector<BaseAnimal*> &animais, const std::vector<BaseAlimento*> &alimentos) override;
    void Hunger() override;
    Coelho* Child() const override;
    bool checkChild() override;
    BaseAlimento* Die() override;
    void Eat(std::vector<BaseAnimal*> &animais, std::vector<BaseAlimento*> &alimentos) override;
};

class Ovelha: public CompleteAnimal
{
public:
    Ovelha();
    Ovelha(const int &x, const int &y);
    Ovelha(const int &x, const int &y, const int &hp);
    ~Ovelha() override;
    void Move(const int &tamanho, const std::vector<BaseAnimal*> &animais, const std::vector<BaseAlimento*> &alimentos) override;
    void Hunger() override;
    Ovelha* Child() const override;
    bool checkChild() override;
    Corpo* Die() override;
    void Eat(std::vector<BaseAnimal*> &animais, std::vector<BaseAlimento*> &alimentos) override;
};

class Lobo: public AnimalH
{
    int VLobo;
    int spawn;
public:
    Lobo();
    Lobo(const int &x, const int &y);
    ~Lobo() override;
    void Move(const int &tamanho, const std::vector<BaseAnimal*> &animais, const std::vector<BaseAlimento*> &alimentos) override;
    void Hunger() override;
    Lobo* Child() const override;
    bool checkChild() override;
    Corpo* Die() override;
    void Eat(std::vector<BaseAnimal*> &animais, std::vector<BaseAlimento*> &alimentos) override;
};

class Canguru: public AnimalL
{
    int idparent;
    bool child, run, hide;
    int hidetick;
public:
    Canguru();
    Canguru(const int &x, const int &y);
    Canguru(const int &x, const int &y, const int &idparent);
    ~Canguru() override;
    void Move(const int &tamanho, const std::vector<BaseAnimal*> &animais, const std::vector<BaseAlimento*> &alimentos) override;
    Canguru* Child() const override;
    bool checkChild() override;
    Corpo* Die() override;
    bool getHide() const override;
};

class Misterio: public AnimalH
{
public:
    Misterio();
    Misterio(const int &x, const int &y);
    ~Misterio() override;
    void Move(const int &tamanho, const std::vector<BaseAnimal*> &animais, const std::vector<BaseAlimento*> &alimentos) override;
    AMisterio* Die() override;
    void Hunger() override;
    Misterio* Child() const override;
    bool checkChild() override;
    void Eat(std::vector<BaseAnimal*> &animais, std::vector<BaseAlimento*> &alimentos) override;
};

#endif //POO_ANIMAL_H
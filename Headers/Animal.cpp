#include "Animal.h"
#include <random>
#include <algorithm>
#include <fstream>
#include <sstream>

#include "Reserva.h"

BaseAnimal::BaseAnimal(const int &id, const int &x, const int &y) : Location(x,y), ID(id), campoVisao(2), Peso(5), especie('X'), HP(100), instante(0){}
BaseAnimal::~BaseAnimal() = default;
void BaseAnimal::InitEspecie(const char &chara) {especie = chara;}
void BaseAnimal::InitCampoVisao(const int &num) {campoVisao = num;}
void BaseAnimal::InitPeso(const double &num) {Peso = num;}
void BaseAnimal::InitLifeTick(const int &num) {}
int BaseAnimal::getX() const {return Location.getX();}
int BaseAnimal::getY() const {return Location.getY();}
int BaseAnimal::getID() const {return ID;}
void BaseAnimal::setPos(int &direction, int &num, const int &tamanho) {Location.setPos(direction, num, tamanho);}
char BaseAnimal::getEspecie() const {return especie;}
int BaseAnimal::getcampoVisao() const {return campoVisao;}
double BaseAnimal::getPeso() const {return Peso;}
int BaseAnimal::getHP() const {return HP;}
void BaseAnimal::setHP(const int &num) {HP = num;}
int BaseAnimal::getHunger() const {return -1;}
void BaseAnimal::LifeTick() {}
void BaseAnimal::Move(const int &tamanho) {}
int BaseAnimal::getLifeTick() const {return -1;}
void BaseAnimal::Hunger() {}
void BaseAnimal::setHunger(const int &num) {}
void BaseAnimal::setPeso(const int &num) {Peso = num;}
int BaseAnimal::getInstante() const {return instante;}
void BaseAnimal::incInstante() {instante++;}
BaseAnimal* BaseAnimal::Child() {return new BaseAnimal(*this);}
bool BaseAnimal::checkChild() {return false;}

AnimalH::AnimalH(const int &id, const int &x, const int &y) : BaseAnimal{id, x, y}, hunger(0) {}
AnimalH::~AnimalH() = default;
int AnimalH::getHunger() const {return hunger;}
void AnimalH::Hunger() {}
void AnimalH::setHunger(const int &num) {hunger = hunger + num;}

AnimalL::AnimalL(const int &id, const int &x, const int &y) : BaseAnimal{id, x, y}, lifeTick(50) {}
AnimalL::~AnimalL() = default;
void AnimalL::InitLifeTick(const int &num) {lifeTick = num;}
void AnimalL::LifeTick() {lifeTick--;}
int AnimalL::getLifeTick() const {return lifeTick;}

CompleteAnimal::CompleteAnimal(const int &id, const int &x, const int &y) : BaseAnimal{id, x, y}, AnimalH{id, x, y}, AnimalL{id, x, y} {}
CompleteAnimal::~CompleteAnimal() = default;

Coelho::Coelho(const int &id, const int &x, const int &y) : BaseAnimal{id, x, y}, CompleteAnimal{id, x, y}
{
    std::random_device random;
    std::mt19937 generator(random());
    std::uniform_real_distribution <> distr(1, 4);

    this->InitEspecie('C');
    this->InitCampoVisao(4);
    this->InitPeso(distr(generator));

    std::string line, variable;
    int num;
    std::ifstream constantes("constantes.txt");
    if (constantes.is_open())
    {
        while(getline(constantes,line))
        {
            std::istringstream p(line);
            p >> variable >> num;
            if(variable == "SCoelho")
            {
                setHP(num);
            }
            else if(variable == "VCoelho")
            {
                InitLifeTick(num);
            }
        }
    }
    constantes.close();
}
Coelho::~Coelho() = default;

void Coelho::Move(const int &tamanho)
{
    std::random_device random;
    std::mt19937 generator(random());
    std::uniform_int_distribution <> random_direction(1, 8);
    int direction = random_direction(generator);
    int steps;

    if(getHunger() >= 10)
    {
        std::uniform_int_distribution <> random_steps(1, 3);
        steps = random_steps(generator);
    }
    else if(getHunger() >= 20)
    {
        std::uniform_int_distribution <> random_steps(1, 4);
        steps = random_steps(generator);
    }
    else
    {
        std::uniform_int_distribution <> random_steps(1, 2);
        steps = random_steps(generator);
    }

    setPos(direction, steps, tamanho);
}

void Coelho::Hunger()
{
    if(getHunger() >= 10 && getHunger() < 20)
    {
        setHP(getHP() - 1);
    }
    else if(getHunger() >= 20)
    {
        setHP(getHP() - 2);
    }
    setHunger(1);
}

bool Coelho::checkChild()
{
    if(getInstante() % 8 == 0)
    {
        std::random_device random;
        std::mt19937 generator(random());
        std::uniform_int_distribution <> distr(1, 2); // 50%/50%
        if(distr(generator) == 2) //new coelho
        {
            return true;
        }
    }
    return false;
}

Coelho* Coelho::Child()
{
    std::random_device random;
    std::mt19937 generator(random());
    std::uniform_int_distribution <> distr1(1, 10);
    return new Coelho(Reserva::getID(), distr1(generator), distr1(generator));
}

Ovelha::Ovelha(const int &id, const int &x, const int &y) : BaseAnimal{id, x, y}, CompleteAnimal{id, x, y}
{
    std::random_device random;
    std::mt19937 generator(random());
    std::uniform_real_distribution <> distr(4, 8);

    this->InitEspecie('O');
    this->InitCampoVisao(3);
    this->InitPeso(distr(generator));

    std::string line, variable;
    int num;
    std::ifstream constantes("constantes.txt");
    if (constantes.is_open())
    {
        while(getline(constantes,line))
        {
            std::istringstream p(line);
            p >> variable >> num;
            if(variable == "SOvelha")
            {
                setHP(num);
            }
            else if(variable == "VOvelha")
            {
                InitLifeTick(num);
            }
        }
    }
    constantes.close();
}
Ovelha::~Ovelha() = default;

void Ovelha::Move(const int &tamanho)
{
    std::random_device random;
    std::mt19937 generator(random());
    std::uniform_int_distribution <> random_direction(1, 8);

    int direction = random_direction(generator);
    int steps = 1;

    if(getHunger() >= 15)
    {
        std::uniform_int_distribution <> random_steps(1, 2);
        steps = random_steps(generator);
    }

    setPos(direction, steps, tamanho);
}

void Ovelha::Hunger()
{
    if(getHunger() >= 15 && getHunger() < 20)
    {
        setHP(getHP() - 1);
    }
    else if(getHunger() >= 20)
    {
        setHP(getHP() - 2);
    }
    setHunger(1);
}

Lobo::Lobo(const int &id, const int &x, const int &y) : BaseAnimal{id, x, y}, AnimalH{id, x, y}
{
    this->InitEspecie('L');
    this->InitCampoVisao(5);
    this->InitPeso(15);

    std::string line, variable;
    int num;
    std::ifstream constantes("constantes.txt");
    if (constantes.is_open())
    {
        while(getline(constantes,line))
        {
            std::istringstream p(line);
            p >> variable >> num;
            if(variable == "SLobo")
            {
                setHP(num);
            }
        }
    }
    constantes.close();
}
Lobo::~Lobo() = default;

void Lobo::Move(const int &tamanho)
{
    std::random_device random;
    std::mt19937 generator(random());
    std::uniform_int_distribution <> random_direction(1, 8);

    int direction = random_direction(generator);
    int steps = 1;

    if(getHunger() >= 15)
    {
        steps = 2;
    }

    setPos(direction, steps, tamanho);
}

void Lobo::Hunger()
{
    if(getHunger() >= 15 && getHunger() < 25)
    {
        setHP(getHP() - 1);
    }
    else if(getHunger() >= 25)
    {
        setHP(getHP() - 2);
    }
    setHunger(2);
}

Canguru::Canguru(const int &id, const int &x, const int &y) : BaseAnimal{id, x, y}, AnimalL{id, x, y}
{
    this->InitEspecie('G');
    this->InitCampoVisao(7);
    this->InitPeso(10);

    std::string line, variable;
    int num;
    std::ifstream constantes("constantes.txt");
    if (constantes.is_open())
    {
        while(getline(constantes,line))
        {
            std::istringstream p(line);
            p >> variable >> num;
            if(variable == "SCanguru")
            {
                setHP(num);
            }
            else if(variable == "VCanguru")
            {
                InitLifeTick(num);
            }
        }
    }
    constantes.close();
}
Canguru::~Canguru() = default;

void Canguru::Move(const int &tamanho)
{
    std::random_device random;
    std::mt19937 generator(random());
    std::uniform_int_distribution <> random_direction(1, 8);

    int direction = random_direction(generator);
    int steps = 1;

    setPos(direction, steps, tamanho);
    if(getInstante() == 20)
    {
        setPeso(20);
    }
}
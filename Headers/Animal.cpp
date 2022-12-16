#include "Animal.h"
#include <random>
#include <algorithm>
#include <fstream>
#include <sstream>

BaseAnimal::BaseAnimal(const int &id, const int &x, const int &y) : Location(x,y), ID(id), campoVisao(2), Peso(5), especie('X'), HP(100) {}
BaseAnimal::~BaseAnimal() = default;
void BaseAnimal::InitEspecie(const char &chara) {especie = chara;}
void BaseAnimal::InitCampoVisao(const int &num) {campoVisao = num;}
void BaseAnimal::InitPeso(const double &num) {Peso = num;}
int BaseAnimal::getX() const {return Location.getX();}
int BaseAnimal::getY() const {return Location.getY();}
int BaseAnimal::getID() const {return ID;}
char BaseAnimal::getEspecie() const {return especie;}
int BaseAnimal::getcampoVisao() const {return campoVisao;}
double BaseAnimal::getPeso() const {return Peso;}
int BaseAnimal::getHP() const {return HP;}
void BaseAnimal::setHP(const int &num) {HP = num;}

AnimalH::AnimalH(const int &id, const int &x, const int &y) : BaseAnimal{id, x, y}, hunger(0) {}
AnimalH::~AnimalH() = default;
int AnimalH::getHunger() const {return hunger;}

AnimalL::AnimalL(const int &id, const int &x, const int &y) : BaseAnimal{id, x, y}, lifeTick(50) {}
AnimalL::~AnimalL() = default;
void AnimalL::setLifeTick(const int &num) {lifeTick = num;}

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
                this->setHP(num);
            }
            else if(variable == "VCoelho")
            {
                this->setLifeTick(num);
            }
        }
    }
    constantes.close();
}
Coelho::~Coelho() = default;

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
                this->setHP(num);
            }
            else if(variable == "VOvelha")
            {
                this->setLifeTick(num);
            }
        }
    }
    constantes.close();
}
Ovelha::~Ovelha() = default;

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
                this->setHP(num);
            }
        }
    }
    constantes.close();
}
Lobo::~Lobo() = default;

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
                this->setHP(num);
            }
            else if(variable == "VCanguru")
            {
                this->setLifeTick(num);
            }
        }
    }
    constantes.close();
}
Canguru::~Canguru() = default;
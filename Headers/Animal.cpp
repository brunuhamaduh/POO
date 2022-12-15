#include "Animal.h"
#include <random>
#include <algorithm>
#include <fstream>
#include <sstream>

Animal::Animal(const int &id, const int &x, const int &y) : Location(x,y), ID(id), campoVisao(2), HP(100), hunger(0), Peso(5), lifeTick(100), especie('X') {}
Animal::~Animal() = default;
char Animal::getEspecie() const {return especie;}
int Animal::getX() const {return Location.getX();}
int Animal::getY() const {return Location.getY();}
int Animal::getID() const {return ID;}
int Animal::getHP() const {return HP;}
int Animal::getHunger() const {return hunger;}
int Animal::getcampoVisao() const {return campoVisao;}
double Animal::getPeso() const {return Peso;}
void Animal::InitEspecie(const char &chara) {especie = chara;}
void Animal::InitCampoVisao(const int &num) {campoVisao = num;}
void Animal::InitPeso(const double &num) {Peso = num;}
void Animal::setHP(const int &num) {HP = num;}
void Animal::setLifeTick(const int &num) {lifeTick = num;}

Coelho::Coelho(const int &id, const int &x, const int &y) : Animal{id, x, y}
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

Ovelha::Ovelha(const int &id, const int &x, const int &y) : Animal{id, x, y}
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

Lobo::Lobo(const int &id, const int &x, const int &y) : Animal{id, x, y}
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
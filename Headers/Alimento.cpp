#include "Alimento.h"
#include "Reserva.h"
#include <algorithm>
#include <random>
#include <fstream>
#include <sstream>

BaseAlimento::BaseAlimento() : ID(Reserva::getID()), ValorNutritivo(0), letra('x'), Toxicidade(0), Instante(0), kill(false) {}
BaseAlimento::BaseAlimento(const int &x, const int &y) : Location(x, y), ID(Reserva::getID()), ValorNutritivo(0), letra('x'), Toxicidade(0), Instante(0), kill(false) {}
BaseAlimento::~BaseAlimento() = default;
int BaseAlimento::getX() const {return Location.getX();}
int BaseAlimento::getY() const {return Location.getY();}
int BaseAlimento::getID() const {return ID;}
int BaseAlimento::getVN() const {return ValorNutritivo;}
int BaseAlimento::getToxic() const {return Toxicidade;}
void BaseAlimento::InitVN(const int &num) {ValorNutritivo = num;}
void BaseAlimento::InitToxic(const int &num) {Toxicidade = num;}
void BaseAlimento::InitLetra(const char &letr) {letra = letr;}
void BaseAlimento::InitCheiro(const std::vector<std::string> &cheiros) {Cheiro = cheiros;}
std::vector<std::string> BaseAlimento::getCheiro() const {return Cheiro;}
int BaseAlimento::getInstante() const {return Instante;}
void BaseAlimento::incInstante() {Instante++;}
int BaseAlimento::getTV() const {return -1;}
char BaseAlimento::getLetra() const {return letra;}
BaseAlimento* BaseAlimento::Child(std::vector<BaseAlimento*> &alimentos) {return nullptr;}
void BaseAlimento::Kill() {kill = true;}
bool BaseAlimento::getKill() const {return kill;}
void BaseAlimento::InitDescription(const std::string &descrip) {Description = descrip;}
std::string BaseAlimento::getDescription() const {return Description;}

AlimentoTV::AlimentoTV() : TempodeVida(30) {}
AlimentoTV::~AlimentoTV() = default;
int AlimentoTV::getTV() const {return TempodeVida;}
int AlimentoTV::getTV2() const {return TempodeVida;}
void AlimentoTV::InitTV(const int &num) {TempodeVida = num;}

Relva::Relva()
{
    std::vector<std::string> cheiros = {"erva", "verdura"};
    InitVN(3);
    InitLetra('r');
    InitCheiro(cheiros);
    InitDescription("Relva");

    std::string line, variable;
    int num;
    std::ifstream constantes("constantes.txt");
    if (constantes.is_open())
    {
        while(getline(constantes,line))
        {
            std::istringstream p(line);
            p >> variable >> num;
            if(variable == "VRelva")
            {
                InitTV(num);
            }
        }
    }
    constantes.close();
    instanteSpawn = getTV2() * 0.75;
    spawned = false;
}

Relva::Relva(const int &x, const int &y) : BaseAlimento{x,y}
{
    std::vector<std::string> cheiros = {"erva", "verdura"};
    InitVN(3);
    InitLetra('r');
    InitCheiro(cheiros);
    InitDescription("Relva");

    std::string line, variable;
    int num;
    std::ifstream constantes("constantes.txt");
    if (constantes.is_open())
    {
        while(getline(constantes,line))
        {
            std::istringstream p(line);
            p >> variable >> num;
            if(variable == "VRelva")
            {
                InitTV(num);
            }
        }
    }
    constantes.close();
    instanteSpawn = getTV2() * 0.75;
    spawned = false;
}
Relva::~Relva() = default;

bool Relva::Action()
{
    InitTV(getTV() - 1);
    if(round(instanteSpawn) >= getInstante() && !spawned)
    {
        return true;
    }
    return false;
}

Relva* Relva::Child(std::vector<BaseAlimento*> &alimentos)
{
    std::random_device random;
    std::mt19937 generator(random());
    std::uniform_int_distribution <> distr(4, 8);
    std::uniform_int_distribution <> sinal(1, 4);
    int xRandom, yRandom, area = Reserva::getArea(), sinalconta, tentativa = 0;

    while(true)
    {
        sinalconta = sinal(generator);
        tentativa++;
        if (sinalconta == 1)
        {
            xRandom = distr(generator) + getX();
            yRandom = distr(generator) + getY();
        }
        else if (sinalconta == 2)
        {
            xRandom = distr(generator) - getX();
            yRandom = distr(generator) + getY();
        }
        else if (sinalconta == 3)
        {
            xRandom = distr(generator) + getX();
            yRandom = distr(generator) - getY();
        }
        else if (sinalconta == 4)
        {
            xRandom = distr(generator) - getX();
            yRandom = distr(generator) - getY();
        }

        if (xRandom > 0 && xRandom < area && yRandom > 0 && yRandom < area)
        {
            break;
        }
        else if (tentativa == 50) //in case it gets stuck in an infinite loop
        {
            xRandom = 0;
            yRandom = 0;
            break;
        }
    }

    for(auto const &it: alimentos)
    {
        if(xRandom == it->getX() && yRandom == it->getY())
        {
            return nullptr;
        }
    }

    spawned = true;
    return new Relva(xRandom, yRandom);
}

Cenoura::Cenoura()
{
    std::vector<std::string> cheiros = {"verdura"};
    InitVN(4);
    InitLetra('t');
    InitCheiro(cheiros);
    InitDescription("Cenoura");
}

Cenoura::Cenoura(const int &x, const int &y) : BaseAlimento{x,y}
{
    std::vector<std::string> cheiros = {"verdura"};
    InitVN(4);
    InitLetra('t');
    InitCheiro(cheiros);
    InitDescription("Cenoura");
}
Cenoura::~Cenoura() = default;

bool Cenoura::Action()
{
    if(getInstante() % 10 == 0)
    {
        if(getToxic() < 3)
        {
            InitToxic(getToxic()+1);
        }
    }
    return false;
}

Corpo::Corpo(const int &x, const int &y, const int &oldcorpse) : BaseAlimento{x,y}
{
    std::vector<std::string> cheiros = {"carne"};
    InitVN(oldcorpse);
    InitLetra('p');
    InitCheiro(cheiros);
    ogVN = oldcorpse;
    InitDescription("Corpo");
}

Corpo::Corpo(const int &x, const int &y, const int &oldcorpse, const int &Toxic) : BaseAlimento{x, y}
{
    std::vector<std::string> cheiros = {"carne"};
    InitVN(oldcorpse);
    InitLetra('p');
    InitCheiro(cheiros);
    InitToxic(Toxic);
    ogVN = oldcorpse;
    InitDescription("Corpo");
}

Corpo::~Corpo() = default;

bool Corpo::Action()
{
    if(getVN() > 0)
    {
        InitVN(getVN() - 1);
    }
    if(getInstante() <= (2 * ogVN))
    {
        InitToxic(getToxic() + 1);
    }
    return false;
}

Bife::Bife()
{
    std::vector<std::string> cheiros = {"carne", "ketchup"};
    InitLetra('b');
    InitTV(30);
    InitVN(10);
    InitToxic(2);
    InitCheiro(cheiros);
    InitDescription("Bife");
}

Bife::Bife(const int &x, const int &y) : BaseAlimento{x,y}
{
    std::vector<std::string> cheiros = {"carne", "ketchup"};
    InitLetra('b');
    InitTV(30);
    InitVN(10);
    InitToxic(2);
    InitCheiro(cheiros);
    InitDescription("Bife");
}
Bife::~Bife() = default;

bool Bife::Action()
{
    InitTV(getTV() - 1);
    if(getVN() > 0)
    {
        InitVN(getVN() - 1);
    }
    return false;
}

AMisterio::AMisterio()
{
    std::vector<std::string> cheiros = {"especial"};
    InitLetra('a');
    InitTV(50);
    InitVN(100);
    InitToxic(0);
    InitCheiro(cheiros);
    InitDescription("Misterio");
}

AMisterio::AMisterio(const int &x, const int &y) : BaseAlimento{x,y}
{
    std::vector<std::string> cheiros = {"especial"};
    InitLetra('a');
    InitTV(50);
    InitVN(100);
    InitToxic(0);
    InitCheiro(cheiros);
    InitDescription("Misterio");
}
AMisterio::~AMisterio() = default;

bool AMisterio::Action()
{
    InitTV(getTV() - 1);
    if(getVN() > 0)
    {
        InitVN(getVN() - 1);
        InitToxic(getToxic() + 1);
    }
    return false;
}

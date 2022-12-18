#include "Alimento.h"
#include "Reserva.h"
#include <algorithm>
#include <fstream>
#include <sstream>

BaseAlimento::BaseAlimento() : ID(Reserva::getID()), ValorNutritivo(0), letra('x'), Toxicidade(0) {}
BaseAlimento::BaseAlimento(const int &x, const int &y) : Location(x, y), ID(Reserva::getID()), ValorNutritivo(0), letra('x'), Toxicidade(0) {}
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

AlimentoTV::AlimentoTV() : TempodeVida(30) {}
AlimentoTV::AlimentoTV(const int &x, const int &y) : BaseAlimento{x, y}, TempodeVida(30) {}
AlimentoTV::~AlimentoTV() = default;
int AlimentoTV::getTV() const {return TempodeVida;}
void AlimentoTV::InitTV(const int &num) {TempodeVida = num;}

Relva::Relva()
{
    std::vector<std::string> cheiros = {"erva", "verdura"};
    InitVN(3);
    InitLetra('r');
    InitCheiro(cheiros);

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
}

Relva::Relva(const int &x, const int &y) : BaseAlimento{x,y}, AlimentoTV{x, y}
{
    std::vector<std::string> cheiros = {"erva", "verdura"};
    InitVN(3);
    InitLetra('r');
    InitCheiro(cheiros);

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
}
Relva::~Relva() = default;

Cenoura::Cenoura()
{
    std::vector<std::string> cheiros = {"verdura"};
    InitVN(4);
    InitLetra('t');
    InitCheiro(cheiros);
}

Cenoura::Cenoura(const int &x, const int &y) : BaseAlimento{x,y}
{
    std::vector<std::string> cheiros = {"verdura"};
    InitVN(4);
    InitLetra('t');
    InitCheiro(cheiros);
}
Cenoura::~Cenoura() = default;

Corpo::Corpo(const int &x, const int &y, const int &oldcorpse) : BaseAlimento{x,y}
{
    std::vector<std::string> cheiros = {"carne"};
    InitVN(oldcorpse);
    InitLetra('p');
    InitCheiro(cheiros);
}
Corpo::~Corpo() = default;

Bife::Bife()
{
    std::vector<std::string> cheiros = {"carne", "ketchup"};
    InitLetra('b');
    InitTV(30);
    InitVN(10);
    InitToxic(2);
    InitCheiro(cheiros);
}

Bife::Bife(const int &x, const int &y) : BaseAlimento{x,y}, AlimentoTV{x, y}
{
    std::vector<std::string> cheiros = {"carne", "ketchup"};
    InitLetra('b');
    InitTV(30);
    InitVN(10);
    InitToxic(2);
    InitCheiro(cheiros);
}
Bife::~Bife() = default;


#include "Reserva.h"
#include <iomanip>

Reserva::Reserva() : Instante(0){ }
Reserva::~Reserva() = default;
int Reserva::getInstante() const {return Instante;}
std::vector<Coordenadas> Reserva::getCoordenadas() const {return Extremos;}
std::string Reserva::getAnimaisPos(const int &xinf, const int &xsup, const int &yinf, const int &ysup) const
{
    std::ostringstream output;
    for (auto& it : Animais)
    {
        if(it.getX() >= xinf && it.getX() <= xsup && it.getY() >= yinf && it.getY() <= ysup)
        {
            output << it.getID() << " " << it.getEspecie() << " " << it.getHP() << " " << it.getX() << " " << it.getY() << "\n";
        }
    }
    return output.str();
}

std::string Reserva::getAlimentosPos(const int &xinf, const int &xsup, const int &yinf, const int &ysup) const
{
    std::ostringstream output;
    for (auto& it : Alimentos)
    {
        if(it.getX() >= xinf && it.getX() <= xsup && it.getY() >= yinf && it.getY() <= ysup)
        {
            output << it.getID() << " " << it.getVN() << " " << it.getToxic() << " " << it.getTV() << " " << it.getX() << " " << it.getY() << std::endl;
        }
    }
    return output.str();
}

std::string Reserva::getAnimais() const
{
    std::ostringstream output;
    for (auto& it : Animais)
    {
        output << it.getID() << " " << it.getEspecie() << " " << it.getHP() << std::endl;
    }
    return output.str();
}

std::string Reserva::getAlimentos() const
{
    std::ostringstream output;
    for (auto& it : Alimentos)
    {
        output << it.getID() << " " << it.getVN() << " " << it.getToxic() << " " << it.getTV() << std::endl;
    }
    return output.str();
}

size_t Reserva::countAnimal() const
{
    return Animais.size();
}

size_t Reserva::countAlimento() const
{
    return Alimentos.size();
}

void Reserva::newAnimal(const int &x, const int &y) {Animais.emplace_back(Animal(x,y));}
void Reserva::newAlimento(const int &x, const int &y) {Alimentos.emplace_back(Alimento(x,y));}
void Reserva::setLimits(const int &x, const int &y)
{
    Extremos.emplace_back(Coordenadas(0,0)); //Superior Esquerdo
    Extremos.emplace_back(Coordenadas(x,0)); //Superior Direito
    Extremos.emplace_back(Coordenadas(0,y)); //Inferior Esquerdo
    Extremos.emplace_back(Coordenadas(x,y)); //Inferior Direito
}
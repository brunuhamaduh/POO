#include "Reserva.h"
#include <iomanip>

Reserva::Reserva() : tamanho(200), instante(0){ }
Reserva::~Reserva()
{
    for(auto el: Animais)
        delete el;
    for(auto el: Alimentos)
        delete el;
}

int Reserva::getArea() const
{
    return tamanho;
}

void Reserva::setSize(const int &num)
{
    tamanho = num;
}

std::vector<int> Reserva::getVArea() const
{
    return viewarea;
}

std::string Reserva::getAnimaisPos(const int &xinf, const int &xsup, const int &yinf, const int &ysup) const
{
    std::ostringstream output;
    for (auto& it : Animais)
    {
        if(it->getX() >= xinf && it->getX() <= xsup && it->getY() >= yinf && it->getY() <= ysup)
        {
            output << it->getID() << " " <<  it->getEspecie() << " " << it->getHP() << " " << it->getX() << " " << it->getY() << "\n";
        }
    }
    return output.str();
}

std::string Reserva::getAlimentosPos(const int &xinf, const int &xsup, const int &yinf, const int &ysup) const
{
    std::ostringstream output;
    for (auto& it : Alimentos)
    {
        if(it->getX() >= xinf && it->getX() <= xsup && it->getY() >= yinf && it->getY() <= ysup)
        {
            output << it->getID() << " " << it->getVN() << " " << it->getToxic() << " " << it->getTV() << " " << it->getX() << " " << it->getY() << std::endl;
        }
    }
    return output.str();
}

std::string Reserva::getAnimais() const
{
    std::ostringstream output;
    for (auto& it : Animais)
    {
        output << "ID: " << it->getID() << " HP: " << it->getHP() << " Hunger: " << it->getHunger() << " X: " << it->getX() << " Y: " << it->getY() << " Especie: " << it->getEspecie() << " Range Campo Visao: " << it->getcampoVisao() << " Peso: " << it->getPeso() << std::endl;
    }
    return output.str();
}

std::string Reserva::getAlimentos() const
{
    std::ostringstream output;
    for (auto& it : Alimentos)
    {
        output << it->getID() << " " << it->getVN() << " " << it->getToxic() << " " << it->getTV() << std::endl;
    }
    return output.str();
}

int Reserva::getInstante() const
{
    return instante;
}

size_t Reserva::countAnimal() const
{
    return Animais.size();
}

size_t Reserva::countAlimento() const
{
    return Alimentos.size();
}

void Reserva::change_VArea(const int &index, bool op)
{
    if(op)
        viewarea[index]++;
    else
        viewarea[index]--;
}

void Reserva::newAnimal(const int &id, const int &x, const int &y, const char &especie)
{
    if(especie == 'C')
    {
        Animais.emplace_back(new Coelho(id, x, y));
    }
}

void Reserva::newAlimento(const int &id, const int &x, const int &y) {}

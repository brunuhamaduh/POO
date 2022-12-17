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
            output << it->getID() << " " <<  it->getEspecie() << " " << " " << it->getX() << " " << it->getY() << "\n";
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
    output << "ID X Y LT H" << std::endl;
    for (auto& it : Animais)
    {
        output << it->getID() << " " << it->getX() << " " << it->getY() << " " << it->getLifeTick() << " " << it->getHunger() << std::endl;
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

std::string Reserva::displayAnimals() const
{
    std::ostringstream output;

    for (auto& it : Animais)
    {
        if(it->getX() >= viewarea[0] && it->getX() <= viewarea[1] && it->getY() >= viewarea[2] && it->getY() <= viewarea[3])
        {
            output << it->getX() << " " << it->getY() << " " << it->getEspecie() << std::endl;
        }
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

void Reserva::newAnimal(const int &x, const int &y, const char &especie)
{
    if(especie == 'c')
    {
        Animais.emplace_back(new Coelho(++ID, x, y));
    }
    else if(especie == 'o')
    {
        Animais.emplace_back(new Ovelha(++ID, x, y));
    }
    else if(especie == 'l')
    {
        Animais.emplace_back(new Lobo(++ID, x, y));
    }
    else if(especie == 'g')
    {
        Animais.emplace_back(new Canguru(++ID, x, y));
    }
}

void Reserva::advanceInstant(term::Window &out)
{
    instante++;
    for (auto& it : Animais)
    {
        it->Move(tamanho);
        it->LifeTick();
        it->Hunger();
    }

    auto ptr = Animais.begin();
    while(ptr != Animais.end())
    {
        if ((*ptr)->getLifeTick() == 0 || (*ptr)->getHP() == 0)
        {
            ptr = Animais.erase(ptr);
        }
        else
        {
            ptr++;
        }
    }
}

void Reserva::newAlimento(const int &id, const int &x, const int &y) {}
int Reserva::ID = 0;
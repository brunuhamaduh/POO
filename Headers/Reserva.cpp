#include "Reserva.h"
#include <iomanip>
#include <algorithm>
#include <random>

Reserva::Reserva() : instante(0){ }
Reserva::~Reserva()
{
    for(auto el: Animais)
    {
        delete el;
    }

    for(auto el: Alimentos)
    {
        delete el;
    }
}

int Reserva::getArea()
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

//rework this
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

//rework this
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
    output << "ID X Y P HP LT H" << std::endl;
    for (auto& it : Animais)
    {
        output << it->getID() << " " << it->getX() << " " << it->getY() << " " << std::setprecision(2) << it->getPeso() << " " << it->getHP() << " ";
        if(it->getLifeTick() == -1)
        {
            output << "-";
        }
        else
        {
            output << it->getLifeTick();
        }
        if(it->getHunger() == -1)
        {
            output << " -" << std::endl;
        }
        else
        {
            output << " " << it->getHunger() << std::endl;
        }
    }
    return output.str();
}

std::string Reserva::getAlimentos() const
{
    std::ostringstream output;
    output << "ID X Y VN TX TV" << std::endl;
    for (auto& it : Alimentos)
    {
        output << it->getID() << " " << it->getX() << " " << it->getY() << " " << it->getVN() << " " << it->getToxic() << " ";
        if(it->getTV() == -1)
        {
            output << "-" << std::endl;
        }
        else
        {
            output << it->getTV() << std::endl;
        }
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

std::string Reserva::displayAlimentos() const
{
    std::ostringstream output;

    for (auto& it : Alimentos)
    {
        if(it->getX() >= viewarea[0] && it->getX() <= viewarea[1] && it->getY() >= viewarea[2] && it->getY() <= viewarea[3])
        {
            output << it->getX() << " " << it->getY() << " " << it->getLetra() << std::endl;
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

void Reserva::newAnimal(const char &especie, int x, int y)
{
    if(x == -1 && y == -1)
    {
        std::random_device random;
        std::mt19937 generator(random());
        std::uniform_int_distribution <> distr(0, tamanho);
        x = distr(generator);
        y = distr(generator);
    }

    if(especie == 'c')
    {
        Animais.emplace_back(new Coelho(x,y));
    }
    else if(especie == 'o')
    {
        Animais.emplace_back(new Ovelha(x, y));
    }
    else if(especie == 'l')
    {
        Animais.emplace_back(new Lobo(x, y));
    }
    else if(especie == 'g')
    {
        Animais.emplace_back(new Canguru(x, y));
    }
}

void Reserva::newAlimento(const char &tipo, int x, int y)
{
    if(x == -1 && y == -1)
    {
        std::random_device random;
        std::mt19937 generator(random());
        std::uniform_int_distribution <> distr(0, tamanho);
        x = distr(generator);
        y = distr(generator);
    }

    if(tipo == 'r')
    {
        Alimentos.emplace_back(new Relva(x,y));
    }
    else if(tipo == 't')
    {
        Alimentos.emplace_back(new Cenoura(x, y));
    }
    else if(tipo == 'b')
    {
        Alimentos.emplace_back(new Bife(x, y));
    }
}

void Reserva::advanceInstant(const int &num)
{
    std::vector<BaseAnimal*> Copy;
    std::vector<BaseAlimento*> Copy2;
    for(int i = 0; i < num; i++)
    {
        instante++;
        Copy = Animais;
        Copy2 = Alimentos;

        for (auto& it : Animais)
        {
            it->incInstante();
            it->Move(tamanho, Animais, Alimentos);
            it->LifeTick();
            it->Hunger();
            if(it->checkChild()) {Copy.emplace_back(it->Child());}
        }

        for(auto& it : Animais)
        {
            it->Eat(Animais, Alimentos);
        }

        Animais = Copy;

        for (auto& it : Alimentos)
        {
            it->incInstante();
            if(it->Action())
            {
                auto teste = it->Child(Alimentos);
                if(teste != nullptr) {Copy2.emplace_back(teste);}
            }
        }

        auto ptr = Animais.begin();
        while(ptr != Animais.end())
        {
            if ((*ptr)->getLifeTick() == 0 || (*ptr)->getHP() == 0 || (*ptr)->getKill())
            {
                if((*ptr)->Die() != nullptr) {Copy2.emplace_back((*ptr)->Die());}
                ptr = Animais.erase(ptr);
            }
            else
            {
                ptr++;
            }
        }

        Alimentos = Copy2;

        auto ptr1 = Alimentos.begin();
        while(ptr1 != Alimentos.end())
        {
            if ((*ptr1)->getTV() == 0 || (*ptr1)->getKill())
            {
                ptr1 = Alimentos.erase(ptr1);
            }
            else
            {
                ptr1++;
            }
        }
    }
}

std::string Reserva::getInfo(const int &ID1)
{
    for (auto& it : Animais)
    {
        if(it->getID() == ID1)
        {
            return it->getFoodHistory();
        }
    }
    return {};
}

int Reserva::getID() {return ++ID;}
int Reserva::ID = 0;
int Reserva::tamanho = 0;
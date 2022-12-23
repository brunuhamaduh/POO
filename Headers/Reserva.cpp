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

std::string Reserva::getAnimaisPos(const int &xinf, const int &xsup, const int &yinf, const int &ysup) const
{
    std::ostringstream out;
    for (auto& it : Animais)
    {
        if(it->getX() >= xinf && it->getX() <= xsup && it->getY() >= yinf && it->getY() <= ysup)
        {
            out << "ID: " << it->getID() << " X: " << it->getX() << "Y: " << it->getY() << " Especie: " << it->getDescription() << " Peso: " << std::setprecision(2) << it->getPeso() << " HP: " << it->getHP() << " ";
            if(it->getLifeTick() == -1)
            {
                out << "LT: -";
            }
            else
            {
                out << "LT: " << it->getLifeTick();
            }
            if(it->getHunger() == -1)
            {
                out << " H: -" << std::endl;
            }
            else
            {
                out << " H: " << it->getHunger() << std::endl;
                if(!(it->getFoodHistory() == "")) {out << "historico: " << it->getFoodHistory() << std::endl;}
            }
        }
    }
    return out.str();
}

std::string Reserva::getAnimais() const
{
    std::ostringstream out;
    for (auto& it : Animais)
    {
        out << "ID: " << it->getID() << " X: " << it->getX() << "Y: " << it->getY() << " Especie: " << it->getDescription() << " Peso: " << std::setprecision(2) << it->getPeso() << " HP: " << it->getHP() << " ";
        if(it->getLifeTick() == -1)
        {
            out << "LT: -";
        }
        else
        {
            out << "LT: " << it->getLifeTick();
        }
        if(it->getHunger() == -1)
        {
            out << " H: -" << std::endl;
        }
        else
        {
            out << " H: " << it->getHunger() << std::endl;
            if(!(it->getFoodHistory() == "")) {out << "historico: " << it->getFoodHistory() << std::endl;}
        }
    }
    return out.str();
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

    for (auto& it : Alimentos)
    {
        if(it->getX() == x && it->getY() == y)
        {
            return;
        }
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

void Reserva::advanceInstant()
{
    std::vector<BaseAnimal*> Copy;
    std::vector<BaseAlimento*> Copy2;

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

std::string Reserva::getInfo(const int &ID1)
{
    std::ostringstream out;

    for (auto& it : Alimentos)
    {
        if(it->getID() == ID1)
        {
            out << "X: " << it->getX() << " Y: " << it->getY() << " VN: " << it->getVN() << " TX: " << it->getToxic() << " DESCRIP: " << it->getDescription() << " ";
            if(it->getTV() == -1)
            {
                out << "TV: -" << std::endl;
            }
            else
            {
                out << "TV: " << it->getTV() << std::endl;
            }
            return out.str();
        }
    }

    for(auto &it : Animais)
    {
        if(it->getID() == ID1)
        {
            out << "X: " << it->getX() << " Y: " << it->getY() << " Especie: " << it->getDescription() << " Peso: " << std::setprecision(2) << it->getPeso() << " HP: " << it->getHP() << " ";
            if(it->getLifeTick() == -1)
            {
                out << "LT: -";
            }
            else
            {
                out << "LT: " << it->getLifeTick();
            }
            if(it->getHunger() == -1)
            {
                out << " H: -" << std::endl;
            }
            else
            {
                out << " H: " << it->getHunger() << std::endl;
                if(!(it->getFoodHistory() == "")) {out << "historico: " << it->getFoodHistory() << std::endl;}
            }
            return out.str();
        }
    }

    return {};
}

void Reserva::feed(const int &x, const int &y, const int &VN, const int &TOXIC)
{
    for(auto &it : Animais)
    {
        if(it->getX() == x && it->getY() == y)
        {
            it->setHP(it->getHP() + VN - TOXIC);
            it->setHunger(0);
            it->addFood(new History(VN, TOXIC, "User"));
            if(it->getHP() <= 0){it->Kill();}
        }
    }

    auto ptr = Animais.begin();
    while(ptr != Animais.end())
    {
        if ((*ptr)->getLifeTick() == 0 || (*ptr)->getHP() == 0 || (*ptr)->getKill())
        {
            if((*ptr)->Die() != nullptr) {Alimentos.emplace_back((*ptr)->Die());}
            ptr = Animais.erase(ptr);
        }
        else
        {
            ptr++;
        }
    }
}

void Reserva::feedID(const int &ID, const int &VN, const int &TOXIC)
{
    for(auto &it : Animais)
    {
        if(it->getID() == ID)
        {
            it->setHP(it->getHP() + VN - TOXIC);
            it->setHunger(0);
            it->addFood(new History(VN, TOXIC, "User"));
            if(it->getHP() <= 0){it->Kill();}
        }
    }

    auto ptr = Animais.begin();
    while(ptr != Animais.end())
    {
        if ((*ptr)->getLifeTick() == 0 || (*ptr)->getHP() == 0 || (*ptr)->getKill())
        {
            if((*ptr)->Die() != nullptr) {Alimentos.emplace_back((*ptr)->Die());}
            ptr = Animais.erase(ptr);
        }
        else
        {
            ptr++;
        }
    }
}

void Reserva::kill(const int &x, const int &y)
{
    for(auto &it : Animais)
    {
        if(it->getX() == x && it->getY() == y)
        {
            it->Kill();
        }
    }

    auto ptr = Animais.begin();
    while(ptr != Animais.end())
    {
        if ((*ptr)->getLifeTick() == 0 || (*ptr)->getHP() == 0 || (*ptr)->getKill())
        {
            if((*ptr)->Die() != nullptr) {Alimentos.emplace_back((*ptr)->Die());}
            ptr = Animais.erase(ptr);
        }
        else
        {
            ptr++;
        }
    }
}

void Reserva::killID(const int &ID)
{
    for(auto &it : Animais)
    {
        if(it->getID() == ID)
        {
            it->Kill();
        }
    }

    auto ptr = Animais.begin();
    while(ptr != Animais.end())
    {
        if ((*ptr)->getLifeTick() == 0 || (*ptr)->getHP() == 0 || (*ptr)->getKill())
        {
            if((*ptr)->Die() != nullptr) {Alimentos.emplace_back((*ptr)->Die());}
            ptr = Animais.erase(ptr);
        }
        else
        {
            ptr++;
        }
    }
}

void Reserva::nofood(const int &XorID, const int &y)
{
    if(y == -1)
    {
        for (auto& it : Alimentos)
        {
            if(it->getID() == XorID)
            {
                it->Kill();
            }
        }
    }
    else
    {
        for (auto& it : Alimentos)
        {
            if(it->getX() == XorID && it->getY() == y)
            {
                it->Kill();
            }
        }
    }

    auto ptr = Alimentos.begin();
    while(ptr != Alimentos.end())
    {
        if ((*ptr)->getTV() == 0 || (*ptr)->getKill())
        {
            ptr = Alimentos.erase(ptr);
        }
        else
        {
            ptr++;
        }
    }
}

void Reserva::empty(const int &x, const int &y)
{
    for (auto& it : Alimentos)
    {
        if(it->getX() == x && it->getY() == y)
        {
            it->Kill();
        }
    }

    for(auto &it : Animais)
    {
        if(it->getX() == x && it->getY() == y)
        {
            it->Kill();
        }
    }

    auto ptr = Animais.begin();
    while(ptr != Animais.end())
    {
        if ((*ptr)->getLifeTick() == 0 || (*ptr)->getHP() == 0 || (*ptr)->getKill())
        {
            ptr = Animais.erase(ptr);
        }
        else
        {
            ptr++;
        }
    }

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

std::string Reserva::see(const int &x, const int &y)
{
    std::ostringstream out;

    if(!Alimentos.empty())
    {
        out << "ALIMENTOS:" << std::endl;
    }

    for (auto& it : Alimentos)
    {
        if(it->getX() == x && it->getY() == y)
        {
            out << "ID: " << it->getID() << " VN: " << it->getVN() << " TX: " << it->getToxic() << " DESCRIP: " << it->getDescription() << " ";
            if(it->getTV() == -1)
            {
                out << "TV: -" << std::endl;
            }
            else
            {
                out << "TV: " << it->getTV() << std::endl;
            }
        }
    }

    if(!Animais.empty())
    {
        out << "ANIMAIS:" << std::endl;
    }

    for(auto &it : Animais)
    {
        if(it->getX() == x && it->getY() == y)
        {
            out << "ID: " << it->getID() << " Especie: " << it->getDescription() << " Peso: " << std::setprecision(2) << it->getPeso() << " HP: " << it->getHP() << " ";
            if(it->getLifeTick() == -1)
            {
                out << "LT: -";
            }
            else
            {
                out << "LT: " << it->getLifeTick();
            }
            if(it->getHunger() == -1)
            {
                out << " H: -" << std::endl;
            }
            else
            {
                out << " H: " << it->getHunger() << std::endl;
                if(!(it->getFoodHistory() == "")) {out << "historico: " << it->getFoodHistory() << std::endl;}
            }
        }
    }

    return out.str();
}

int Reserva::getID() {return ++ID;}
int Reserva::ID = 0;
int Reserva::tamanho = 0;
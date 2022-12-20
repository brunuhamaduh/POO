#include "Animal.h"
#include <random>
#include <algorithm>
#include <fstream>
#include <sstream>
#include "Reserva.h"

BaseAnimal::BaseAnimal() : ID(Reserva::getID()), HP(100), instante(0), campoVisao(0), Peso(0.0), especie('X') {}
BaseAnimal::BaseAnimal(const int &x, const int &y, const int &hp) : Location(x,y), ID(Reserva::getID()), HP(hp), instante(0), campoVisao(0), Peso(0.0), especie('X') {}
BaseAnimal::BaseAnimal(const int &x, const int &y) : Location(x,y), ID(Reserva::getID()), HP(100), instante(0), campoVisao(0), Peso(0.0), especie('X') {}
BaseAnimal::~BaseAnimal() = default;
void BaseAnimal::InitEspecie(const char &chara) {especie = chara;}
void BaseAnimal::InitCampoVisao(const int &num) {campoVisao = num;}
void BaseAnimal::InitPeso(const double &num) {Peso = num;}
int BaseAnimal::getX() const {return Location.getX();}
int BaseAnimal::getY() const {return Location.getY();}
int BaseAnimal::getID() const {return ID;}
void BaseAnimal::setPos(int &direction, int &num, const int &tamanho) {Location.setPos(direction, num, tamanho);}
char BaseAnimal::getEspecie() const {return especie;}
int BaseAnimal::getcampoVisao() const {return campoVisao;}
double BaseAnimal::getPeso() const {return Peso;}
int BaseAnimal::getHP() const {return HP;}
void BaseAnimal::setHP(const int &num) {HP = num;}
void BaseAnimal::setPeso(const int &num) {Peso = num;}
int BaseAnimal::getInstante() const {return instante;}
void BaseAnimal::incInstante() {instante++;}
std::vector<BaseAnimal*> BaseAnimal::checkAroundAnimais(const std::vector<BaseAnimal*> &animais,  const int &visionRange, const int &x, const int &y, const int &id) const
{
    std::vector<BaseAnimal*> temp;
    for(auto const &it : animais)
    {
        if((abs(it->getX() - x) <= visionRange || abs(it->getY() - y) <= visionRange) && (it->getID() != id))
        {
            temp.emplace_back(it);
        }
    }
    return temp;
}
std::vector<BaseAlimento*> BaseAnimal::checkAroundAlimentos(const std::vector<BaseAlimento*> &alimentos, const int &visionRange, const int &x, const int &y, const int &id) const
{
    std::vector<BaseAlimento*> temp;
    for(auto const &it : alimentos)
    {
        if((abs(it->getX() - x) <= visionRange || abs(it->getY() - y) <= visionRange) && (it->getID() != id))
        {
            temp.emplace_back(it);
        }
    }
    return temp;
}
//virtual functions
void BaseAnimal::InitLifeTick(const int &num) {}
int BaseAnimal::getLifeTick() const {return -1;}
void BaseAnimal::LifeTick() {}
int BaseAnimal::getHunger() const {return -1;}
void BaseAnimal::setHunger(const int &num) {}
void BaseAnimal::Hunger() {}

AnimalH::AnimalH() : hunger(0) {}
AnimalH::AnimalH(const int &x, const int &y) : hunger(0), BaseAnimal{x,y} {}
AnimalH::AnimalH(const int &x, const int &y, const int &hp) : hunger(0), BaseAnimal{x,y, hp} {}
AnimalH::~AnimalH() = default;
int AnimalH::getHunger() const {return hunger;}
void AnimalH::Hunger() {}
void AnimalH::setHunger(const int &num) {hunger = hunger + num;}

AnimalL::AnimalL() : lifeTick(50) {}
AnimalL::AnimalL(const int &x, const int &y) : lifeTick(50), BaseAnimal{x,y} {}
AnimalL::AnimalL(const int &x, const int &y, const int &hp) : lifeTick(50), BaseAnimal{x,y,hp} {}
AnimalL::~AnimalL() = default;
void AnimalL::InitLifeTick(const int &num) {lifeTick = num;}
void AnimalL::LifeTick() {lifeTick--;}
int AnimalL::getLifeTick() const {return lifeTick;}

CompleteAnimal::CompleteAnimal() {}
CompleteAnimal::CompleteAnimal(const int &x, const int &y) : BaseAnimal{x, y}, AnimalH{x, y}, AnimalL{x, y} {}
CompleteAnimal::CompleteAnimal(const int &x, const int &y, const int &hp) : BaseAnimal{x, y, hp}, AnimalH{x, y, hp}, AnimalL{x, y, hp} {}
CompleteAnimal::~CompleteAnimal() = default;

Coelho::Coelho()
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

Coelho::Coelho(const int &x, const int &y) : BaseAnimal{x,y}, CompleteAnimal{x, y}
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

void Coelho::Move(const int &tamanho, const std::vector<BaseAnimal*> &animais, const std::vector<BaseAlimento*> &alimentos, term::Window &out)
{
    std::random_device random;
    std::mt19937 generator(random());
    std::vector<BaseAnimal*> AroundAnimais = checkAroundAnimais(animais, getcampoVisao(), getX(), getY(), getID());
    std::vector<BaseAlimento*> AroundAlimentos = checkAroundAlimentos(alimentos, getcampoVisao(), getX(), getY(), getID());
    std::vector<std::string> Cheiros;

    bool Run = false;
    bool Chase = false;
    int xTarget = -1, yTarget = -1, direction, steps;

    for(auto &it: AroundAlimentos)
    {
        Cheiros = it->getCheiro();
        if(std::count(Cheiros.begin(), Cheiros.end(), "verdura"))
        {
            Run = false;
            Chase = true;
            if(it->getX() < xTarget && it->getY() < yTarget || (xTarget == -1 && yTarget == -1)) //if it's closer
            {
                xTarget = it->getX();
                yTarget = it->getY();
            }
        }
    }

    for(auto &it: AroundAnimais) //Running from animals has priority
    {
        if(it->getPeso() >= 10)
        {
            Run = true;
            Chase = false;
            xTarget = it->getX();
            yTarget = it->getY();
        }
    }

    if(Run)
    {
        if(getX() - xTarget > 0 && getY() == yTarget) //Animal on the left then run right
        {
            direction = 3;
        }
        else if(getX() - xTarget < 0 && getY() == yTarget) //Animal on the right then run left
        {
            direction = 7;
        }
        else if(getX() == xTarget && getY() - yTarget > 0) //Animal is up then run down
        {
            direction = 5;
        }
        else if(getX() == xTarget && getY() - yTarget < 0) //Animal is down then run up
        {
            direction = 1;
        }
        else if(getX() - xTarget > 0 && getY() - yTarget > 0) //Animal is on the diagonal (upper left) then run lower right
        {
            direction = 4;
        }
        else if(getX() - xTarget > 0 && getY() - yTarget < 0) //Animal is on the diagonal (lower left) then run upper right
        {
            direction = 2;
        }
        else if(getX() - xTarget < 0 && getY() - yTarget > 0) //Animal is on the diagonal (upper right) then run lower left
        {
            direction = 6;
        }
        else if(getX() - xTarget < 0 && getY() - yTarget < 0) //Animal is on the diagonal (lower right) then run upper left
        {
            direction = 8;
        }
    }
    else if(Chase)
    {
        if(getX() - xTarget > 0 && getY() == yTarget) //Food on the left then run left
        {
            direction = 7;
        }
        else if(getX() - xTarget < 0 && getY() == yTarget) //Food on the right then run right
        {
            direction = 3;
        }
        else if(getX() == xTarget && getY() - yTarget > 0) //Food is up then run up
        {
            direction = 1;
        }
        else if(getX() == xTarget && getY() - yTarget < 0) //Food is down then run down
        {
            direction = 5;
        }
        else if(getX() - xTarget > 0 && getY() - yTarget > 0) //Food is on the diagonal (upper left) then run upper left
        {
            direction = 8;
        }
        else if(getX() - xTarget > 0 && getY() - yTarget < 0) //Food is on the diagonal (lower left) then run lower left
        {
            direction = 6;
        }
        else if(getX() - xTarget < 0 && getY() - yTarget > 0) //Food is on the diagonal (upper right) then run upper right
        {
            direction = 2;
        }
        else if(getX() - xTarget < 0 && getY() - yTarget < 0) //Food is on the diagonal (lower right) then run lower right
        {
            direction = 4;
        }
    }
    else
    {
        std::uniform_int_distribution <> random_direction(1, 8);
        direction = random_direction(generator);
    }

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

Coelho* Coelho::Child() const
{
    std::random_device random;
    std::mt19937 generator(random());
    std::uniform_int_distribution <> distr(1, 10);
    std::uniform_int_distribution <> sinal(1, 4);
    int xRandom, yRandom, area = Reserva::getArea(), tentativa = 0, sinalconta;
    while(true) //making sure the child doesn't spawn outside area if parent is on the edges
    {
        tentativa++;
        sinalconta = sinal(generator);

        if(sinalconta == 1)
        {
            xRandom = distr(generator) + getX();
            yRandom = distr(generator) + getY();
        }
        else if(sinalconta == 2)
        {
            xRandom = distr(generator) - getX();
            yRandom = distr(generator) + getY();
        }
        else if(sinalconta == 3)
        {
            xRandom = distr(generator) + getX();
            yRandom = distr(generator) - getY();
        }
        else if(sinalconta == 4)
        {
            xRandom = distr(generator) - getX();
            yRandom = distr(generator) - getY();
        }

        if(xRandom > 0 && xRandom < area && yRandom > 0 && yRandom < area)
        {
            break;
        }
        else if(tentativa == 50) //in case it gets stuck in an infinite loop
        {
            xRandom = 0;
            yRandom = 0;
            break;
        }
    }
    return new Coelho(xRandom, yRandom);
}

BaseAlimento* Coelho::Die() {return nullptr;} //rabbit doesn't spawn anything when it dies

Ovelha::Ovelha()
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

Ovelha::Ovelha(const int &x, const int &y) : BaseAnimal{x,y}, CompleteAnimal{x, y}
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

Ovelha::Ovelha(const int &x, const int &y, const int &hp) : BaseAnimal{x, y, hp}, CompleteAnimal{x, y, hp}
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

void Ovelha::Move(const int &tamanho, const std::vector<BaseAnimal*> &animais, const std::vector<BaseAlimento*> &alimentos, term::Window &out)
{
    std::random_device random;
    std::mt19937 generator(random());
    std::vector<BaseAnimal*> AroundAnimais = checkAroundAnimais(animais, getcampoVisao(), getX(), getY(), getID());
    std::vector<BaseAlimento*> AroundAlimentos = checkAroundAlimentos(alimentos, getcampoVisao(), getX(), getY(), getID());
    std::vector<std::string> Cheiros;

    bool Run = false;
    bool Chase = false;
    int xTarget = -1, yTarget = -1, direction, steps;

    for(auto &it: AroundAlimentos)
    {
        Cheiros = it->getCheiro();
        if(std::count(Cheiros.begin(), Cheiros.end(), "erva"))
        {
            Run = false;
            Chase = true;
            if(it->getX() < xTarget && it->getY() < yTarget || (xTarget == -1 && yTarget == -1)) //if it's closer
            {
                xTarget = it->getX();
                yTarget = it->getY();
            }
        }
    }

    for(auto &it: AroundAnimais) //Running from animals has priority
    {
        if(it->getPeso() >= 15)
        {
            Run = true;
            Chase = false;
            xTarget = it->getX();
            yTarget = it->getY();
        }
    }

    if(Run)
    {
        if(getX() - xTarget > 0 && getY() == yTarget) //Animal on the left then run right
        {
            direction = 3;
        }
        else if(getX() - xTarget < 0 && getY() == yTarget) //Animal on the right then run left
        {
            direction = 7;
        }
        else if(getX() == xTarget && getY() - yTarget > 0) //Animal is up then run down
        {
            direction = 5;
        }
        else if(getX() == xTarget && getY() - yTarget < 0) //Animal is down then run up
        {
            direction = 1;
        }
        else if(getX() - xTarget > 0 && getY() - yTarget > 0) //Animal is on the diagonal (upper left) then run lower right
        {
            direction = 4;
        }
        else if(getX() - xTarget > 0 && getY() - yTarget < 0) //Animal is on the diagonal (lower left) then run upper right
        {
            direction = 2;
        }
        else if(getX() - xTarget < 0 && getY() - yTarget > 0) //Animal is on the diagonal (upper right) then run lower left
        {
            direction = 6;
        }
        else if(getX() - xTarget < 0 && getY() - yTarget < 0) //Animal is on the diagonal (lower right) then run upper left
        {
            direction = 8;
        }
    }
    else if(Chase)
    {
        if(getX() - xTarget > 0 && getY() == yTarget) //Food on the left then run left
        {
            direction = 7;
        }
        else if(getX() - xTarget < 0 && getY() == yTarget) //Food on the right then run right
        {
            direction = 3;
        }
        else if(getX() == xTarget && getY() - yTarget > 0) //Food is up then run up
        {
            direction = 1;
        }
        else if(getX() == xTarget && getY() - yTarget < 0) //Food is down then run down
        {
            direction = 5;
        }
        else if(getX() - xTarget > 0 && getY() - yTarget > 0) //Food is on the diagonal (upper left) then run upper left
        {
            direction = 8;
        }
        else if(getX() - xTarget > 0 && getY() - yTarget < 0) //Food is on the diagonal (lower left) then run lower left
        {
            direction = 6;
        }
        else if(getX() - xTarget < 0 && getY() - yTarget > 0) //Food is on the diagonal (upper right) then run upper right
        {
            direction = 2;
        }
        else if(getX() - xTarget < 0 && getY() - yTarget < 0) //Food is on the diagonal (lower right) then run lower right
        {
            direction = 4;
        }
    }
    else
    {
        std::uniform_int_distribution <> random_direction(1, 8);
        direction = random_direction(generator);
    }

    if(getHunger() >= 15)
    {
        std::uniform_int_distribution <> random_steps(1, 2);
        steps = random_steps(generator);
    }
    else
    {
        steps = 1;
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

bool Ovelha::checkChild()
{
    if(getInstante() % 15 == 0)
    {
        return true;
    }
    return false;
}

Ovelha* Ovelha::Child() const
{
    std::random_device random;
    std::mt19937 generator(random());
    std::uniform_int_distribution <> distr(1, 12);
    std::uniform_int_distribution <> sinal(1, 4);
    int xRandom, yRandom, area = Reserva::getArea(), tentativa = 0, sinalconta;
    while(true) //making sure the child doesn't spawn outside area if parent is on the edges
    {
        tentativa++;
        sinalconta = sinal(generator);

        if(sinalconta == 1)
        {
            xRandom = distr(generator) + getX();
            yRandom = distr(generator) + getY();
        }
        else if(sinalconta == 2)
        {
            xRandom = distr(generator) - getX();
            yRandom = distr(generator) + getY();
        }
        else if(sinalconta == 3)
        {
            xRandom = distr(generator) + getX();
            yRandom = distr(generator) - getY();
        }
        else if(sinalconta == 4)
        {
            xRandom = distr(generator) - getX();
            yRandom = distr(generator) - getY();
        }

        if(xRandom > 0 && xRandom < area && yRandom > 0 && yRandom < area)
        {
            break;
        }
        else if(tentativa == 50) //in case it gets stuck in an infinite loop
        {
            xRandom = 0;
            yRandom = 0;
            break;
        }
    }
    return new Ovelha(xRandom, yRandom, getHP());
}

Corpo* Ovelha::Die()
{
    return new Corpo(getX(), getY(), int(getPeso()));
}

Lobo::Lobo()
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
            else if(variable == "VLobo")
            {
                std::random_device random;
                std::mt19937 generator(random());
                VLobo = num;
                std::uniform_int_distribution <> spawnChild(5, VLobo);
                spawn = spawnChild(generator);
            }
        }
    }
    constantes.close();
}

Lobo::Lobo(const int &x, const int &y) : BaseAnimal{x,y}, AnimalH{x, y}, VLobo(50)
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
            else if(variable == "VLobo")
            {
                VLobo = num;
            }
        }
    }
    constantes.close();
    std::random_device random;
    std::mt19937 generator(random());
    std::uniform_int_distribution <> spawnChild(5, VLobo);
    spawn = spawnChild(generator);
}

Lobo::~Lobo() = default;

void Lobo::Move(const int &tamanho, const std::vector<BaseAnimal*> &animais, const std::vector<BaseAlimento*> &alimentos, term::Window &out)
{
    std::vector<std::string> cheiros;
    int x_target, y_target, steps = 1, direction, choice = 0;
    double biggestAnimal = 0.0;

    for(auto &it: alimentos)
    {
        cheiros = it->getCheiro();
        if(abs(it->getX() - getX()) <= getcampoVisao() && it->getX() == getX())
        {
            for(auto const &it1: cheiros)
            {
                if(it1 == "carne")
                {
                    x_target = it->getX();
                    choice = 1;
                    goto End;
                }
            }
        }

        if(abs(it->getY() - getY()) <= getcampoVisao() && it->getY() == getY())
        {
            for(auto const &it1: cheiros)
            {
                if(it1 == "carne")
                {
                    y_target = it->getY();
                    choice = 2;
                    goto End;
                }
            }
        }
    }

    End:
    for(auto &it: animais)
    {
        if(abs(it->getX() - getX()) <= getcampoVisao() && it->getID() != getID() && it->getY() == getY())
        {
            if(it->getPeso() > biggestAnimal)
            {
                biggestAnimal = it->getPeso();
                x_target = it->getX();
                choice = 3;
            }
        }

        if(abs(it->getY() - getY()) <= getcampoVisao() && it->getID() != getID() && it->getX() == getX())
        {
            if(it->getPeso() > biggestAnimal)
            {
                biggestAnimal = it->getPeso();
                y_target = it->getY();
                choice = 4;
            }
        }
    }

    if(choice == 0)
    {
        std::random_device random;
        std::mt19937 generator(random());
        std::uniform_int_distribution <> random_direction(1, 4);
        direction = random_direction(generator);
    }

    else if(choice == 1 || choice == 3)
    {
        if(x_target - getX() < 0)
        {
            direction = 4; //left
        }
        else if(x_target - getX() > 0)
        {
            direction = 2; //right
        }
    }
    else if(choice == 2 || choice == 4)
    {
        if(y_target - getY() < 0)
        {
            direction = 1; //up
        }
        else if(y_target - getY() > 0)
        {
            direction = 3; //down
        }
    }

    if(choice == 3 || choice == 4)
    {
        steps = 2;
        if(getHunger() >= 15)
        {
            steps = 3;
        }
    }
    else
    {
        steps = 1;
        if(getHunger() >= 15)
        {
            steps = 2;
        }
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

    if(getHP() == -1)
    {
        setHP(0);
    }

    setHunger(2);
}

bool Lobo::checkChild()
{
    if(getInstante() == spawn)
    {
        return true;
    }
    return false;
}

Lobo* Lobo::Child() const
{
    std::random_device random;
    std::mt19937 generator(random());
    std::uniform_int_distribution <> distr(1, 15);
    std::uniform_int_distribution <> sinal(1, 4);
    int xRandom, yRandom, area = Reserva::getArea(), sinalconta, tentativa = 0;
    while(true) //making sure the child doesn't spawn outside area if parent is on the edges
    {
        tentativa++;
        sinalconta = sinal(generator);

        if(sinalconta == 1)
        {
            xRandom = distr(generator) + getX();
            yRandom = distr(generator) + getY();
        }
        else if(sinalconta == 2)
        {
            xRandom = distr(generator) - getX();
            yRandom = distr(generator) + getY();
        }
        else if(sinalconta == 3)
        {
            xRandom = distr(generator) + getX();
            yRandom = distr(generator) - getY();
        }
        else if(sinalconta == 4)
        {
            xRandom = distr(generator) - getX();
            yRandom = distr(generator) - getY();
        }

        if(xRandom > 0 && xRandom < area && yRandom > 0 && yRandom < area)
        {
            break;
        }
        else if(tentativa == 50) //in case it gets stuck in an infinite loop
        {
            xRandom = 0;
            yRandom = 0;
            break;
        }
    }
    return new Lobo(xRandom, yRandom);
}

Corpo* Lobo::Die()
{
    return new Corpo(getX(), getY(), 10);
}

Canguru::Canguru()
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

Canguru::Canguru(const int &x, const int &y) : BaseAnimal{x,y}, AnimalL{x, y}
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

void Canguru::Move(const int &tamanho, const std::vector<BaseAnimal*> &animais, const std::vector<BaseAlimento*> &alimentos, term::Window &out)
{
    std::random_device random;
    std::mt19937 generator(random());
    std::uniform_int_distribution <> random_direction(1,  4);

    int direction = random_direction(generator);
    int steps = 1;

    setPos(direction, steps, tamanho);

    if(getInstante() == 20)
    {
        setPeso(20);
    }
}

bool Canguru::checkChild()
{
    if(getInstante() % 30 == 0)
    {
        return true;
    }
    return false;
}

Canguru* Canguru::Child() const
{
    std::random_device random;
    std::mt19937 generator(random());
    std::uniform_int_distribution <> distr(1, 3);
    std::uniform_int_distribution <> sinal(1, 4);
    int xRandom, yRandom, area = Reserva::getArea(), sinalconta, tentativa = 0;
    while(true) //making sure the child doesn't spawn outside area if parent is on the edges
    {
        tentativa++;
        sinalconta = sinal(generator);

        if(sinalconta == 1)
        {
            xRandom = distr(generator) + getX();
            yRandom = distr(generator) + getY();
        }
        else if(sinalconta == 2)
        {
            xRandom = distr(generator) - getX();
            yRandom = distr(generator) + getY();
        }
        else if(sinalconta == 3)
        {
            xRandom = distr(generator) + getX();
            yRandom = distr(generator) - getY();
        }
        else if(sinalconta == 4)
        {
            xRandom = distr(generator) - getX();
            yRandom = distr(generator) - getY();
        }

        if(xRandom > 0 && xRandom < area && yRandom > 0 && yRandom < area)
        {
            break;
        }
        else if(tentativa == 50) //in case it gets stuck in an infinite loop
        {
            xRandom = 0;
            yRandom = 0;
            break;
        }
    }
    return new Canguru(xRandom, yRandom);
}

Corpo* Canguru::Die()
{
    return new Corpo(getX(), getY(), 15, 5);
}
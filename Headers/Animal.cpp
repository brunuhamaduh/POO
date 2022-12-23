#include "Animal.h"
#include <random>
#include <algorithm>
#include <fstream>
#include <sstream>
#include "Reserva.h"

BaseAnimal::BaseAnimal() : ID(Reserva::getID()), HP(100), instante(0), campoVisao(0), Peso(0.0), especie('X'), kill(false) {}
BaseAnimal::BaseAnimal(const int &x, const int &y, const int &hp) : Location(x,y), ID(Reserva::getID()), HP(hp), instante(0), campoVisao(0), Peso(0.0), especie('X'), kill(false) {}
BaseAnimal::BaseAnimal(const int &x, const int &y) : Location(x,y), ID(Reserva::getID()), HP(100), instante(0), campoVisao(0), Peso(0.0), especie('X'), kill(false) {}
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
void BaseAnimal::Kill() {kill = true;}
bool BaseAnimal::getKill() const {return kill;}
bool BaseAnimal::getHide() const {return false;}
void BaseAnimal::setX(const int &num) {Location.setX(num);}
void BaseAnimal::setY(const int &num) {Location.setY(num);}
void BaseAnimal::setDescription(const std::string &str) {Description = str;}
std::string BaseAnimal::getDescription() const {return Description;}
std::string BaseAnimal::getFoodHistory() const {return "";}
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
void BaseAnimal::Eat(std::vector<BaseAnimal*> &animais, std::vector<BaseAlimento*> &alimentos) {}
void BaseAnimal::addFood(History *food) {}

AnimalH::AnimalH() : FoodHistory(nullptr), eatenfood(0), hunger(0) {}
AnimalH::AnimalH(const int &x, const int &y) : FoodHistory(nullptr), eatenfood(0), hunger(0), BaseAnimal{x,y} {}
AnimalH::AnimalH(const int &x, const int &y, const int &hp) : FoodHistory(nullptr), eatenfood(0), hunger(0), BaseAnimal{x,y, hp} {}
AnimalH::~AnimalH() {delete [] FoodHistory[0]; delete[] FoodHistory;}
int AnimalH::getHunger() const {return hunger;}
void AnimalH::Hunger() {}
void AnimalH::setHunger(const int &num) {hunger = num;}
void AnimalH::addFood(History *food)
{
    int oldFood = eatenfood++, i;
    auto **newFoodHistory = new History*[eatenfood];
    for (i = 0; i < oldFood; i++)
    {
        newFoodHistory[i] = FoodHistory[i];
    }
    newFoodHistory[i] = food;
    delete[] FoodHistory;
    FoodHistory = newFoodHistory;
}
std::string AnimalH::getFoodHistory() const
{
    std::ostringstream out;
    for(int i = 0; i < eatenfood; i++)
    {
        History temp = *FoodHistory[i];
        out << temp.getEntry();
    }
    return out.str();
}

AnimalL::AnimalL() : lifeTick(50) {}
AnimalL::AnimalL(const int &x, const int &y) : lifeTick(50), BaseAnimal{x,y} {}
AnimalL::AnimalL(const int &x, const int &y, const int &hp) : lifeTick(50), BaseAnimal{x,y,hp} {}
AnimalL::~AnimalL() = default;
void AnimalL::InitLifeTick(const int &num) {lifeTick = num;}
void AnimalL::LifeTick() {lifeTick--;}
int AnimalL::getLifeTick() const {return lifeTick;}

CompleteAnimal::CompleteAnimal() = default;
CompleteAnimal::CompleteAnimal(const int &x, const int &y) : BaseAnimal{x, y}, AnimalH{x, y}, AnimalL{x, y} {}
CompleteAnimal::CompleteAnimal(const int &x, const int &y, const int &hp) : BaseAnimal{x, y, hp}, AnimalH{x, y, hp}, AnimalL{x, y, hp} {}
CompleteAnimal::~CompleteAnimal() = default;

Coelho::Coelho()
{
    std::random_device random;
    std::mt19937 generator(random());
    std::uniform_real_distribution <> distr(1, 4);

    InitEspecie('C');
    InitCampoVisao(4);
    InitPeso(distr(generator));
    setDescription("Coelho");

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

    InitEspecie('C');
    InitCampoVisao(4);
    InitPeso(distr(generator));
    setDescription("Coelho");

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

void Coelho::Move(const int &tamanho, const std::vector<BaseAnimal*> &animais, const std::vector<BaseAlimento*> &alimentos)
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

    if(abs(getX()-xTarget) == 1 || abs(getY()-yTarget) == 1 && Chase) //making sure the animal doesn't overshoot the target
    {
        steps = 1;
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
    setHunger(getHunger()+1);
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
void Coelho::Eat(std::vector<BaseAnimal*> &animais, std::vector<BaseAlimento*> &alimentos)
{
    std::vector<std::string> Cheiros;
    for(auto &it : alimentos)
    {
        Cheiros = it->getCheiro();
        if(it->getX() == getX() && it->getY() == getY() && std::count(Cheiros.begin(), Cheiros.end(), "verdura"))
        {
            if(getHP() + it->getVN() - it->getToxic() >= 0)
            {
                setHP(getHP() + it->getVN() - it->getToxic());

            }
            else if(getHP() + it->getVN() - it->getToxic() <= 0)
            {
                Kill();
            }

            addFood(new History(it->getVN(),it->getToxic(),it->getDescription()));
            it->Kill();
            setHunger(0);
            break;
        }
    }
}

Ovelha::Ovelha()
{
    std::random_device random;
    std::mt19937 generator(random());
    std::uniform_real_distribution <> distr(4, 8);

    InitEspecie('O');
    InitCampoVisao(3);
    InitPeso(distr(generator));
    setDescription("Ovelha");

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

    InitEspecie('O');
    InitCampoVisao(3);
    InitPeso(distr(generator));
    setDescription("Ovelha");

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

    InitEspecie('O');
    InitCampoVisao(3);
    InitPeso(distr(generator));
    setDescription("Ovelha");

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

void Ovelha::Move(const int &tamanho, const std::vector<BaseAnimal*> &animais, const std::vector<BaseAlimento*> &alimentos)
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

    if(abs(getX()-xTarget) == 1 || abs(getY()-yTarget) == 1 && Chase) //making sure the animal doesn't overshoot the target
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
    setHunger(getHunger()+1);
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

void Ovelha::Eat(std::vector<BaseAnimal*> &animais, std::vector<BaseAlimento*> &alimentos)
{
    std::vector<std::string> Cheiros;
    for(auto &it : alimentos)
    {
        Cheiros = it->getCheiro();
        if(it->getX() == getX() && it->getY() == getY() && std::count(Cheiros.begin(), Cheiros.end(), "erva"))
        {
            if(getHP() + it->getVN() - it->getToxic() >= 0)
            {
                setHP(getHP() + it->getVN() - it->getToxic());

            }
            else if(getHP() + it->getVN() - it->getToxic() <= 0)
            {
                Kill();
            }

            addFood(new History(it->getVN(),it->getToxic(),it->getDescription()));
            it->Kill();
            setHunger(0);
            break;
        }
    }
}

Lobo::Lobo()
{
    InitEspecie('L');
    InitCampoVisao(5);
    InitPeso(15);
    setDescription("Lobo");

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
    InitEspecie('L');
    InitCampoVisao(5);
    InitPeso(15);
    setDescription("Lobo");

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

void Lobo::Move(const int &tamanho, const std::vector<BaseAnimal*> &animais, const std::vector<BaseAlimento*> &alimentos)
{
    std::random_device random;
    std::mt19937 generator(random());
    std::vector<BaseAnimal*> AroundAnimais = checkAroundAnimais(animais, getcampoVisao(), getX(), getY(), getID());
    std::vector<BaseAlimento*> AroundAlimentos = checkAroundAlimentos(alimentos, getcampoVisao(), getX(), getY(), getID());
    std::vector<std::string> Cheiros;

    bool ChaseAnimal = false;
    bool ChaseFood = false;
    int xTarget = -1, yTarget = -1, direction, steps;
    double biggestAnimal = 0.0;

    for(auto &it: AroundAlimentos)
    {
        Cheiros = it->getCheiro();
        if(std::count(Cheiros.begin(), Cheiros.end(), "carne"))
        {
            ChaseAnimal = false;
            ChaseFood = true;
            if(it->getX() < xTarget && it->getY() < yTarget || (xTarget == -1 && yTarget == -1)) //if it's closer
            {
                xTarget = it->getX();
                yTarget = it->getY();
            }
        }
    }

    for(auto &it: AroundAnimais)
    {
        ChaseAnimal = true;
        ChaseFood = false;
        if(it->getPeso() > biggestAnimal)
        {
            xTarget = it->getX();
            yTarget = it->getY();
            biggestAnimal = it->getPeso();
        }
    }

    if(ChaseAnimal || ChaseFood)
    {
        if(getX() - xTarget > 0 && getY() == yTarget) //Food/Animal on the left then run left
        {
            direction = 7;
        }
        else if(getX() - xTarget < 0 && getY() == yTarget) //Food/Animal on the right then run right
        {
            direction = 3;
        }
        else if(getX() == xTarget && getY() - yTarget > 0) //Food/Animal is up then run up
        {
            direction = 1;
        }
        else if(getX() == xTarget && getY() - yTarget < 0) //Food/Animal is down then run down
        {
            direction = 5;
        }
        else if(getX() - xTarget > 0 && getY() - yTarget > 0) //Food/Animal is on the diagonal (upper left) then run upper left
        {
            direction = 8;
        }
        else if(getX() - xTarget > 0 && getY() - yTarget < 0) //Food/Animal is on the diagonal (lower left) then run lower left
        {
            direction = 6;
        }
        else if(getX() - xTarget < 0 && getY() - yTarget > 0) //Food/Animal is on the diagonal (upper right) then run upper right
        {
            direction = 2;
        }
        else if(getX() - xTarget < 0 && getY() - yTarget < 0) //Food/Animal is on the diagonal (lower right) then run lower right
        {
            direction = 4;
        }
    }
    else
    {
        std::uniform_int_distribution <> random_direction(1, 8);
        direction = random_direction(generator);
    }

    if(ChaseAnimal)
    {
        if(getHunger() >= 15)
        {
            steps = 3;
        }
        else
        {
            steps = 2;
        }
    }
    else
    {
        if(getHunger() >= 15)
        {
            steps = 2;
        }
        else
        {
            steps = 1;
        }
    }

    if(abs(getX()-xTarget) == 1 || abs(getY()-yTarget) == 1 && (ChaseAnimal || ChaseFood)) //making sure the animal doesn't overshoot the target
    {
        steps = 1;
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

    setHunger(getHunger()+2);
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

void Lobo::Eat(std::vector<BaseAnimal*> &animais, std::vector<BaseAlimento*> &alimentos)
{
    std::vector<std::string> Cheiros;
    std::vector<BaseAnimal*> Copy = animais;

    for(auto &it : Copy)
    {
        if(it->getID() != getID() && (it->getX() == getX() && it->getY() == getY() || abs(it->getX() == getX()) == 1 && abs(it->getY() == getY()) == 1))
        {
            if(it->getHide())
            {
                continue;
            }
            if(getPeso() > it->getPeso())
            {
                it->Kill();
            }
            else
            {
                std::random_device random;
                std::mt19937 generator(random());
                std::uniform_int_distribution <> random_death(1,  2);

                if(random_death(generator) == 1)
                {
                    it->Kill();
                }
                else
                {
                    Kill();
                }
            }
            break;
        }
    }

    for(auto &it : alimentos)
    {
        Cheiros = it->getCheiro();
        if(it->getX() == getX() && it->getY() == getY() && std::count(Cheiros.begin(), Cheiros.end(), "carne"))
        {
            if(getHP() + it->getVN() - it->getToxic() >= 0)
            {
                setHP(getHP() + it->getVN() - it->getToxic());
            }
            else if(getHP() + it->getVN() - it->getToxic() <= 0)
            {
                Kill();
            }

            addFood(new History(it->getVN(),it->getToxic(),it->getDescription()));
            it->Kill();
            setHunger(0);
            break;
        }
    }
    animais = Copy;
}

Canguru::Canguru() : idparent(0), child(false), run(false), hide(false), hidetick(0)
{
    InitEspecie('G');
    InitCampoVisao(7);
    InitPeso(10);
    setDescription("Canguru");

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

Canguru::Canguru(const int &x, const int &y) : BaseAnimal{x,y}, AnimalL{x, y}, idparent(0), child(false), run(false), hide(false), hidetick(0)
{
    InitEspecie('G');
    InitCampoVisao(7);
    InitPeso(10);
    setDescription("Canguru");

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

Canguru::Canguru(const int &x, const int &y, const int &idparent) : BaseAnimal{x,y}, AnimalL{x, y}, idparent(idparent), child(true), run(false), hide(false), hidetick(0)
{
    InitEspecie('G');
    InitCampoVisao(7);
    InitPeso(10);
    setDescription("Canguru");

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

void Canguru::Move(const int &tamanho, const std::vector<BaseAnimal*> &animais, const std::vector<BaseAlimento*> &alimentos)
{
    int xTarget = -1;
    int yTarget = -1;
    int direction;
    int steps = 1;
    std::vector<BaseAnimal*> AroundAnimais = checkAroundAnimais(animais, getcampoVisao(), getX(), getY(), getID());

    if(getInstante() == 10 && child)
    {
        child = false;
        run = false;
        hide = false;
        hidetick = 0;
        idparent = 0;
    }
    else if(getInstante() == 20)
    {
        setPeso(20);
    }

    if(!child)
    {
        std::random_device random;
        std::mt19937 generator(random());
        std::uniform_int_distribution <> random_direction(1,  8);
        direction = random_direction(generator);
    }

    else
    {
        for(auto const &it : animais)
        {
            if(it->getID() == idparent)
            {
                xTarget = it->getX();
                yTarget = it->getY();
            }
        }

        if(hide)
        {
            if(xTarget == -1 && yTarget == -1) //if the parent is dead while he's hiding then he dies too
            {
                Kill();
            }
            else if(hidetick == 5)
            {
                hide = false;
                hidetick = 0;
            }
            else
            {
                setX(xTarget);
                setY(yTarget);
                hidetick++;
                return;
            }
        }
        else
        {
            if(run)
            {
                if((abs(getX() - xTarget) <= 1 && abs(getY() - yTarget) <= 1))
                {
                    setX(xTarget);
                    setY(yTarget);
                    hide = true;
                    run = false;
                    return;
                }
                steps = 2;
            }
            if(xTarget != -1 && yTarget != -1) //parent still alive, follow it
            {
                if(getX() - xTarget > 0 && getY() == yTarget) //Parent on the left then run left
                {
                    direction = 7;
                }
                else if(getX() - xTarget < 0 && getY() == yTarget) //Parent on the right then run right
                {
                    direction = 3;
                }
                else if(getX() == xTarget && getY() - yTarget > 0) //Parent is up then run up
                {
                    direction = 1;
                }
                else if(getX() == xTarget && getY() - yTarget < 0) //Parent is down then run down
                {
                    direction = 5;
                }
                else if(getX() - xTarget > 0 && getY() - yTarget > 0) //Parent is on the diagonal (upper left) then run upper left
                {
                    direction = 8;
                }
                else if(getX() - xTarget > 0 && getY() - yTarget < 0) //Parent is on the diagonal (lower left) then run lower left
                {
                    direction = 6;
                }
                else if(getX() - xTarget < 0 && getY() - yTarget > 0) //Parent is on the diagonal (upper right) then run upper right
                {
                    direction = 2;
                }
                else if(getX() - xTarget < 0 && getY() - yTarget < 0) //Parent is on the diagonal (lower right) then run lower right
                {
                    direction = 4;
                }
            }

            for(auto const &it: AroundAnimais)
            {
                if(it->getID() != idparent && !hide)
                {
                    run = true;
                }
            }
        }
    }

    setPos(direction, steps, tamanho);
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
    return new Canguru(xRandom, yRandom, getID());
}

Corpo* Canguru::Die()
{
    return new Corpo(getX(), getY(), 15, 5);
}

bool Canguru::getHide() const
{
    return hide;
}
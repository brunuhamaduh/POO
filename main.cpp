#include <iostream>
#include <string>
#include <iomanip>
#include <vector>
#include <cctype>
#include <algorithm>
#include <random>
#include <fstream>
#include "Terminal.h"
using namespace term;
using namespace std;

class Coordenadas
{
    int x, y;
public:
    Coordenadas(const int &x, const int &y)
    {
        this->x = x;
        this->y = y;
    }
    Coordenadas()
    {
        random_device random;
        mt19937 generator(random());
        uniform_int_distribution <> distr(0, 100);

        x = distr(generator);
        y = distr(generator);
    }
    ~Coordenadas() = default;
    int getX() const {return x;}
    int getY() const {return y;}
    void setX(int xc){x = xc;}
    void setY(int yc){y = yc;}
    friend Window & operator<<(Window & o, const Coordenadas &coordenadas);
};

class Alimento
{
    static int count;
    int ID;
    int ValorNutritivo, Toxicidade, TempodeVida;
    string Cheiro;
    Coordenadas Location;

public:
    Alimento(const int &x, const int &y) : Location(x,y), ID(++count), ValorNutritivo(0), Toxicidade(0), TempodeVida(0) {}
    ~Alimento() = default;
    int getX() const {return Location.getX();}
    int getY() const {return Location.getY();}
};

class Animal
{
    static int count;
    int ID;
protected:
    double Peso;
    char Especie;
    int HP;
    Coordenadas Location;
public:
    Animal(const int &x, const int &y) : Location(x,y), ID(++count), Peso(0), Especie('C'), HP(100){}
    ~Animal() = default;
    int getX() const {return Location.getX();}
    int getY() const {return Location.getY();}
    int getID() const {return ID;}
    char getEspecie() const {return Especie;}
    int getHP() const {return HP;}
};

class Reserva
{
    int Instante;
    vector<Coordenadas> Extremos;
    vector<Animal> Animais;
    vector<Alimento> Alimentos;

public:
    Reserva() : Instante(0){ }
    ~Reserva() = default;
    int getInstante() const {return Instante;}
    vector<Coordenadas> getCoordenadas() const {return Extremos;}
    void newAnimal(const int &x, const int &y) {Animais.emplace_back(Animal(x,y));}
    void newAlimento(const int &x, const int &y) {Alimentos.emplace_back(Alimento(x,y));}
    void setLimits(const int &x, const int &y)
    {
        Extremos.emplace_back(Coordenadas(0,0)); //Superior Esquerdo
        Extremos.emplace_back(Coordenadas(x,0)); //Superior Direito
        Extremos.emplace_back(Coordenadas(0,y)); //Inferior Esquerdo
        Extremos.emplace_back(Coordenadas(x,y)); //Inferior Direito
    }
    string getAnimais()
    {
        ostringstream output;
        for (auto& it : Animais)
        {
            output << it.getID() << " " << it.getEspecie() << " " << it.getHP() << endl;
        }
        return output.str();
    }
    string getAnimalX() const
    {
        ostringstream output;
        for (auto& it : Animais)
        {
            output << it.getX() << endl;
        }
        return output.str();
    }
    string getAnimalY() const
    {
        ostringstream output;
        for (auto& it : Animais)
        {
            output << it.getY() << endl;
        }
        return output.str();
    }
    string getAlimentoX() const
    {
        ostringstream output;
        for (auto& it : Alimentos)
        {
            output << it.getX() << endl;
        }
        return output.str();
    }
    string getAlimentoY() const
    {
        ostringstream output;
        for (auto& it : Alimentos)
        {
            output << it.getY() << endl;
        }
        return output.str();
    }
    int countAnimal() const
    {
        return Animais.size();
    }
    int countAlimento() const
    {
        return Alimentos.size();
    }
};

int Animal::count = 0;
int Alimento::count = 0;

Window & operator<<(Window & o, const Coordenadas &coordenadas)
{
    o << coordenadas.x << " " << coordenadas.y << "\n";
    return o;
}

Window & operator<<(Window & o, const vector<Coordenadas> n)
{
    for (auto& it : n)
    {
        o << it;
    }
    return o;
}

int isNumber(const string &listComando)
{
    for(int i = 0; listComando[i] != '\0'; i++)
    {
        if (isdigit(listComando[i]) == 0)
        {
            return 0;
        }
    }
    return 1;
}

bool isValid(const string &comando, vector<string> &listComando)
{
    char letra;
    stringstream Comando(comando);
    string Palavra;

    listComando.clear();
    while (Comando >> Palavra)
    {
        listComando.push_back(Palavra);
    }

    if(listComando[0] == "KEY_UP" || listComando[0] == "KEY_DOWN" || listComando[0] == "KEY_RIGHT" || listComando[0] == "KEY_LEFT")
    {
        return true;
    }

    if(listComando[0] == "animal") //criar animal (posiçao aleatoria / posiçao aleatoria)
    {
        if((listComando.size() == 2 && listComando[1].size() == 1) || (listComando.size() == 4 && listComando[1].size() == 1 && isNumber(listComando[2]) == 1 && isNumber(listComando[3]) == 1)) //posiçao aleatoria
        {
            letra = listComando[1][0];
            if(isalpha(letra) != 0 && (letra == 'c' || letra == 'o' || letra == 'l' || letra == 'g' || letra == 'm')) //coelho/ovelha/lobo/canguru/misterio
            {
                return true;
            }
        }
    }
    else if(listComando[0] == "kill") //matar animal por posiçao
    {
        if(listComando.size() == 3 && isNumber(listComando[1]) == 1 && isNumber(listComando[2]) == 1)
        {
            return true;
        }
    }
    else if(listComando[0] == "killid") //matar animal por id
    {
        if(listComando.size() == 2 && isNumber(listComando[1]) == 1)
        {
            return true;
        }
    }
    else if(listComando[0] == "food") //colocar alimento (posiçao aleatoria / posiçao aleatoria)
    {
        if((listComando.size() == 2 && listComando[1].size() == 1) || (listComando.size() == 4 && listComando[1].size() == 1 && isNumber(listComando[2]) == 1 && isNumber(listComando[3]) == 1))
        {
            letra = listComando[1][0];
            if(isalpha(letra) != 0 && (letra == 'r' || letra == 't' || letra == 'b' || letra == 'a')) //relva/cenoura/bife/misterio
            {
                return true;
            }
        }
    }
    else if(listComando[0] == "feed") //alimentar diretamente animais (por linha/coluna)
    {
        if(listComando.size() == 5 && isNumber(listComando[1]) == 1 && isNumber(listComando[2]) == 1 && isNumber(listComando[3]) == 1 && isNumber(listComando[4]) == 1)
        {
            return true;
        }
    }
    else if(listComando[0] == "feedid") //alimentar diretamente animais (por linha/coluna)
    {
        if(listComando.size() == 4 && isNumber(listComando[1]) == 1 && isNumber(listComando[2]) == 1 && isNumber(listComando[3]) == 1)
        {
            return true;
        }
    }
    else if(listComando[0] == "nofood") //remover alimento
    {
        if((listComando.size() == 3 && isNumber(listComando[1]) == 1 && isNumber(listComando[2]) == 1) ||(listComando.size() == 2 && isNumber(listComando[1]) == 1) )
        {
            return true;
        }
    }
    else if(listComando[0] == "empty") //eliminar o que quer que esteja numa posicao
    {
        if(listComando.size() == 3 && isNumber(listComando[1]) == 1 && isNumber(listComando[2]) == 1)
        {
            return true;
        }
    }
    else if(listComando[0] == "see") //ver o que se encontra numa posicao
    {
        if(listComando.size() == 3 && isNumber(listComando[1]) == 1 && isNumber(listComando[2]) == 1)
        {
            return true;
        }
    }
    else if(listComando[0] == "info") //ver informacao acerca de um elemento do simulador (animal ou alimento)
    {
        if(listComando.size() == 2 && isNumber(listComando[1]) == 1)
        {
            return true;
        }
    }
    else if(listComando[0] == "n") //passar para o instante seguinte da simulacao
    {
        if((listComando.size() == 1) || (listComando.size() == 2 && isNumber(listComando[1]) == 1) || (listComando.size() == 3 && isNumber(listComando[1]) == 1 && isNumber(listComando[2]) == 1))
        {
            return true;
        }
    }
    else if(listComando[0] == "anim" || listComando[0] == "visanim") //listar id dos animais da reserva ou listar id dos animais visiveis da reserva
    {
        if(listComando.size() == 1)
        {
            return true;
        }
    }
    else if(listComando[0] == "store" || listComando[0] == "restore" || listComando[0] == "load") //armazenar o estado da reserva em memoria ou reativar um estado de reserva previamente armazenado em memoria
    {
        if(listComando.size() == 2)
        {
            return true;
        }
    }
    else if(listComando[0] == "slide") //deslocar a area de visualizacao
    {
        if((listComando.size() == 4 && isNumber(listComando[2]) == 1 && isNumber(listComando[3]) == 1))
        {
            if(listComando[1] == "up" || listComando[1] == "down" || listComando[1] == "right" || listComando[1] == "left")
            {
                return true;
            }
        }
    }
    return false;
}

void mostraReserva(Reserva &principal, Window &reserva, Window &out, string &input, vector<Coordenadas> &viewarea, const vector<Coordenadas> &viewablearea)
{
    vector<int> AnimalXCoordinates;
    vector<int> AnimalYCoordinates;
    vector<int> AlimentoXCoordinates;
    vector<int> AlimentoYCoordinates;
    stringstream processa;

    if(viewarea.empty())
    {
        viewarea.emplace_back(Coordenadas(0,0)); //Superior Esquerdo
        viewarea.emplace_back(Coordenadas(90,0)); //Superior Direito
        viewarea.emplace_back(Coordenadas(0,27)); //Inferior Esquerdo
        viewarea.emplace_back(Coordenadas(90,27)); //Inferior Direito
    }

    int num;
    processa << principal.getAnimalX();

    while(processa >> num)
    {
        AnimalXCoordinates.push_back(num);
    }

    processa.clear();
    processa.str("");

    processa << principal.getAnimalY();

    while(processa >> num)
    {
        AnimalYCoordinates.push_back(num);
    }

    processa.clear();
    processa.str("");

    processa << principal.getAlimentoX();

    while(processa >> num)
    {
        AlimentoXCoordinates.push_back(num);
    }

    processa.clear();
    processa.str("");

    processa << principal.getAlimentoY();

    while(processa >> num)
    {
        AlimentoYCoordinates.push_back(num);
    }

    if(input == "KEY_RIGHT" && viewarea[1].getX() < viewablearea[1].getX())
    {
        for(int i = 0; i < viewarea.size(); i++)
        {
            viewarea[i].setX(viewarea[i].getX()+1);
        }
    }

    else if(input == "KEY_LEFT" && viewarea[0].getX() > viewablearea[0].getX())
    {
        for(int i = 0; i < viewarea.size(); i++)
        {
            viewarea[i].setX(viewarea[i].getX()-1);
        }
    }

    else if(input == "KEY_UP" && viewarea[0].getY() > viewablearea[0].getY())
    {
        for(int i = 0; i < viewarea.size(); i++)
        {
            viewarea[i].setY(viewarea[i].getY()-1);
        }
    }

    else if(input == "KEY_DOWN" && viewarea[2].getY() < viewablearea[2].getY())
    {
        for(int i = 0; i < viewarea.size(); i++)
        {
            viewarea[i].setY(viewarea[i].getY()+1);
        }
    }

    reserva.clear();
    reserva << "";
    for(int i = 0; i < AnimalXCoordinates.size(); i++)
    {
        if((AnimalXCoordinates[i] >= viewarea[0].getX() && AnimalXCoordinates[i] <= viewarea[1].getX()) && (AnimalYCoordinates[i] >= viewarea[0].getY()) && (AnimalYCoordinates[i] <= viewarea[3].getY()))
        {
            reserva << move_to(AnimalXCoordinates[i]-viewarea[0].getX(), AnimalYCoordinates[i]-viewarea[0].getY());
            reserva << "C";
        }
    }
    for(int i = 0; i < AlimentoXCoordinates.size(); i++)
    {
        if((AlimentoXCoordinates[i] >= viewarea[0].getX() && AlimentoXCoordinates[i] <= viewarea[1].getX()) && (AlimentoYCoordinates[i] >= viewarea[0].getY()) && (AlimentoYCoordinates[i] <= viewarea[3].getY()))
        {
            reserva << move_to(AlimentoXCoordinates[i]-viewarea[0].getX(), AlimentoYCoordinates[i]-viewarea[0].getY());
            reserva << "X";
        }
    }
}

void mostra(Window &comando, Window &info, Window &out, Reserva &principal)
{
    comando.clear();
    info.clear();
    comando << "Comando: ";
    info << "Instante: " << principal.getInstante() << "\n";
    info << "Animais Vivos: " << principal.countAnimal() << "\n";
    info << "Comida: " << principal.countAlimento() << "\n";
    info << "Extremos: ";
    info << principal.getCoordenadas();
}

void leComandos(const string &name, Window &out, vector<string> &listComando)
{
    string line;
    ifstream comandos(name);
    if (comandos.is_open())
    {
        while (getline(comandos,line))
        {
            if(!isValid(line, listComando))
            {
                out << "Comando invalido";
            }
        }
        comandos.close();
    }
    else
    {
        out << "Erro ao abrir ficheiro\n";
    }
}

void leConstantes(Window &out, Reserva &principal)
{
    string line;
    int x, y;
    ifstream constantes("constantes.txt");
    if (constantes.is_open())
    {
        getline(constantes,line);
        istringstream p(line);
        p >> x >> y;
        principal.setLimits(x, y);
        constantes.close();
    }
    else
    {
        out << "Erro ao abrir ficheiro\n";
    }
}

void displayEverything(Reserva &principal, Window &out)
{
    out << principal.getAnimais();
}

void displayScreen(Reserva &principal, Window &out, vector<Coordenadas> &viewarea, const vector<Coordenadas> &viewablearea)
{
    vector<int> AnimalXCoordinates;
    vector<int> AnimalYCoordinates;
    stringstream processa;
    int num;

    processa << principal.getAnimalX();

    while(processa >> num)
    {
        AnimalXCoordinates.push_back(num);
    }

    processa.clear();
    processa.str("");

    processa << principal.getAnimalY();

    while(processa >> num)
    {
        AnimalYCoordinates.push_back(num);
    }

    for(int i = 0; i < AnimalXCoordinates.size(); i++)
    {
        if((AnimalXCoordinates[i] >= viewarea[0].getX() && AnimalXCoordinates[i] <= viewarea[1].getX()) && (AnimalYCoordinates[i] >= viewarea[0].getY()) && (AnimalYCoordinates[i] <= viewarea[3].getY()))
        {
            //FAZER ISTO
        }
    }
}

int main()
{
    //Inicio (30x120)
    Terminal &t = Terminal::instance();

    Window comando = Window(0, 27, 90, 3);
    Window info = Window(90, 0, 30, 9);
    Window reserva = Window(0, 0, 90, 27);
    Window out = Window(90,9,30,21);
    //Fim

    string input;
    vector<string> listComando;
    Reserva principal;
    leConstantes(out, principal);

    static vector<Coordenadas> viewarea;
    const vector<Coordenadas> viewablearea = principal.getCoordenadas();

    principal.newAnimal(5,5);
    principal.newAnimal(20, 20);
    principal.newAlimento(10, 10);
    do
    {
        out.clear();
        mostra(comando, info, out, principal);
        mostraReserva(principal, reserva, out, input, viewarea, viewablearea);
        comando >> input;
        if(!isValid(input, listComando))
        {
            out << "Comando invalido";
        }
        else
        {
            if(listComando[0] == "load")
            {
                leComandos(listComando[1], out, listComando);
            }
            else if(listComando[0] == "anim")
            {
                displayEverything(principal, out);
            }
            else if(listComando[0] == "visanim")
            {
                displayScreen(principal, out, viewarea, viewablearea);
            }
        }
    } while(input != "exit");

    return 0;
}
#include <iostream>
#include <string>
#include <iomanip>
#include <vector>
#include <cctype>
#include <algorithm>
#include <random>
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
    ~Coordenadas() {}
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
};

class Animal
{
    static int count;
    int ID;
protected:
    string nome;
    double Peso;
    string Especie;
    string EstadoSaude;

    Coordenadas Location;
public:
    Animal(const string &nome, const int &x, const int &y) : Location(x,y), ID(++count), nome(nome) {}
    Animal() : ID(++count) {}
    ~Animal() {}
    int getX() const {return Location.getX();}
    int getY() const {return Location.getY();}
    string getName() const {return nome;}
    friend Window & operator<<(Window & o, const Animal &animais);
};

class Reserva
{
    int Instante, animalcount, alimentocount;
    vector<Coordenadas> Extremos;
    vector<Animal> Animais;
    vector<Alimento> Alimentos;

public:
    Reserva() : Instante(0), animalcount(0), alimentocount(0)
    {
        Extremos.emplace_back(Coordenadas(0,0)); //Superior Esquerdo
        Extremos.emplace_back(Coordenadas(200,0)); //Superior Direito
        Extremos.emplace_back(Coordenadas(0,200)); //Inferior Esquerdo
        Extremos.emplace_back(Coordenadas(200,200)); //Inferior Direito
    }
    ~Reserva() {}
    const int getInstante() {return Instante;}
    const vector<Coordenadas> getCoordenadas() {return Extremos;}
    const vector<Animal> getAnimais() {return Animais;}
    const vector<Alimento> getAlimentos() {return Alimentos;}
    void newAnimal(const int &x, const int &y, const string &nome)
    {
        Animais.emplace_back(Animal(nome,x,y));
        animalcount++;
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
};

int Animal::count = 0;
int Alimento::count = 0;

Window & operator<<(Window & o, const Coordenadas &coordenadas)
{
    o << coordenadas.x;
    o << "|";
    o << coordenadas.y;
    o << "\n";
    return o;
}

Window & operator<<(Window & o, const Animal &animais)
{
    o << animais.getName() << " " << animais.getX() << " " << animais.getY();
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

Window & operator<<(Window & o, const vector<Animal> n)
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

void mostraReserva(Reserva &principal, Window &reserva, Window &out, string &input)
{
    vector<int> XCoordinates;
    vector<int> YCoordinates;
    stringstream processa;
    const vector<Coordenadas> viewablearea = principal.getCoordenadas();
    static vector<Coordenadas> viewarea;
    static int x = 0;
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
        XCoordinates.push_back(num);
    }

    processa.clear();
    processa.str("");

    processa << principal.getAnimalY();

    while(processa >> num)
    {
        YCoordinates.push_back(num);
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
    for(int i = 0; i < XCoordinates.size(); i++)
    {
        if((XCoordinates[i] >= viewarea[0].getX() && XCoordinates[i] <= viewarea[1].getX()) && (YCoordinates[i] >= viewarea[0].getY()) && (YCoordinates[i] <= viewarea[3].getY()))
        {
            reserva << move_to(XCoordinates[i]-viewarea[0].getX(), YCoordinates[i]-viewarea[0].getY());
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
    //info << "Animais Vivos: " << principal.CountAnimal() << "\n";
    //info << "Comida: " << principal.CountAlimento() << "\n";
    info << "Extremos: ";
    info << principal.getCoordenadas();
}

void writeOut(Window &out)
{
    static int x = 0;
    if(x < 19)
    {
        out << "Comando invalido\n";
        x++;
    }
    else
    {
        x = 0;
        out.clear();
        out << "Comando invalido\n";
        x++;
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
    principal.newAnimal(5,5,"Francisca");
    principal.newAnimal(10,10,"Francisca");
    principal.newAnimal(50,50,"Francisca");
    do
    {
        mostra(comando, info, out, principal);
        mostraReserva(principal, reserva, out, input);
        comando >> input;
        if(!isValid(input, listComando))
        {
            writeOut(out);
        }
    } while(input != "exit");

    return 0;
}
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
    int getX() {return x;}
    int getY() {return y;}
};

class Alimento
{
    int ValorNutritivo, Toxicidade, TempodeVida;
    string Cheiro;
    Coordenadas Location;
};

class Animal
{
    static int count;
    int ID;
protected:
    double Peso;
    Coordenadas Location;
    string Especie;
    string EstadoSaude;

public:
    Animal(const int &x, const int &y) : Location(x,y), ID(++count) {}
    Animal() : ID(++count) {}
    int getX() {return Location.getX();}
    int getY() {return Location.getY();}
};

class Reserva
{
    int Instante;
    vector<Coordenadas> Extremos;
    vector<Animal> Animais;
    vector<Alimento> Alimentos;
};

int Animal::count = 0;

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

bool isValid(const string &comando, vector<string> &listComando, Window &out)
{
    char letra;
    stringstream Comando(comando);
    string Palavra;

    listComando.clear();
    while (Comando >> Palavra)
    {
        listComando.push_back(Palavra);
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

void limpa(Terminal &t, Window &comando, Window &info, Window &reserva, Window &out)
{
    comando.clear();
    info.clear();
    reserva.clear();
    out.clear();
}

void mostra(Terminal &t, Window &comando, Window &info, Window &reserva, Window &out)
{
    limpa(t, comando, info, reserva, out);
    comando << "Comando: \n";
    info << "Instante: \n";
    info << "Animais Vivos: \n";
    info << "Comida: \n";
    info << "Extremos: \n";
}

int main()
{
    //Inicio (30x120)
    Terminal &t = Terminal::instance();
    Window comando = Window(0, 27, 90, 3);
    Window info = Window(90, 0, 30, 6);
    Window reserva = Window(0, 0, 90, 27);
    Window out = Window(90,6,30,24);
    //Fim

    string input;
    vector<string> listComando;
    Animal teste;

    do
    {
        mostra(t, comando, info, reserva, out);
        comando >> input;
        isValid(input, listComando, out);
    } while(input != "exit");

    return 0;
}
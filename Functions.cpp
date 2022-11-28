#include "Functions.h"
#include <iomanip>
#include <fstream>

int isNumber(const std::string &listComando)
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

bool isValid(const std::string &comando, std::vector<std::string> &listComando)
{
    char letra;
    std::stringstream Comando(comando);
    std::string Palavra;

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
    else if(listComando[0] == "kill" || listComando[0] == "empty" || listComando[0] == "see") //matar animal por posiçao
    {
        if(listComando.size() == 3 && isNumber(listComando[1]) == 1 && isNumber(listComando[2]) == 1)
        {
            return true;
        }
    }

    else if(listComando[0] == "killid" || listComando[0] == "info") //matar animal por id
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

void displayEverything(Reserva &principal, term::Window &out)
{
    out << "ANIMAIS\n";
    out << principal.getAnimais();
    out << "ALIMENTOS\n";
    out << principal.getAlimentos();
}

void displayScreen(Reserva &principal, term::Window &out, std::vector<int> &viewarea, const std::vector<Coordenadas> &viewablearea)
{
    std::string detalhes;
    std::stringstream processa(principal.getAnimaisPos(viewarea[0],viewarea[1],viewarea[2],viewarea[3]));

    if(!processa.str().empty())
    {
        out << "ANIMAIS\n";
        out << processa.str();
    }

    processa.clear();
    processa.str("");

    processa.str(principal.getAlimentosPos(viewarea[0],viewarea[1],viewarea[2],viewarea[3]));
    if(!processa.str().empty())
    {
        out << "ALIMENTOS\n";
        out << processa.str();
    }
}

void mostraReserva(Reserva &principal, term::Window &reserva, term::Window &out, std::string &input, std::vector<int> &viewarea, const std::vector<Coordenadas> &viewablearea)
{
    int ID, HP, X, Y, VN, Toxic, TV;
    char Especie;
    std::stringstream processa;

    if(input == "KEY_RIGHT" && viewarea.at(1) < viewablearea[1].getX())
    {
        viewarea.at(0)++;
        viewarea.at(1)++;
    }

    else if(input == "KEY_LEFT" && viewarea.at(0) > viewablearea[0].getX())
    {
        viewarea.at(0)--;
        viewarea.at(1)--;
    }

    else if(input == "KEY_UP" && viewarea.at(2) > viewablearea[0].getY())
    {
        viewarea.at(2)--;
        viewarea.at(3)--;
    }

    else if(input == "KEY_DOWN" && viewarea.at(3) < viewablearea[2].getY())
    {
        viewarea.at(2)++;
        viewarea.at(3)++;
    }

    processa.str(principal.getAnimaisPos(viewarea[0],viewarea[1],viewarea[2],viewarea[3]));

    while(processa >> ID >> Especie >> HP >> X >> Y)
    {
        reserva << term::move_to(X - viewarea.at(0), Y - viewarea.at(2));
        reserva << Especie;
    }

    processa.clear();
    processa.str("");
    processa.str(principal.getAlimentosPos(viewarea[0],viewarea[1],viewarea[2],viewarea[3]));

    while(processa >> ID >> VN >> Toxic >> TV >> X >> Y)
    {
        reserva << term::move_to(X - viewarea.at(0), Y - viewarea.at(2));
        reserva << "X";
    }
}

void mostra(term::Window &comando, term::Window &info, term::Window &out, Reserva &principal)
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

void leComandos(term::Window &out, std::vector<std::string> &listComando, Reserva &principal, std::vector<int> &viewarea, const std::vector<Coordenadas> &viewablearea)
{
    std::string line;
    std::ifstream comandos(listComando[1]);
    if (comandos.is_open())
    {
        while (getline(comandos,line))
        {
            if(!isValid(line, listComando))
            {
                out << "Comando invalido";
            }
            else
            {
                if(listComando[0] == "anim")
                {
                    displayEverything(principal, out);
                }
                else if(listComando[0] == "visanim")
                {
                    displayScreen(principal, out, viewarea, viewablearea);
                }
            }
        }
        comandos.close();
    }
    else
    {
        out << "Erro ao abrir ficheiro\n";
    }
}

void leConstantes(term::Window &out, int &x, int &y)
{
    std::string line;
    std::ifstream constantes("constantes.txt");
    if (constantes.is_open())
    {
        getline(constantes,line);
        std::istringstream p(line);
        p >> x >> y;
        constantes.close();
    }
    else
    {
        out << "Erro ao abrir ficheiro\n";
    }
}
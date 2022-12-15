#include "Functions.h"
#include <iomanip>
#include <fstream>

int getID()
{
    static int i = 0;
    return ++i;
}

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

void executeInput(std::string &input, std::vector<std::string> &listComando, Reserva &principal, term::Window &out)
{
    if(!isValid(input, listComando))
    {
        out << "Comando invalido";
    }
    else if(input != "KEY_UP" && input != "KEY_DOWN" && input != "KEY_RIGHT" && input != "KEY_LEFT")
    {
        out << "";
        if(listComando[0] == "load")
        {
            leComandos(out, listComando, principal);
        }
        else if(listComando[0] == "anim")
        {
            displayEverything(principal, out);
        }
        else if(listComando[0] == "visanim")
        {
            displayScreen(principal, out);
        }
        else if(listComando[0] == "animal")
        {
            if(listComando[1] == "c")
            {
                principal.newAnimal(getID(), 20, 20, 'C');
            }
        }
    }
}

void displayEverything(Reserva &principal, term::Window &out)
{
    if(principal.countAnimal() != 0)
    {
        out << "ANIMAIS\n";
        out << principal.getAnimais();
    }

    if(principal.countAlimento() != 0)
    {
        out << "ALIMENTOS\n";
        out << principal.getAlimentos();
    }
}

void displayScreen(Reserva &principal, term::Window &out)
{
    std::vector<int> viewarea = principal.getVArea();
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

void mostra(Reserva &principal, term::Window &reserva, term::Window &comando, term::Window &info, term::Window &out, std::string &input)
{
    int ID, HP, X, Y, VN, Toxic, TV;
    char letra;
    std::stringstream processa;
    std::vector<int> viewarea = principal.getVArea();
    int limite = principal.getArea();

    reserva.clear();
    out.clear();
    comando.clear();
    info.clear();
    reserva << "";

    if(input == "KEY_RIGHT" && viewarea.at(1) < limite)
    {
        principal.change_VArea(0, true);
        principal.change_VArea(1, true);
    }

    else if(input == "KEY_LEFT" && viewarea.at(0) > 0)
    {
        principal.change_VArea(0, false);
        principal.change_VArea(1, false);
    }

    else if(input == "KEY_UP" && viewarea.at(2) > 0)
    {
        principal.change_VArea(2, false);
        principal.change_VArea(3, false);
    }

    else if(input == "KEY_DOWN" && viewarea.at(3) < limite)
    {
        principal.change_VArea(2, true);
        principal.change_VArea(3, true);
    }

    viewarea = principal.getVArea();
    processa.str(principal.getAnimaisPos(viewarea[0],viewarea[1],viewarea[2],viewarea[3]));

    while(processa >> ID >> letra >> HP >> X >> Y)
    {
        reserva << term::move_to(X - viewarea.at(0), Y - viewarea.at(2));
        reserva << letra;
    }

    processa.clear();
    processa.str("");
    processa.str(principal.getAlimentosPos(viewarea[0],viewarea[1],viewarea[2],viewarea[3]));

    while(processa >> ID >> VN >> Toxic >> TV >> X >> Y)
    {
        reserva << term::move_to(X - viewarea.at(0), Y - viewarea.at(2));
        reserva << "X";
    }

    comando << "Comando: ";
    info << "Instante: " << principal.getInstante() << "\n";
    info << "Animais Vivos: " << principal.countAnimal() << "\n";
    info << "Comida: " << principal.countAlimento() << "\n";
    info << "Extremos: \n";
    info << viewarea[0] << " " << viewarea[2] << " | " << viewarea[1] << " " << viewarea[2] << "\n";
    info << viewarea[0] << " " << viewarea[3] << " | " << viewarea[1] << " " << viewarea[3];
}

void leComandos(term::Window &out, std::vector<std::string> &listComando, Reserva &principal)
{
    std::vector<int> viewarea = principal.getVArea();
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
                    displayScreen(principal, out);
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

void startGame(term::Window &comando, std:: string &input, Reserva &principal)
{
    do
    {
        comando << "Tamanho da reserva: ";
        comando >> input;
        comando.clear();
        comando << "";
    } while(stoi(input) < 16 || stoi(input) > 500);

    principal.setSize(stoi(input));
}

void loopGame(Reserva &principal, term::Window &reserva, term::Window &comando, term::Window &info, term::Window &out, std::string input, std::vector<std::string> &listComando)
{
    do
    {
        mostra(principal, reserva, comando, info, out, input);
        comando >> input;
        executeInput(input, listComando, principal, out);
    } while(input != "exit");
}
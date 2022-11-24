#include <iostream>
#include <string>
#include <iomanip>
#include <vector>
#include <cctype>
#include "Terminal.h"
using namespace term;
using namespace std;

class Animal
{
    static int count;
    int ID, x, y;
protected:
    float Peso;
    string Especie;
    string EstadoSaude;

public:
    Animal():ID(++count){}
    int getID() {return ID;}
    int getPeso() {return Peso;}
    string getEspecie() {return Especie;}
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

bool isValid(const string &comando, vector<string> &listComando, Window &erro)
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
                erro << "Teste";
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


    return false;
}

void limpa(Terminal &t, Window &comando, Window &info, Window &reserva, Window &erro)
{
    comando.clear();
    info.clear();
    reserva.clear();
    erro.clear();
}

void mostra(Terminal &t, Window &comando, Window &info, Window &reserva, Window &erro)
{
    limpa(t, comando, info, reserva, erro);
    comando << "Comando: \n";
    info << "Instante: \n";
    info << "Animais Vivos: \n";
    info << "Comida: \n";
    info << "Extremos: \n";
}

int main(void)
{
    //Inicio (30x120)
    Terminal &t = Terminal::instance();
    Window comando = Window(0, 27, 100, 3);
    Window info = Window(100, 0, 20, 27);
    Window reserva = Window(0, 0, 100, 27);
    Window erro = Window(100,27,20,3);
    //Fim

    string input;
    vector<string> listComando;

    do
    {
        mostra(t, comando, info, reserva, erro);
        comando >> input;
        isValid(input, listComando, erro);
    } while(input != "exit");

    return 0;
}


//Leitura do ficheiro de comandos e também dos valores do ficheiro constantes.txt.
//Construção da reserva. A representação da reserva irá ser melhorada com matéria dada posteriormente e agora só se pretende algo que possa ser representado no ecrã.
//Definição do conceito de Animal. Não é preciso considerar as variações inerentes às espécie e deve mesmo limitar-se aquilo que é genérico e comum a todos.
//Definição do conceito de Alimento. Idem focar apenas o que é comum a todos os alimentos.
//Representação visual da reserva e conteúdo incluído nesta meta. Inclui-se aqui a questão de ver apenas a área visível da reserva.
//Implementação da leitura e validação de todos os comandos, seja por teclado, ou seja por leitura do ficheiro de comandos. Os comandos não farão ainda nada, mas devem ser já interpretados e validados, incluindo a sintaxe de todos os parâmetros que tenham.
//Implementar os comandos para: ver animais e alimentos, deslizar a área visível para o lado/cima/abaixo, executar comandos em ficheiro (que são também validados), e terminar.
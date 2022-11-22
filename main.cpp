#include <iostream>
#include <string>
#include <iomanip>
#include "Terminal.h"
using namespace term;
using namespace std;

class Animal
{

};

class Coelho: private Animal
{

};

void print_size(Terminal& t)
{
    std::ostringstream o;
    o << std::setw(7) << t.getNumCols() << "x" << t.getNumRows();
    std::string str = o.str();
    t.clear();
    t << set_color(0) << move_to(t.getNumCols()-str.length(), t.getNumRows()-1) << str;
}

int main()
{
    int instante = 0, animaisvivos = 0, quantidadecomida = 0;
    int tamanho = 20;
    Terminal &t = Terminal::instance();

    for(int i=0; i<=tamanho*2; i++)
    {
        for(int j=0; j<=tamanho; j++)
        {
            t << move_to(i, j)  << "_";
        }
    }

    t << move_to(tamanho*2+2,0) << "Instante: " << instante;
    t << move_to(tamanho*2+2,1) << "Animais Vivos: " << animaisvivos;
    t << move_to(tamanho*2+2,2) << "Quantidade de comida: " << quantidadecomida;
    t << move_to(tamanho*2+2,3) << "Extremos: (0,0) (" << tamanho << ",0) (" << tamanho << "," << tamanho << ") (0," << tamanho << ")";

    t << move_to(0,22) << "Comando = ";

    t.getchar();
    print_size(t);
}
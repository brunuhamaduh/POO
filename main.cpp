#include <iostream>
#include "Headers/Functions.h"

int main()
{
    //Tamanho default do terminal (30x120)
    term::Terminal &t = term::Terminal::instance();
    term::Window comando = term::Window(0, 27, 90, 3);
    term::Window info = term::Window(90, 0, 30, 8);
    term::Window reserva = term::Window(0, 0, 90, 27);
    term::Window out = term::Window(90,8,30,22);

    std::string input;
    std::vector<std::string> listComando;
    Reserva principal;

    //leConstantes(out,  x, y);

    startGame(comando, input, principal);
    loopGame(principal, reserva, comando, info, out, input, listComando);
    return 0;
}
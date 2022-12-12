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

    //meta 1 only
    principal.newAnimal(getID(), 5, 5);
    principal.newAnimal(getID(), 20, 20);
    principal.newAnimal(getID(), 50, 50);
    principal.newAlimento(getID(), 20, 50);
    //meta 1 only

    do {
        comando << "Tamanho da reserva: ";
        comando >> input;
        comando.clear();
        comando << "";
    } while(stoi(input) < 16 || stoi(input) > 500);

    do
    {
        mostra(principal, reserva, comando, info, out, input);
        comando >> input;
        executeInput(input, listComando, principal, out);
    } while(input != "exit");
    return 0;
}
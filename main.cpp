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

void mostra(Terminal &t, Window &comando, Window &info, Window &reserva)
{
    string input;
    comando << "Comando: \n";
    info << "Instante: \n";
    info << "Animais Vivos: \n";
    info << "Comida: \n";
    info << "Extremos: \n";
    comando >> input;
}

int main()
{
    Terminal &t = Terminal::instance();

    //30x120
    Window comando = Window(0, 27, 100, 3);
    Window info = Window(100, 0, 20, 30);
    Window reserva = Window(0, 0, 100, 27);
    mostra(t, comando, info, reserva);
}
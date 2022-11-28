#include <iostream>
#include <fstream>
#include <iomanip>
#include "Functions.h"

int main()
{
    //Inicio (30x120)
    term::Terminal &t = term::Terminal::instance();

    term::Window comando = term::Window(0, 27, 90, 3);
    term::Window info = term::Window(90, 0, 30, 9);
    term::Window reserva = term::Window(0, 0, 90, 27);
    term::Window out = term::Window(90,9,30,21);
    //Fim

    int x, y;
    std::string input;
    std::vector<std::string> listComando;
    Reserva principal;
    std::stringstream ficheiro;

    leConstantes(out,  x, y);
    principal.setLimits(x, y);

    std::vector<int> viewarea = {0, 87, 0, 24};
    const std::vector<Coordenadas> viewablearea = principal.getCoordenadas();

    principal.newAnimal(5,5);
    principal.newAnimal(20, 20);
    principal.newAnimal(88, 25);
    principal.newAlimento(50, 5);
    principal.newAlimento(160, 160);

    do
    {
        reserva.clear();
        reserva << "";
        out.clear();

        mostra(comando, info, out, principal);
        mostraReserva(principal, reserva, out, input, viewarea, viewablearea);
        comando >> input;

        if(!isValid(input, listComando))
        {
            out << "Comando invalido";
        }
        else if(input != "KEY_UP" && input != "KEY_DOWN" && input != "KEY_RIGHT" && input != "KEY_LEFT")
        {
            out << "";
            if(listComando[0] == "load")
            {
                leComandos(out, listComando, principal, viewarea, viewablearea);
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
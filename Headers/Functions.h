#ifndef POO_FUNCTIONS_H
#define POO_FUNCTIONS_H

#include "Reserva.h"

int isNumber(const std::string &listComando);
bool isValid(const std::string &comando, std::vector<std::string> &listComando);
void displayEverything(Reserva &principal, term::Window &out);
void displayScreen(Reserva &principal, term::Window &out, std::vector<int> &viewarea, const std::vector<Coordenadas> &viewablearea);
void mostraReserva(Reserva &principal, term::Window &reserva, term::Window &out, std::string &input, std::vector<int> &viewarea, const std::vector<Coordenadas> &viewablearea);
void mostra(term::Window &comando, term::Window &info, term::Window &out, Reserva &principal);
void leComandos(term::Window &out, std::vector<std::string> &listComando, Reserva &principal, std::vector<int> &viewarea, const std::vector<Coordenadas> &viewablearea);
void leConstantes(term::Window &out, int &x, int &y);

#endif //POO_FUNCTIONS_H

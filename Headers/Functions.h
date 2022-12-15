#ifndef POO_FUNCTIONS_H
#define POO_FUNCTIONS_H

#include "Reserva.h"

int getID();
int isNumber(const std::string &listComando);
bool isValid(const std::string &comando, std::vector<std::string> &listComando);
void executeInput(std::string &input, std::vector<std::string> &listComando, Reserva &principal, term::Window &out);
void displayEverything(Reserva &principal, term::Window &out);
void displayScreen(Reserva &principal, term::Window &out);
void mostra(Reserva &principal, term::Window &reserva, term::Window &comando, term::Window &info, term::Window &out, std::string &input);
void leComandos(term::Window &out, std::vector<std::string> &listComando, Reserva &principal);
void startGame(term::Window &comando, std:: string &input, Reserva &principal);
void loopGame(Reserva &principal, term::Window &reserva, term::Window &comando, term::Window &info, term::Window &out, std::string input, std::vector<std::string> &listComando);

#endif //POO_FUNCTIONS_H
#include "Alimento.h"

Alimento::Alimento(const int &x, const int &y) : Location(x,y), ID(++count), ValorNutritivo(0), Toxicidade(0), TempodeVida(0) {}
Alimento::~Alimento() = default;
int Alimento::getX() const {return Location.getX();}
int Alimento::getY() const {return Location.getY();}
int Alimento::getID() const {return ID;}
int Alimento::getVN() const {return ValorNutritivo;}
int Alimento::getToxic() const {return Toxicidade;}
int Alimento::getTV() const {return TempodeVida;}

int Alimento::count = 0;
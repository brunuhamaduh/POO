#include "Animal.h"

Animal::Animal(const int &id, const int &x, const int &y, const char &especie) : Location(x,y), ID(id), HP(100), especie(especie){}
Animal::~Animal() = default;
char Animal::getEspecie() const {return especie;}
int Animal::getX() const {return Location.getX();}
int Animal::getY() const {return Location.getY();}
int Animal::getID() const {return ID;}
int Animal::getHP() const {return HP;}
int Animal::getRange() const {return campoVisao;}
double Animal::getPeso() const {return Peso;}

Coelho::Coelho(const int &id, const int &x, const int &y) : Animal{id, x, y, 'C'} {}
Coelho::~Coelho() = default;
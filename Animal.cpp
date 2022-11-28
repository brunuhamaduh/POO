#include "Animal.h"

Animal::Animal(const int &x, const int &y) : Location(x,y), ID(++count), Especie('C'), HP(100){}
Animal::~Animal() = default;
int Animal::getX() const {return Location.getX();}
int Animal::getY() const {return Location.getY();}
int Animal::getID() const {return ID;}
int Animal::getHP() const {return HP;}
char Animal::getEspecie() const {return Especie;}

int Animal::count = 0;
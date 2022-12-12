#ifndef POO_ALIMENTO_H
#define POO_ALIMENTO_H
#include "Animal.h"

class Alimento
{
    int ID;
    int ValorNutritivo, Toxicidade, TempodeVida;
    std::string Cheiro;
    Coordenadas Location;

public:
    Alimento(const int &id, const int &x, const int &y);
    ~Alimento();
    int getX() const;
    int getY() const;
    int getID() const;
    int getVN() const;
    int getToxic() const;
    int getTV() const;
};

#endif //POO_ALIMENTO_H

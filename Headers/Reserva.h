#ifndef POO_RESERVA_H
#define POO_RESERVA_H

#include "Alimento.h"

class Reserva
{
    int Instante;
    std::vector<Coordenadas> Extremos;
    std::vector<Animal> Animais;
    std::vector<Alimento> Alimentos;

public:
    Reserva();
    ~Reserva();
    int getInstante() const;
    std::vector<Coordenadas> getCoordenadas() const;
    std::string getAnimaisPos(const int &xinf, const int &xsup, const int &yinf, const int &ysup) const;
    std::string getAlimentosPos(const int &xinf, const int &xsup, const int &yinf, const int &ysup) const;
    std::string getAnimais() const;
    std::string getAlimentos() const;
    size_t countAnimal() const;
    size_t countAlimento() const;
    void newAnimal(const int &x, const int &y);
    void newAlimento(const int &x, const int &y);
    void setLimits(const int &x, const int &y);
};

#endif //POO_RESERVA_H

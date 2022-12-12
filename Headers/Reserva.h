#ifndef POO_RESERVA_H
#define POO_RESERVA_H

#include "Alimento.h"

class Reserva
{
    int tamanho, instante;
    std::vector<Animal> Animais;
    std::vector<Alimento> Alimentos;
    std::vector<int> viewarea = {0, 87, 0, 24};

public:
    Reserva();
    ~Reserva();
    int getArea() const;
    std::vector<int> getVArea() const;
    std::string getAnimaisPos(const int &xinf, const int &xsup, const int &yinf, const int &ysup) const;
    std::string getAlimentosPos(const int &xinf, const int &xsup, const int &yinf, const int &ysup) const;
    std::string getAnimais() const;
    std::string getAlimentos() const;
    int getInstante() const;
    size_t countAnimal() const;
    size_t countAlimento() const;
    void newAnimal(const int &id, const int &x, const int &y);
    void newAlimento(const int &id, const int &x, const int &y);
    void change_VArea(const int &index, bool op);
};

#endif //POO_RESERVA_H

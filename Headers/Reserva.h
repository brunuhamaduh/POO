#ifndef POO_RESERVA_H
#define POO_RESERVA_H

#include "Animal.h"

class Reserva
{
    static int ID;
    static int tamanho;
    int instante;
    std::vector<BaseAnimal*> Animais;
    std::vector<BaseAlimento*> Alimentos;
    std::vector<int> viewarea = {0, 87, 0, 24};

public:
    Reserva();
    ~Reserva();
    static int getArea();
    std::vector<int> getVArea() const;
    std::string getAnimaisPos(const int &xinf, const int &xsup, const int &yinf, const int &ysup) const;
    std::string getAlimentosPos(const int &xinf, const int &xsup, const int &yinf, const int &ysup) const;
    std::string getAnimais() const;
    std::string getAlimentos() const;
    std::string displayAnimals() const;
    std::string displayAlimentos() const;
    void setSize(const int &num);
    int getInstante() const;
    size_t countAnimal() const;
    size_t countAlimento() const;
    void newAnimal(const int &x, const int &y, const char &especie);
    void newAlimento(const int &x, const int &y, const char &tipo);
    void change_VArea(const int &index, bool op);
    void advanceInstant(const int &num = 1);
    std::string getInfo(const int &ID);
    static int getID();
};

#endif //POO_RESERVA_H

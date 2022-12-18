#ifndef POO_ALIMENTO_H
#define POO_ALIMENTO_H
#include "Animal.h"

class BaseAlimento
{
    int ID;
    int ValorNutritivo, Toxicidade;
    char letra;
    std::vector<std::string> Cheiro;
    Coordenadas Location;

protected:
    BaseAlimento();
    BaseAlimento(const int &x, const int &y);

public:
    ~BaseAlimento();
    int getX() const;
    int getY() const;
    int getID() const;
    int getVN() const;
    int getToxic() const;
    virtual int getTV() const = 0;

    void InitVN(const int &num);
    void InitToxic(const int &num);
    void InitLetra(const char &letr);
    void InitCheiro(const std::vector<std::string> &cheiros);
};

class AlimentoTV: virtual public BaseAlimento
{
    int TempodeVida;
protected:
    AlimentoTV();
    AlimentoTV(const int &x, const int &y);
    ~AlimentoTV();
    int getTV() const override;
    void InitTV(const int &num);
};

class Relva: public AlimentoTV
{
public:
    Relva();
    Relva(const int &x, const int &y);
    ~Relva();
    //Spawna outra relva aos 75% de TempodeVida (posicao aleatoria entre 4 e 8 de distancia. se a posicao ja tiver um alimento, nao acontece nada e tenta novamente no instante seguinte
};

class Cenoura: public BaseAlimento
{
public:
    Cenoura();
    Cenoura(const int &x, const int &y);
    ~Cenoura();
    //A toxicidade aumenta 1 ponto a cada 10 instantes até ao maximo de 3
};

class Corpo: public BaseAlimento
{
    Corpo(const int &x, const int &y, const int &oldcorpse);
    ~Corpo();
    //A cada instante --valornutritivo e ++toxicidade. (Toxicidade pára de aumentar quando instantes = 2x valornutritivo inicial
};

class Bife: public AlimentoTV
{
    Bife();
    Bife(const int &x, const int &y);
    ~Bife();
    //A cada instante --valornutritivo ate chegar a 0
};

#endif //POO_ALIMENTO_H

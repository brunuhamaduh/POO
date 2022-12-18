#ifndef POO_ALIMENTO_H
#define POO_ALIMENTO_H
#include "Animal.h"

class BaseAlimento
{
    int ID;
    int ValorNutritivo;
    int Toxicidade;
    int Instante;
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
    virtual void Action() = 0;
    int getInstante() const;
    void incInstante();
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
    int instanteSpawn;
public:
    Relva();
    Relva(const int &x, const int &y);
    ~Relva();
    void Action() override;
    //Se a posicao ja tiver um alimento, nao acontece nada e tenta novamente no instante seguinte
};

class Cenoura: public BaseAlimento
{
public:
    Cenoura();
    Cenoura(const int &x, const int &y);
    ~Cenoura();
    void Action() override;
};

class Corpo: public BaseAlimento
{
    int ogVN;
public:
    Corpo(const int &x, const int &y, const int &oldcorpse);
    ~Corpo();
    void Action() override;
};

class Bife: public AlimentoTV
{
public:
    Bife();
    Bife(const int &x, const int &y);
    ~Bife();
    void Action() override;
};

#endif //POO_ALIMENTO_H

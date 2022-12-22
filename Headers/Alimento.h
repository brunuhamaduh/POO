#ifndef POO_ALIMENTO_H
#define POO_ALIMENTO_H

#include "Coordenadas.h"

class BaseAlimento
{
    int ID;
    int ValorNutritivo;
    int Toxicidade;
    int Instante;
    char letra;
    std::vector<std::string> Cheiro;
    std::string Description;
    Coordenadas Location;
    bool kill;

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
    char getLetra() const;
    std::string getDescription() const;
    virtual int getTV() const;
    void Kill();
    bool getKill() const;
    void InitVN(const int &num);
    void InitToxic(const int &num);
    void InitLetra(const char &letr);
    void InitCheiro(const std::vector<std::string> &cheiros);
    std::vector<std::string> getCheiro() const;
    virtual bool Action() = 0;
    virtual BaseAlimento* Child(std::vector<BaseAlimento*> &alimentos);
    int getInstante() const;
    void incInstante();
    void InitDescription(const std::string &descrip);
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
    bool spawned;
public:
    Relva();
    Relva(const int &x, const int &y);
    ~Relva();
    bool Action() override;
    Relva* Child(std::vector<BaseAlimento*> &alimentos) override;
};

class Cenoura: public BaseAlimento
{
public:
    Cenoura();
    Cenoura(const int &x, const int &y);
    ~Cenoura();
    bool Action() override;
};

class Corpo: public BaseAlimento
{
    int ogVN;
public:
    Corpo(const int &x, const int &y, const int &oldcorpse);
    Corpo(const int &x, const int &y, const int &oldcorpse, const int &Toxic);
    ~Corpo();
    bool Action() override;
};

class Bife: public AlimentoTV
{
public:
    Bife();
    Bife(const int &x, const int &y);
    ~Bife();
    bool Action() override;
};

#endif //POO_ALIMENTO_H

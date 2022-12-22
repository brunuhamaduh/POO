#ifndef POO_HISTORY_H
#define POO_HISTORY_H
#include <string>

class History
{
    int valorNutricional;
    int Toxicidade;
    char letra;

public:
    History(const int &VN, const int &Toxic, const char &letra);
    ~History();
    std::string getEntry() const;
};


#endif //POO_HISTORY_H

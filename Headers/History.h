#ifndef POO_HISTORY_H
#define POO_HISTORY_H
#include <string>

class History
{
    int valorNutricional;
    int Toxicidade;
    std::string Description;

public:
    History(const int &VN, const int &Toxic, const std::string &descrip);
    ~History();
    std::string getEntry() const;
};


#endif //POO_HISTORY_H

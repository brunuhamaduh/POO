#include "History.h"
#include <sstream>

History::History(const int &VN, const int &Toxic, const char &letra) : valorNutricional(VN), Toxicidade(Toxic), letra(letra){}
History::~History() = default;
std::string History::getEntry() const
{
    std::ostringstream out;
    out << valorNutricional << " " << Toxicidade << " " << letra << std::endl;
    return out.str();
}
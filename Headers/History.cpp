#include "History.h"
#include <sstream>

History::History(const int &VN, const int &Toxic, const std::string &descrip) : valorNutricional(VN), Toxicidade(Toxic), Description(descrip){}
History::~History() = default;
std::string History::getEntry() const
{
    std::ostringstream out;
    out << valorNutricional << " " << Toxicidade << " " << Description << std::endl;
    return out.str();
}
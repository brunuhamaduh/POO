#include "History.h"
#include <sstream>

History::History(const int &VN, const int &Toxic, std::string descrip) : valorNutricional(VN), Toxicidade(Toxic), Description(std::move(descrip)){}
History::~History() = default;
std::string History::getEntry() const
{
    std::ostringstream out;
    out << valorNutricional << " " << Toxicidade << " " << Description << std::endl;
    return out.str();
}
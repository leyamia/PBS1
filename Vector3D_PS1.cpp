#include "Vector3D.h"
#include <sstream>

//operator== method 
bool Vector3D::operator==(const Vector3D& aOther) const noexcept 
{
    return (std::abs((*this).x() - aOther.x()) < std::numeric_limits<float>::epsilon()) &&
           (std::abs((*this).y() - aOther.y()) < std::numeric_limits<float>::epsilon()) &&
           (std::abs((*this).w() - aOther.w()) < std::numeric_limits<float>::epsilon());
}

//tostring() method 
std::string Vector3D::toString() const noexcept
{
    std::stringstream lstream;

    lstream << (*this).x() << ","
           << (*this).y() << ","
           << (*this).w();
        
    std::string lresult = lstream.str();

    return "[" + lresult + "]";
}





#pragma once
#include "Typeid.hpp"

namespace reflect
{


std::ostream& operator<<( std::ostream & os, TypeId typeId)
{
    os << typeId.hash_code();
    return os;
}


}

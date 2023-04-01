#pragma once
#include <typeindex>
#include <type_traits>
#include <ostream>
#include "TypeId.hpp"

namespace reflect
{
std::ostream& operator<<( std::ostream & os, TypeId typeId);


}
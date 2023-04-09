#pragma once
#include "TypeId.hpp"
#include <iostream>
#include <type_traits>
#include <typeindex>


namespace reflect {
std::ostream& operator<<(std::ostream& os, TypeId typeId);

}
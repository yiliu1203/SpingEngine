#pragma once
#include "ReflectMacro.h"

namespace reflect {

class SP_API UserObject
{

public:
    template <typename T>
    UserObject(const T& object)
    {}
};


}   // namespace reflect

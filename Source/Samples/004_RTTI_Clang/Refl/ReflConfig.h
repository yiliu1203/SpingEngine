#pragma once

#include <exception>

#define REFL_API




#define REFL_ASSERT(condition,...)              \
{                                               \
        if (!(condition))                       \
        {throw std::exception(__VA_ARGS__);}    \
}                                               
#pragma once
#include "TypeAlias.h"
#include <algorithm>
#include <iostream>


namespace SPing {

template <typename T>
void Swap(T& first, T& second)
{
    using std::swap;
    swap(first, second);
}

std::ostream& operator<<(std::ostream& os, const TypeId& typeId);

}   // namespace SPing
#pragma once
#include <algorithm>
#include <iostream>


namespace SPing {

class TypeId;

template <typename T>
void Swap(T& first, T& second)
{
    using std::swap;
    swap(first, second);
}

std::ostream& operator<<(std::ostream& os, const TypeId& typeId);

}   // namespace SPing
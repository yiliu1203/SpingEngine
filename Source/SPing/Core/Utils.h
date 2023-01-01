#pragma once
#include <algorithm>

namespace SPing {

template <typename T>
void Swap(T& first, T& second)
{
    using std::swap;
    swap(first, second);
}

}
#include <any>
#include <array>
#include <functional>
#include <iostream>
#include <tuple>
#include <type_traits>
#include <utility>

namespace reflect
{

namespace detail
{

class Value
{

public:

    template <typename T>
    Value(T&& val)
    {
    }

};


}

}
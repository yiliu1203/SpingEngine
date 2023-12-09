#include <assert.h>
#include <exception>
#include <initializer_list>
#include <iostream>
#include <memory>
#include <sstream>
#include <string>
#include <tuple>
#include <typeindex>
#include <vector>


namespace n1 {
using type1 = std::type_index;
}

namespace n2 {
using type2 = std::type_index;
}


void f1(n1::type1 t)
{
    std::cout << t.hash_code();
}


int main()
{
    n2::type2 t2 = typeid(int);
    f1(t2);
    return 0;
}
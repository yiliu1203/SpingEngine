
#include <string>
#include <iostream>
#include <type_traits>
#include <vector>
#include <compare> 
#include <algorithm> 

#include <array>
#include <functional>
#include <iterator>
#include <string_view>
#include <cassert>



template <size_t N=0>
struct fixed_string {
    char _chars[N+1];
    size_t n = N;

    // constexpr fixed_string(const char (&array)[N + 1]) noexcept
    // {
    //   std::copy(std::begin(array), std::end(array), _chars);
    //   n = 0;
    // }

    
    constexpr fixed_string(const size_t& t) noexcept
    {
    //   std::copy(std::begin(array), std::end(array), "tes");
        _chars[N+1] = {};
        n = N;
    }

    constexpr size_t size() const {
        return N;
    }
};


// template <size_t N>
// fixed_string(const char (&arr)[N])-> fixed_string<N-1>;

template <size_t N>
fixed_string(const size_t& n)-> fixed_string<N>;




// ----TEST fixed_string -----
template <fixed_string>
struct Literal {
    using type = char;
};


//---------------------------

int main() 
{

    // -------- TEST fixed_string----------------
    // fixed_string str{""};
    // std::cout << str.size();
    // std::cout << typeid(Literal<"hello">::type).name() << std::endl;

    // 无法实现 本质是 fixed_string(N), 没法根据实参N, 推导模板参数。 而字符串字面量 中的N是属于类型的一部分（复合类型），可以用来推导模板参数N
    auto t = fixed_string{0};       

    std::cout << typeid(Literal<0>::type).name() << std::endl;

    std::cout << "---------------"<< std::endl;
    // ----------------------------------------------

}

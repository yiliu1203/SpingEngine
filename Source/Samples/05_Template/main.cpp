#include <iostream>

template <typename T>
class is_const : public std::false_type {

};

template <typename T>
class is_const<const T>: public std::true_type {
};

int main() {
    std::cout << "Hello Template" << std::endl;
    std::cout << is_const<const int>::value << std::endl;   // 1
    // 这里输出0， 有点难理解 看起来const匹配的优先级很低？指针或者地址符匹配的优先级更高
    std::cout << is_const<const int&>::value << std::endl;  // 0
    std::cout << is_const<const int*>::value << std::endl;  // 0
}
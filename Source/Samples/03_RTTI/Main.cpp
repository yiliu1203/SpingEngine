#include <iostream>
#include "Rtti/RttiConfig.hpp"

class Foo {
public:
    int x;
    int y;
};
RTTI_TYPE(Foo);

class Shape {
};

int main()
{
    using namespace SPing::RTTI;
    std::cout << "Hello World" << std::endl;

    std::cout << "typeid: Foo" << typeid(Foo).name() << std::endl;

    std::cout << StaticTypeDecl<Foo>::name() << " " << StaticTypeDecl<Foo>::id() << std::endl;

    

}
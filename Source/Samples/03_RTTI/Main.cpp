#include <iostream>
#include "Reflect/Reflect.h"

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
    using namespace reflect;
    std::cout << "Hello World" << std::endl;

    std::cout << "typeid: Foo " << typeid(Foo).name() << std::endl;

    std::cout << StaticTypeDecl<Foo>::name() << " " << StaticTypeDecl<Foo>::id() << std::endl;

    Meta::Declare<Foo>().property("x", &Foo::x);
    
}
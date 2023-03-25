#include "Reflect/Reflect.h"
#include <iostream>


class Foo
{
public:
    int x;
    int y;
};
RTTI_TYPE(Foo);

class Shape
{};

int main()
{
    using namespace reflect;
    std::cout << "Hello World" << std::endl;

    std::cout << "typeid: Foo " << typeid(Foo).name() << std::endl;

    std::cout << StaticTypeDecl<Foo>::name() << " " << StaticTypeDecl<Foo>::id() << std::endl;

    Meta::Declare<Foo>().property("x", &Foo::x);

    // const Meta* meta1 = reflect::MetaManager::Instance().Get("Foo");
    // const Meta* meta2 = reflect::MetaManager::Instance().Get<Foo>();
    // ASSERT(meta1 != nullptr);
    // ASSERT(meta1 == meta2);

    // meta1->getProprity("x");




    Foo F;
    F.x = 1;
    F.y = 2;


    std::cout << std::endl << "Success";
}
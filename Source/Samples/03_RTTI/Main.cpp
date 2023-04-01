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

    Meta::Declare<Foo>().property("x", &Foo::x).property("y", &Foo::y);

    const Meta* meta1 = reflect::MetaManager::Instance().Get("Foo");
    const Meta* meta2 = reflect::MetaManager::Instance().Get<Foo>();
    ASSERT(meta1 != nullptr);
    ASSERT(meta1 == meta2);

    Foo F;
    F.x = 1;
    F.y = 2;

    auto propX = meta1->getProprity("x");
    auto propY = meta1->getProprity("y");
    std::cout << "property Foo.x = " << propX->get(&F).To<int>() << std::endl;
    std::cout << "property Foo.y = " << propY->get(&F).To<int>() << std::endl;
    propX->set(&F, 10);
    propY->set(&F, 20);

    std::cout << "test set" << std::endl;
    std::cout << "property Foo.x = " << propX->get(&F).To<int>() << std::endl;
    std::cout << "property Foo.y = " << propY->get(&F).To<int>() << std::endl;


    std::cout << std::endl << "Success";
}
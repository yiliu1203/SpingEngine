#include <iostream>
#include "Core/Object.h"
#include "Core/Context.h"

using namespace SPing;

class TestA : public Object {

    TYPE_RTTI(TestA, Object);

public:
    explicit TestA(Context* context) : Object(context){};
    ~TestA(){};
};

class TestB : public TestA
{
    TYPE_RTTI(TestB, TestA);

public:
    explicit TestB(Context* context) : TestA(context) { std::cout << "destroyB" << std::endl;};
    ~TestB() {};
};


int main() 
{
    std::cout << "********************test Object**************************************" << std::endl;
    Context* context = new Context();

    TestA *a = new TestA(context);
    TestB *b = new TestB(context);
    Object &c = *b;

    std::string typeName = a->GetTypeName();
    std::cout << a->GetTypeName() << std:: endl 
    << a->GetType() << std::endl 
    << b->IsInstanceOf(a->GetType()) << std:: endl 
    << c.IsInstanceOf(b->GetType()) << std::endl;
    std::cout << a->IsInstanceOf(b->GetType());
    
    delete a;
    
}
#include <iostream>
#include "Core/Object.h"
#include "Core/Context.h"
#include "Core/Ptr.h"

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
    explicit TestB(Context* context) : TestA(context) { std::cout << "ConstructB" << std::endl;};
    ~TestB() {std::cout <<"DestroyB"<< std::endl;};
};


int main() 
{
    std::cout << "********************test Object**************************************" << std::endl;
    Context* context1 = new Context();

    TestA *a = new TestA(context1);
    TestB *b = new TestB(context1);
    Object &c = *b;

    std::string typeName = a->GetTypeName();
    std::cout << a->GetTypeName() << std:: endl 
    << a->GetType() << std::endl 
    << b->IsInstanceOf(a->GetType()) << std:: endl 
    << c.IsInstanceOf(b->GetType()) << std::endl;
    std::cout << a->IsInstanceOf(b->GetType());
    
    delete a;

    std::cout << "**************************Test SharePtr *********************************" << std:: endl;

    {
        Context* context2 = new Context();
        TestA * rawPtrA = new TestA(context2);
        TestB * rawPtrB = new TestB(context2);
        SharePtr<TestA> shareA(rawPtrA);
        {
            SharePtr<TestA> shareAA(rawPtrA);
            std::cout << "Ref rawPtrA: " << shareA.Refs() << std::endl; 
            std::cout << "Ref rawPtrAA: " << shareA.Refs() << std::endl; 

            TestB * rawPtrBB = new TestB(context2);
            SharePtr<TestB> shareB(rawPtrBB);

            SharePtr<TestB> BB(shareB);
            std::cout << BB.Refs() << std::endl;
        }
        
        std::cout << "Ref rawPtrA: " << shareA.Refs() << std:: endl; 

    }
    

    












    
}
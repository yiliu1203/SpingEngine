#include <iostream>
#include "Core/Object.h"
#include "Core/Context.h"
#include "Core/Ptr.h"
#include "Math/Vector.h"
#include "Math/Matrix.h"

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

class Test0
{
public:
    explicit Test0(Context* context) { std::cout << "ConstructB" << std::endl;};
};

class TestDeletage {

public:
    int Add(int a, int b)
    {
        return a + b;
    }
};

int Add(int a, int b)
{
    return a + b;
}


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

    {
        std::cout << "**************************Test SharePtr *********************************" << std:: endl;
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

        //
        Test0 * rawPtr0 = new Test0(context2);
        // SharePtr<Test0> t0(rawPtr0);  // 编译报错
    }

    {
        std::cout << "**************************Test Vector Matrix *********************************" << std:: endl;
        using namespace SPing::Math;
        Vec2 v2_0;
        std::cout << v2_0;
        Vec2 v2_1{1.5, 2.5};  // 这里可以超过 2, 但是 4 被舍弃了
        std::cout << v2_1;
        std::cout << (v2_1 * 3);

        Vec2d v2d_0{10, 20};
        std::cout << (v2_1 + v2d_0) << std::endl;

    }

    {
        std::cout << "**************************Test Delegate *********************************" << std:: endl;

        TestDeletage testDelegate;
        typedef int (TestDeletage::*CF)(int, int);
        CF cf = &(TestDeletage::Add);
        std::cout << "testDelegate.*cf: " << (testDelegate.*cf)(1, 2) << std::endl;


    }


    

    












    
}
/**
 * 【参考】https://github.com/taichi-dev/cpp-training-season1/blob/main/reflection/src/reflect.hpp
*/



#include <iostream>
#include <string>
#include "reflect.hpp"

class Foo
{
    public:
        std::string anme;

        void PassByValue(std:: string s) const
        {
            std::cout << "FOO::PassByValue (" << s << ")" << std::endl;
        }

         void PassByRef(const std:: string& s) const
        {
            std::cout << "FOO::PassByValue ( const" << s << ")" << std::endl;
        }

        std::string Concat(const std::string& s1, const std::string& s2)
        {
            return s1 + s2;
        }

        int x() const {return x_;}

    
    private:
        int x_{0};

};


// reflect::AddClass<Foo>("Foo")
//         .AddMemberVar("name", &Foo::name)
//         .AddMemberVar("x_", &Foo::x_)
//         .AddMemberFunc("PassByValue", &Foo::PassByValue)
//         .AddMemberFunc("PassByConstRef", &Foo::PassByConstRef)
//         .AddMemberFunc("Concat", &Foo::Concat)
//         .AddMemberFunc("MakeFloatPtr", &Foo::MakeFloatPtr);


int main()
{
    reflect::AddClass<Foo>("Foo");
    std::cout << "Hello World" << std::endl;

}
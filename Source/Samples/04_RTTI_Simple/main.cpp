/**
 * 【参考】https://github.com/taichi-dev/cpp-training-season1/blob/main/reflection/src/reflect.hpp
*/

# pragma warning (disable:4819)

#include <iostream>
#include <string>
#include "reflect.hpp"
#include "value.hpp"

class Foo
{
    public:
        std::string name;

        void PassByValue(std:: string s) const
        {
            std::cout << "FOO::PassByValue (" << s << ")" << std::endl;
        }

        void PassByValue(int num) const
        {
            std::cout << "FOO::PassByValue (" << num << ")" << std::endl;
        }

        std::string PassByValueReturn(const std:: string s)
        {
            std::cout << "FOO::PassByValue (" << s << ")" << std::endl;
            return s;
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

void PassByValue(std:: string s)
{
    std::cout << "FOO::PassByValue (" << s << ")" << std::endl;
}

void PassByRef(const std:: string& s)
{
    std::cout << "FOO::PassByValue ( const" << s << ")" << std::endl;
}


// reflect::AddClass<Foo>("Foo")
//         .AddMemberVar("name", &Foo::name)
//         .AddMemberVar("x_", &Foo::x_)
//         .AddMemberFunc("PassByValue", &Foo::PassByValue)
//         .AddMemberFunc("PassByConstRef", &Foo::PassByConstRef)
//         .AddMemberFunc("Concat", &Foo::Concat)
//         .AddMemberFunc("MakeFloatPtr", &Foo::MakeFloatPtr);

int main()
{
    // 模拟重载的情况
    void (Foo::*ptr1)(std::string) const = &Foo::PassByValue;
    void (Foo::*ptr2)(int) const = &Foo::PassByValue;
    reflect::AddClass<Foo>("Foo")
    .AddMemberVar("name", &Foo::name)
    .AddMemberFunc("PassByValue_string", ptr1)
    .AddMemberFunc("PassByValue_int", ptr2)
    .AddMemberFunc("PassByValueReturn", &Foo::PassByValueReturn);

    std::cout << reflect::detail::Registry::instance().Find("Foo") << std::endl;
    auto* fooMeta = reflect::detail::Registry::instance().Find("Foo");
    std::cout << *fooMeta << std::endl;

    Foo foo;
    foo.name = "Empty";
    {
        std::cout << "-----------Test MemberVariable---------------" << std::endl;
        reflect::detail::MemberVariable mv{&Foo::name};
        mv.SetValue(foo, std::string{"name1"});
        std::cout << foo.name << "|" << mv.GetValue<Foo, std::string>(foo) << std::endl;

        std::cout << "-----------Test MemberFunction---------------" << std::endl;
        reflect::detail::MemberFunction mf{ptr2};
        std::cout << mf.name() << " is const: " << mf.is_const() << std::endl;
        mf.Invoke(foo, 1);
        
    }

    {
        std::cout << std::endl << std::endl << "---------------test Value---------------------" << std::endl;
        int tmpval = 5;
        const int& tmp = tmpval;
        reflect::detail::Value v{tmp};
        // bool test = typeid(std::add_const_t<int*>) == 
        using const_int = std::add_const_t<int>;
        std::cout << (typeid(const_int).hash_code() == typeid(int).hash_code()) << std::endl;
        std::cout << "is_same:" << std::is_same<const int, std::add_const_t<int>>::value << std::endl;
        std::cout << "is_same*" << std::is_same<const int *, std::add_const_t<int*>>::value << std::endl;
        std::cout << "const_int:" << std::is_const_v<const_int> << std::is_const_v<int> << std::endl;
        std::cout << typeid(const int).name() << std::endl;
        std::cout << typeid(const int *).name() << std::endl;
        std::cout << v.IsConst() << v.RefType() << std::endl;
        std::cout << v.To<const int&>() << std::endl;

        tmpval = 55;
        int& tmp2 = tmpval;
        reflect::detail::Value v2{tmp2};
        std::cout << v.IsConst() << v.RefType() << std::endl;
        std::cout << v.To<const int>() << std::endl;

    }

    {
        std::cout << std::endl << "-------------------Test FuncWrap-------------------------" << std::endl;
        reflect::detail::FuncWrap func_value{PassByValue};
        func_value.Invoke(std::string{"Hello"});
        reflect::detail::FuncWrap func_ref{PassByRef};
        func_value.Invoke(std::string{"Hello"});
    }

}

#include <iostream>

/**
 * 函数模板。 
 * template <typename T>
 * rType fName(【关于T 的元类型转换后得到的类型】 _t){}  这个时候可能调用时需要显示指定T的类型，而不能通过实参推导出T了
*/
template <typename T>
void f1(typename std::remove_reference_t<T> a_copy) {
    a_copy ++;
}


/**
 * 关于is_reference的演化，元编程的模式【type、value、using、injected-class-name的概念】，使用继承可以让代码很简洁。 
 * std::true_type 和 std::false_type广泛被使用
*/
template <typename T>
struct is_refenerce_v0 {
    static constexpr bool value = false;
    using type = is_refenerce_v0;
};

template <typename T>
struct is_refenerce_v0 <T&> {
    static constexpr bool value = true;
    using type = is_refenerce_v0;
};


template <typename T>
struct is_refenerce_v1 {
    using type = std::integral_constant<bool, false>;
};

template <typename T>
struct is_refenerce_v1 <T&> {
    using type = std::integral_constant<bool, true>;
};

template <typename T>
struct is_refenerce_v2 : std::false_type {};

template <typename T>
struct is_refenerce_v2<T&> : std::true_type {};


/**
 * 
*/
template <typename T, typename U> struct S {};
template <typename T> struct S<int, T> {};





int main()
{
    {
        int i = 0;
        // f1(i);  Error!!
        f1<int&>(i);
        f1<int&&>(i);
        std::cout << i << std::endl;

    }
    {

        std::cout << "is_reference_v0 int& " << is_refenerce_v0<int&>::value << std::endl;
        std::cout << "is_reference_v1 int& " << is_refenerce_v1<int&>::type::value << std::endl;
        std::cout << "is_reference_v2 int& " << is_refenerce_v2<int&>::value << std::endl;
    }

    {
        S<int, float>();
        /**
         * The number of template arguments is only determined by the parameter list of
         * the primary template。Arguments of a template instantiation are determined before selecting the
         * template specialization
        */
        // S<float>(); Error!!!         
        S<int, int>();
    }
}
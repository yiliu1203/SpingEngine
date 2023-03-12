#include <iostream>

template <typename T>
class is_const : public std::false_type {

};

template <typename T>
class is_const<const T>: public std::true_type {
};

// 利用 void_t 判断是类型是否有特定数据成员

template <typename T, typename=void>
class has_member: public std::false_type{};

template <typename T>
/** void_t 相当于对任何类型都满足推导，会优先用特化版本*/
class has_member<T, std::void_t<decltype(T::member)>> : public std::true_type {};

struct test_has_member
{
    int member;
};
struct test_no_member
{
};

/**利用void_t 和 declval 判断类型是否有特定方法*/
template <typename T, typename=void>
class is_smart_ptr: public std::false_type{};

template <typename T>
class is_smart_ptr<T, std::void_t<decltype(std::declval<T>().operator->()), decltype(std::declval<T>().get())>>
:public std::true_type{};


/** 利用继承来实现多态 std::is_member_funcon_pointer 可能的实现*/
template <typename T>
struct is_member_function_pointer_helper : std::false_type {};

// 特化版本
template<typename T, typename U>
struct is_member_function_pointer_helper <T U::*> : std::is_function<T> {};
// struct is_member_function_pointer_helper <T(U::*)> : std::is_function<T> {};  成员函数？注意和上面的区别

template <typename T>
struct is_member_function_pointer : is_member_function_pointer_helper<typename std::remove_cv_t<T>> {};

//----------------------------------------------------------------


int main() {
    std::cout << "Hello Template" << std::endl;
    {
        std::cout << "---------------test is_const-------------------" << std::endl;
        std::cout << is_const<const int>::value << std::endl;   // 1
        // 这里输出0， 有点难理解 看起来const匹配的优先级很低？指针或者地址符匹配的优先级更高
        std::cout << is_const<const int&>::value << std::endl;  // 0
        std::cout << is_const<const int*>::value << std::endl;  // 0
    }

    {
        std::cout << "----------------test void_t--------------------" << std::endl;
        std::cout << has_member<test_has_member>::value << std::endl;   // 1
        std::cout << has_member<test_no_member>::value << std::endl;    // 0
    }

    {
        std::cout << "----------------test void_t with smart_ptr ------" << std::endl;
        std::cout << is_smart_ptr<std::shared_ptr<int>>::value << std::endl;    // 1
        std::cout << is_smart_ptr<std::weak_ptr<int>>::value << std::endl;      // 0
        std::cout << is_smart_ptr<int>::value << std::endl;                     // 0
    }
    

    
}
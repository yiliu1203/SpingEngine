#include <iostream>

template <typename T>
class is_const : public std::false_type
{};

template <typename T>
class is_const<const T> : public std::true_type
{};

// 利用 void_t 判断是类型是否有特定数据成员

template <typename T, typename = void>
class has_member : public std::false_type
{};

template <typename T>
/** void_t 相当于对任何类型都满足推导，会优先用特化版本 */
class has_member<T, std::void_t<decltype(T::member)>> : public std::true_type
{};


// 根据是否有 GetTypeInfoStatic 静态成员判断是否继承至 Object
template <typename T, typename = void>
class InheritFromObject : public std::false_type
{};

template <typename T>
class InheritFromObject<T, std::void_t<typename T::StaticTypeDecl>> : public std::true_type
{};



struct test_has_member
{
    int member;
};
struct test_no_member
{};

/**利用void_t 和 declval 判断类型是否有特定方法 */
template <typename T, typename = void>
class is_smart_ptr : public std::false_type
{};

template <typename T>
class is_smart_ptr<T, std::void_t<decltype(std::declval<T>().operator->()), decltype(std::declval<T>().get())>>
    : public std::true_type
{};


/** 利用继承来实现多态 std::is_member_funcon_pointer 可能的实现 */
template <typename T>
struct is_member_function_pointer_helper : std::false_type
{};

// 特化版本
template <typename T, typename U>
struct is_member_function_pointer_helper<T U::*> : std::is_function<T>
{};   // 注意判断 is_function 用T, 判断is_member_function 用 T U::*
// struct is_member_function_pointer_helper <T(U::*)> : std::is_member_function_pointer<T U::*> {};  // 成员函数？注意和上面的区别

template <typename T>
struct is_member_function_pointer : is_member_function_pointer_helper<typename std::remove_cv_t<T>>
{};

template <typename T, typename = void>
struct is_member_object_pointer : std::false_type
{};

// template<typename T, typename U>
// // 这种写法，integral_constant 第二个参数是 bool类型的值，通过constexpr在编译器求值。 就不需要上面那个 std::false_type 的基础版本了
// struct is_member_object_pointer <T(U::*)> : std::integral_constant<bool, std::is_member_pointer<T>::value && !is_member_function_pointer<T>::value > {};     // 这里 T(U::*) 和 T U::* 的形式是一样的, 静态成员不满足
// // struct is_member_object_pointer <T U::*> : std::is_member_pointer<T U::*> {};

template <typename T, typename U>
// 1. 部分专用化不能带有默认模板参数, 2. 【特别注意】T 和 T(U::*) 的区别, 一个是普通类型，一个带成员的类型。函数成员时也同理
struct is_member_object_pointer<
    T(U::*), typename std::enable_if_t<std::is_member_pointer<T U::*>::value && !is_member_function_pointer<T U::*>::value>>
    : std::true_type
{};
// 体会下上面 std::enable_if 在模板特化 和 继承上的用法

class TestMemFunc
{
public:
    int                  f1() { return 1; };
    int                  a;
    static int           f2() { return 1; }
    static constexpr int a2 = 1;

public:
    struct StaticTypeDecl
    {
        /* data */
    };
};



//----------------------------------------------------------------


int main()
{
    std::cout << "Hello Template" << std::endl;
    {
        std::cout << "---------------test is_const-------------------" << std::endl;
        std::cout << is_const<const int>::value << std::endl;   // 1
        // 这里输出0， 有点难理解 看起来const匹配的优先级很低？指针或者地址符匹配的优先级更高
        std::cout << is_const<const int&>::value << std::endl;   // 0
        std::cout << is_const<const int*>::value << std::endl;   // 0
    }

    {
        std::cout << "----------------test void_t--------------------" << std::endl;
        std::cout << has_member<test_has_member>::value << std::endl;   // 1
        std::cout << has_member<test_no_member>::value << std::endl;    // 0
    }

    {
        std::cout << "----------------test void_t with smart_ptr ------" << std::endl;
        std::cout << is_smart_ptr<std::shared_ptr<int>>::value << std::endl;   // 1
        std::cout << is_smart_ptr<std::weak_ptr<int>>::value << std::endl;     // 0
        std::cout << is_smart_ptr<int>::value << std::endl;                    // 0
    }

    {
        std::cout << "-----------------test std::add_pointer -------------------" << std::endl;
        std::cout << std::is_same<std::add_pointer_t<int>, int*>::value << std::endl;
        std::cout << std::is_same<std::add_pointer_t<int*>, int*>::value << std::endl;
        std::cout << std::is_same<std::add_pointer_t<std::remove_pointer_t<int>>, int*>::value << std::endl;
    }

    {
        std::cout << "-----------------test member_function -------------------" << std::endl;
        // 注意这里要加 decltype 转成类型，因为 TestMemFunc::f1 是一个值
        std::cout << is_member_function_pointer<decltype(&TestMemFunc::f1)>::value << std::endl;
        std::cout << is_member_function_pointer<decltype(&TestMemFunc::a)>::value << std::endl;

        std::cout << is_member_object_pointer<decltype(&TestMemFunc::f1)>::value << std::endl;
        std::cout << is_member_object_pointer<decltype(&TestMemFunc::a)>::value << std::endl;
        std::cout << is_member_object_pointer<decltype(&TestMemFunc::f2)>::value << std::endl;
        std::cout << is_member_object_pointer<decltype(&TestMemFunc::a2)>::value << std::endl;
        std::cout << std::is_member_pointer<decltype(&TestMemFunc::a)>::value << std::endl;

        std::cout << InheritFromObject<TestMemFunc>::value << std::endl;
        std::cout << InheritFromObject<test_has_member>::value << std::endl;
    }

    return 0;
}
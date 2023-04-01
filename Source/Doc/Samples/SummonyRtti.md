# 记录一些总结
```c++
    template <typename T>
    // 【如果匹配到 const int *, 则这里的 T == const int *&】
    Value(T&& val)
    {
        ref_type_ = trait::RefTrait<T>::value;
        is_const_ = trait::IsConst<T>::value;
    }
```
## typeid 去掉了 顶层const和volatile
```c++
assert(typeid(const_int).hash_code() == typeid(int).hash_code());
```

## std::add_const_t 对指针时注释不是 const*

```c++
std::cout << "is_same*" << std::is_same<const int *, std::add_const_t<int*>>::value << std::endl;  // 0
```

## std::apply 和 std::invoke

最大的却别是 std::apply 接受元组作为参数，而std::invoke 接受参数包

```c++
// 注意 完美转发的std::forward
namespace detail {
template <class F, class Tuple, std::size_t... I>
constexpr decltype(auto) apply_impl(F&& f, Tuple&& t, std::index_sequence<I...>)
{
    return std::invoke(std::forward<F>(f), std::get<I>(std::forward<Tuple>(t))...);
}
}  // namespace detail

template <class F, class Tuple>
constexpr decltype(auto) apply(F&& f, Tuple&& t)
{
    return detail::apply_impl(
        std::forward<F>(f), std::forward<Tuple>(t),
        std::make_index_sequence<std::tuple_size_v<std::remove_reference_t<Tuple>>>{});
}
```


## std::make_index_sequence 

创建一个1-n序列的参数包，用std::index_sequence类型来接收，注意index_sequence 的使用

```c++
template <typename... A>
void OUT(A... args) {
    auto a = std::forward_as_tuple(args...);
    OUT(a, std::make_index_sequence<sizeof... (A)>{});
}

// std::index_sequence 和 std::make_index_sequence 配合使用，拿到编译期的size_t类型的一串常量模板参数包。
template<typename... A, size_t ...N>
void OUT(std::tuple<A...>& a, std::index_sequence<N...>)
{
    // 这里本质是利用模板实例化的过程，也需要用这个特征才能在生成 实例化 std::get
    std::initializer_list<int> tmp = { (std::cout << std::get<N>(a) << " ",0)... };
}
```

## 利用 void_t 判断是否有特定成员数据或者成员方法

```c++
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

```


#pragma once
#include "ObjectTraits.hpp"


namespace reflect {
namespace detail {

template<typename C> struct MemberTraits;

template<typename C, typename T> struct MemberTraits<T(C::*)>
{
    using BoundType = T(C::*);
    // typedef T(C::*BoundType);
    using ExposedType   = T;
    using ExposedTraits = TypeTraits<T>;

    static constexpr bool isWriteable = ExposedTraits::isWriteable;

    // 下面的Binding 是为了将数据成员和函数成员统一起来
    class Binding
    {
    public:
        Binding(const BoundType& bound_type)
            : bound_type(bound_type)
        {}
        ExposedTraits::ReferenceType access(const C& c) const { return c.*bound_type_; }

    private:
        BoundType bound_type_;
    };
};

template<typename T> struct MethodDetail
{};

template<typename R, typename C, typename... A> struct MethodDetail<R (C::*)(A...)>
{
    using ClassType               = C;
    using ParamType               = std::tuple<A...>;
    using ReturnType              = R;
    using FuncType                = (ReturnType)(ClassType : *)(A...);   // 全类型
    using FunctionCallTypes       = std::tuple<ClassType&, A...>;
    static constexpr bool isConst = false;
};


template<typename R, typename C, typename... A> struct MethodDetail<R (C::*)(A...) const>
{
    using ClassType               = const C;
    using ParamType               = std::tuple<A...>;
    using ReturnType              = R;
    using FuncType                = (ReturnType)(const ClassType : *)(A...);
    using FunctionCallTypes       = std::tuple<const ClassType&, A...>;
    static constexpr bool isConst = true;
};


template<typename C, typename = void> struct FunctionTraits;

template<typename T>
struct FunctionTraits<
    T, typename std::is_member_function_pointer<
           T>::type>   // 成员函数匹配，注意和 数据成员的区别, 这里也可以用 std::enable_if 来实现
{
    using Detail        = MethodDetail<T>;
    using BoundType     = Detail::FuncType;
    using ExposedType   = Detail::ReturnType;
    using ExposedTraits = TypeTraits<ExposedType>;
    using isWriteable   = std::is_lvalue_reference_v<ExposedType> && !Detail::isConst;

    class Binding
    {
    public:
        Binding(const BoundType& bound_type)
            : bound_type_(bound_type)
        {}
        Detail::ReturnType access(Detail::ClassType& c) const { return (c.*bound_type_)(); }

    private:
        BoundType bound_type_;
    }
};






}   // namespace detail

}   // namespace reflect
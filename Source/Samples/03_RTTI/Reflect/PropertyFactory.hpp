#pragma once
#include "Property.h"
#include "PropertySimpleImpl.hpp"
#include "TraitsFunction.hpp"
#include "TraitsObject.hpp"
#include "ValueWrap.hpp"
#include <vector>






namespace reflect {
namespace detail {

template <typename C, typename TRAITS>
class ValueBinder
{
public:
    using ClassType  = C;
    using Binding    = typename TRAITS::Binding;
    using AccessType = typename TRAITS::AccessType;
    using SetType    = typename std::remove_reference_t<AccessType>;
    ValueBinder(const Binding& b)
        : bound_{b}
    {}
    // 这里本质上是需要一个成员指针，但是为了兼容成员函数的形式，包装成了 Binding
    AccessType getter(ClassType& c) const { return bound_.access(c); }
    bool       setter(ClassType& c, const SetType& value) const
    {
        if constexpr (TRAITS::isWriteable) return bound_.access(c), true;
        return false;
    }

protected:
    Binding bound_;
};


template <typename TRAITS, typename = void>
class AccessTraitsObjectMember
{
public:
    template <class C>
    using ValueBinder = ValueBinder<C, TRAITS>;

    template <typename A>
    using Impl = SimplePropertyImpl<A>;
};

/** 用于对象数据成员的 getset */
template <typename C, typename TRAITS>
class GetSetObjectMember
{
public:
    using ClassType                = C;
    using PropTraits               = TRAITS;
    static constexpr bool canRead  = true;
    static constexpr bool canWrite = PropTraits::isWriteable;

    using Access        = AccessTraitsObjectMember<TRAITS>;
    using InterfaceType = typename Access::template ValueBinder<ClassType>;

    /**
     * boundtype 就是一个全的类型 T C::*, 或者 T (C::*)(A...)
    */
    GetSetObjectMember(typename TRAITS::BoundType boundtype)
        : accessor_{boundtype}
    {}

    typename InterfaceType accessor_;
};




template <typename C, typename T, typename = void>
struct PropertyFactory1
{
    // static_assert(false);
};

template <typename C, typename T>
struct PropertyFactory1<C, T, typename std::enable_if_t<std::is_member_object_pointer_v<T>>>
{
    static Property* create(const std::string& name, T accessor)
    {
        using Accessor     = GetSetObjectMember<C, MemberTraits<T>>;
        using PropertyImpl = Accessor::Access::Impl<Accessor>;
        return new PropertyImpl(name, Accessor(accessor));
    }
};



}   // namespace detail
}   // namespace reflect
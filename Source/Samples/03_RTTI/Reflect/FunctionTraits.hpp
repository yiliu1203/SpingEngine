#pragma once
#include "ObjectTraits.hpp"


namespace reflect
{

namespace detail
{

template <typename C>
struct MemberTraits;

template <typename C, typename T>
struct MemberTraits < T (C::*) >
{
    // using BoundType = T (C::*);
    typedef T(C::*BoundType);
    using ExposedType = T;
    using ExposedTraits = TypeTraits<T>;
    
    static constexpr bool isWriteable = ExposedTraits::isWriteable;

    // 下面的Binding 是为了将数据成员和函数成员统一起来
    class Binding
    {
    public:
        Binding(const BoundType& bound_type) : bound_type(bound_type)
        {
        }
        ExposedTraits::ReferenceType access(const C& c) const {
            return c.*bound_type_;
        }
    private:
        BoundType bound_type_;
        
    };

};

template <typename C>
struct MemFunctionTraits;

template <typename C, typename T>
struct MemFunctionTraits<T C::*>    // 成员函数匹配，注意和 数据成员的区别
{
    

}





    
}

}
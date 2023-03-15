#pragma once
#include <vector>
#include "TypeId.hpp"

namespace reflect {
namespace detail
{

// 用于 T, T&, 不考虑右值引用
template <typename T>
struct TypeTraits
{
    using Type = T;
    using PureType = std::remove_reference_t<std::remove_pointer_t<T>>;
    using ReferenceType = std::add_rvalue_reference_t<PureType>;
    using PointerType = std::add_pointer_t<PureType>;
    using DereferencedType = PureType;
    static constexpr ReferenerKind kind = std::is_reference_v<T> ? ReferenceKind::Reference : ReferenceKind::Instance;
    static constexpr isWriteable = std::is_const_v<DereferencedType>;
    static constexpr isRef = std::is_reference_v<T> || std::is_pointer_v<T>;
};

// 用于 T* 
template <typename T>
struct TypeTraits<T*>
{
    using Type = T;
    using PureType = std::remove_reference_t<std::remove_pointer_t<T>>;
    // using ReferenceType = std::add_rvalue_reference_t<PureType>;
    using ReferenceType = std::add_pointer_t<PureType>;  // T* 和 T& 只有这里不一样
    using PointerType = std::add_pointer_t<PureType>;
    using DereferencedType = PureType;
    static constexpr ReferenerKind kind = ReferenceKind::Pointer;
    static constexpr isWriteable = std::is_const_v<DereferencedType>;
    static constexpr isRef = std::is_reference_v<T> || std::is_pointer_v<T>;
};

// todo 指针

}
}
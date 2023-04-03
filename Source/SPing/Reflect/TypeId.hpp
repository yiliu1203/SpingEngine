#pragma once
#include "ReflectMacro.h"
#include <ostream>
#include <type_traits>
#include <typeindex>


namespace reflect {

using TypeId = std::type_index;   // 类型的唯一id

// 注意 type_info 是忽略 const 和 引用的，指针影响 typeid.
// typeid(int) == typeid(const int) == typeid(int&).  typeid(int*) !== typeid(int)=

template <typename T>
inline TypeId CalcTypeId()
{
    return TypeId(typeid(T));
}


template <typename T>
struct StaticTypeDecl
{
    using type = T;
    static const TypeId id()
    {
        static_assert(false, "StaticTypeDecl Not Declare");
        return 0;
    };

    static constexpr const char* name()
    {
        static_assert(false, "StaticTypeDecl Not Declare");
        return "";
    }
};

template <typename T>
struct StaticTypeDecl2
{
    using Type = T;
    static StaticTypeDecl2 Instance()
    {
        static StaticTypeDecl2 mm;
        return mm;
    }

    static const TypeId id()
    {
        static_assert(false, "StaticTypeDecl Not Declare");
        return 0;
    };

    static constexpr const char* name()
    {
        static_assert(false, "StaticTypeDecl Not Declare");
        return "";
    }



    // static constexpr IsTypeOf(const TypeId& other) {}
};


enum class ValueKind
{
    None,
    Boolean,
    Integer,
    Real,
    String,
    Enum,
    Array,
};

enum class ReferenceKind
{
    None,
    Instance,
    Pointer,
    Reference,
};

template <typename T>
struct ValueKindMapper
{
    static constexpr ValueKind valueKind = ValueKind::None;
};

template <>
struct ValueKindMapper<bool>
{
    static constexpr ValueKind valueKind = ValueKind::Boolean;
};

template <>
struct ValueKindMapper<int>
{
    static constexpr ValueKind valueKind = ValueKind::Integer;
};

template <>
struct ValueKindMapper<float>
{
    static constexpr ValueKind valueKind = ValueKind::Real;
};

template <>
struct ValueKindMapper<double>
{
    static constexpr ValueKind valueKind = ValueKind::Real;
};

template <>
struct ValueKindMapper<std::string>
{
    static constexpr ValueKind valueKind = ValueKind::String;
};

template <>
struct ValueKindMapper<char*>
{
    static constexpr ValueKind valueKind = ValueKind::String;
};






}   // namespace reflect

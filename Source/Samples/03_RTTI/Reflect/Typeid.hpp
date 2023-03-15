#pragma once
#include <typeindex>
#include <type_traits>
#include <ostream>
#include "Macro.h"

namespace reflect
{
using TypeId = std::type_index;

template <typename T>
inline TypeId CalcTypeId() {return TypeId(typeid(T));}


template <typename T>
struct StaticTypeDecl
{
    using type = T;
    static const TypeId id()
    {
        static_assert(false, "StaticTypeDecl Not Declare");
        return 0;
    };

    static constexpr const char * name()
    {
        static_assert(false, "StaticTypeDecl Not Declare");
        return "";
    }

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

enum class ReferenceKind {
    None,
    Instance,
    Pointer,
    Reference,
};



}

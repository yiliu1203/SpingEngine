#pragma once
#include <typeindex>
#include <type_traits>
#include <ostream>

namespace SPing::RTTI
{
using TypeId = std::type_index;

template <typename T>
inline TypeId CalcTypeId() {return TypeId(typeid(T));}

std::ostream& operator<<( std::ostream & os, TypeId typeId);


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

}

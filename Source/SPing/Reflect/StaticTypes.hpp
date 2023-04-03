#pragma once
#include "TypeId.hpp"
#include <typeindex>

#define RTTI_TYPE(...)                                   \
    namespace reflect {                                  \
    template <>                                          \
    struct StaticTypeDecl<__VA_ARGS__>                   \
    {                                                    \
        static const TypeId id()                         \
        {                                                \
            return std::type_index(typeid(__VA_ARGS__)); \
        }                                                \
        static constexpr const char* name()              \
        {                                                \
            return #__VA_ARGS__;                         \
        }                                                \
    };                                                   \
    }

#define RTTI_TYPE2(...)
namespace reflect {}
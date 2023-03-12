#pragma once
#include <typeindex>
#include "Typeid.hpp"


#define RTTI_TYPE(...) \
    namespace reflect {\
    template<> struct StaticTypeDecl<__VA_ARGS__> \
    { \
    static const TypeId id() { return std::type_index(typeid(__VA_ARGS__));} \
    static constexpr const char* name(){return #__VA_ARGS__;} \
    }; \
}
    




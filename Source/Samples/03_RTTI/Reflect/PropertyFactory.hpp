#pragma ocne
#include "ObjectTraits.hpp"
#include "Property.h"
#include <vector>



namespace reflect {
namespace detail {

template <typename C, typename T, typename = void>
struct PropertyFactory1
{
    static_assert(false);
};

template <typename C, typename T>
struct PropertyFactory1<C, T, typename std::enable_if_t<std::is_member_object_pointer_v<T>>>
{
    static Property* create(const std::string& name, T accessor) {}
};



}   // namespace detail
}   // namespace reflect
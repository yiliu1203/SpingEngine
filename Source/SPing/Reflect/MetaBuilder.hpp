#pragma once
#include "Meta.h"
#include "Property.h"
#include "PropertyFactory.hpp"
#include "ReflectMacro.h"




namespace reflect {

template <typename T>
class SP_API MetaBuilder
{
public:
    MetaBuilder(Meta& meta)
        : meta_(&meta)
    {}

    template <typename A>
    MetaBuilder& property(const std::string& name, A accessor)
    {
        return addProperty(detail::PropertyFactory1<T, A>::create(name, accessor));
    }

private:
    MetaBuilder& addProperty(Property* property)
    {
        meta_->addProperty(property);
        return *this;
    }

private:
    Meta* meta_;
};

}   // namespace reflect
#pragma once
#include "Macro.h"
#include "Meta.h"
#include "Property.h"

namespace reflect {

template <typename T>
class SP_API MetaBuilder
{
public:
    MetaBuilder(Meta& meta)
        : meta_(&meta)
    {}

    template <typename F>
    MetaBuilder& property(const std::string& name, F accesser)
    {
        return addProperty()
    }

private:
    MetaBuilder& addProperty(Property* property) { return *this; }

private:
    Meta* meta_;
};

}   // namespace reflect
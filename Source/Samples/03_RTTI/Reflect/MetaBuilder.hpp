#pragma once
#include "Meta.h"
#include "Macro.h"
#include "Property.h"

namespace reflect
{


template <typename T>
class SP_API MetaBuilder
{

public:
    MetaBuilder(Meta& meta) : meta_(&meta)
    {
    }

    template<typename F>
    MetaBuilder& property(const std::string& name, F accesser) {
        return addProperty()
    }

private:
    MetaBuilder& addProperty(Property* property){
        return *this;
    }


private:
    Meta* meta_;


};

}
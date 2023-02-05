#pragma once
#include "../TypeErasure/Typeid.hpp"

namespace SPing::RTTI
{

template <typename T> class MetaBuilder;


class Meta
{
    struct BaseInfo
    {
        const Meta* base;
        int offset;
    };

    Meta(const TypeId& id, const std::string& name)
    {
    }


    public:
        friend class MetaManager;
        template <typename T>
        static MetaBuilder<T> Declare();
};


    
} // namespace SPing::RTTI



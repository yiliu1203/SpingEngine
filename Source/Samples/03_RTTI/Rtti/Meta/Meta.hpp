#pragma once
#include "MetaManager.h"
#include "../Detail/Typeid.hpp"

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
        static MetaBuilder<T> Declare()
        {
            using TypeDecl = StaticTypeDecl<T>;
            Meta& meta = MetaManager::Instance().AddMeta(TypeDecl::id(), TypeDecl::name());
            return MetaBuilder<T>(meta);
        }
};


    
} // namespace SPing::RTTI



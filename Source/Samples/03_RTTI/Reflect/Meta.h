#pragma once
#include <vector>
#include <map>
#include <memory>
#include "MetaManager.h"
#include "TypeId.hpp"
#include "Macro.h"
#include "Property.h"



namespace reflect
{

template <typename T> class MetaBuilder;
class Property;
class Function;

class SP_API Meta
{

public:
    using PropertyPtr = std::shared_ptr<Property>;
    friend class MetaManager;
    template <typename T>
    static MetaBuilder<T> Declare()
    {
        using TypeDecl = StaticTypeDecl<T>; // 实例化一个 Type类型，只有id和name
        Meta& meta = MetaManager::Instance().AddMeta(TypeDecl::id(), TypeDecl::name());
        return MetaBuilder<T>(meta);
    }

    const TypeId& id() { return this->id_; }
    const std::string name() { return this->name_; }

    const PropertyPtr getProprity(const std::string& name) {
        for(auto item : properties_) {
            if (name.compare(item->name())) {
                return item;
            }
        }
        return nullptr;
    }
    

private:
    
    struct BaseInfo
    {
        const Meta* base;
        int offset;
    };

    Meta(const TypeId& id, const std::string& name) : id_{id}, name_{name}
    {
    }

    bool addProperty(Property* property)
    {
        if (getProprity(property->name())) {
            RTTI_ERROR("Add Repeat Proprity ")
        }

    }


public:
    size_t sizeT_{0};
private:
    const TypeId id_;
    const std::string name_;
    std::vector<BaseInfo> base_list_;
    std::vector<PropertyPtr> properties_;




};


    
} // namespace SPing::RTTI



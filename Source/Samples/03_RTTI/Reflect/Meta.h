#pragma once
#include "Macro.h"
#include "MetaManager.h"
#include "Property.h"
#include "TypeId.hpp"
#include <map>
#include <memory>
#include <vector>




namespace reflect {

template <typename T>
class MetaBuilder;
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
        using TypeDecl = StaticTypeDecl<T>;   // 实例化一个 Type类型，只有id和name
        Meta& meta     = MetaManager::Instance().AddMeta(TypeDecl::id(), TypeDecl::name());
        return MetaBuilder<T>(meta);
    }

    const TypeId&     id() { return this->id_; }
    const std::string name() { return this->name_; }

    const PropertyPtr getProprity(const std::string& name) const
    {
        // for (auto& item : properties_) {
        //     if (name.compare(item->name())) {
        //         return item;
        //     }
        // }
        return nullptr;
    }

private:
    template <typename T>
    friend class MetaBuilder;
    struct BaseInfo
    {
        const Meta* base;
        int         offset;
    };

    Meta(const TypeId& id, const std::string& name)
        : id_{id}
        , name_{name}
        , base_list_{0}
        , properties_{0}

    {}

    bool addProperty(Property* property)
    {
        // if (getProprity(property->name())) {
        //     RTTI_ERROR("Add Repeat Proprity ")
        // }
        ASSERT(getProprity(property->name()) == nullptr, "Add Repeat Proprity");

        return true;
    }


public:
    size_t sizeT_{0};

private:
    const TypeId             id_;
    const std::string        name_;
    std::vector<BaseInfo>    base_list_;
    std::vector<PropertyPtr> properties_;
};



}   // namespace reflect

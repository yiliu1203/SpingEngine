#pragma once
// #include "MetaManager.h"
#include "Property.h"
#include "ReflectMacro.h"
#include "TypeAlias.h"
#include "TypeId.hpp"
#include <map>
#include <memory>
#include <vector>




namespace reflect {
template <typename T>
class MetaBuilder;

class MetaManager;



class SP_API Meta
{

public:
    using PropertyPtr = std::shared_ptr<reflect::Property>;
    friend class reflect::MetaManager;
    template <typename T>
    static reflect::MetaBuilder<T> Declare()
    {
        using TypeDecl = StaticTypeDecl<T>;   // 实例化一个 Type类型，只有id和name
        Meta& meta     = reflect::MetaManager::Instance().AddMeta(TypeDecl::id(), TypeDecl::name());
        return reflect::MetaBuilder<T>(meta);
    }

    const TypeId&     id() const { return this->id_; }
    const std::string name() const { return this->name_; }

    void SetBase(const Meta* base) { base_ = base; }

    const PropertyPtr getProperty(const std::string& name) const
    {
        for (auto item : properties_) {
            if (name.compare(item->name()) == 0) {
                return item;
            }
        }
        return nullptr;
    }

    bool IsTypeOf(const TypeId& typeId) const
    {
        // if (id_ == typeid) return true;
        return false;
    }

    bool IsTypeOf(const std::string& typeName) const
    {
        // if (id_ == typeid) return true;
        return false;
    }

private:
    template <typename T>
    friend class MetaBuilder;

    Meta(const TypeId& id, const std::string& name)
        : id_{id}
        , name_{name}
        , base_{nullptr}
        , properties_(0)   // 特别注意 这里的初始化，如果用 {}，调用initiallist
    {}

    bool addProperty(reflect::Property* property)
    {
        ASSERT(getProperty(property->name()) == nullptr, "Add Repeat Proprity");
        properties_.push_back(std::shared_ptr<reflect::Property>{property});

        return true;
    }

public:
    size_t sizeT_{0};

private:
    const TypeId      id_;
    const std::string name_;
    /** Vector 的初始化要特别注意，如果用{}， 会使用initial_list的版本，如果希望分配size, 用（）初始化*/
    const Meta*              base_;
    std::vector<PropertyPtr> properties_;
};

}   // namespace reflect

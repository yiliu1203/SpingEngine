#pragma once
#include <map>
#include "Typeid.hpp"
#include "Macro.h"

namespace reflect
{

class Meta;

class SP_API MetaManager
{
public:
    static MetaManager& Instance() {
        static MetaManager mm;
        return mm;
    }

    Meta& AddMeta(const TypeId& id, const std::string& name);

    const Meta* Get(const TypeId& id) const
    {
        auto iter = meta_ids_.find(id.hash_code());
        return iter == meta_ids_.end() ? nullptr : iter->second;
    }


    bool IsClassExists(const TypeId& id) noexcept
    {
        return !(meta_ids_.find(id.hash_code()) == meta_ids_.end());
    }

    bool IsClassExists(const std::string& name) {
        return !(meta_names_.find(name) == meta_names_.end());
    }

private:
    std::map<std::string, Meta*> meta_names_;
    std::map<std::size_t, Meta*> meta_ids_;
};

}

#pragma once
#include <map>
#include "Typeid.hpp"
#include "Macro.h"

namespace reflect
{

class Meta;

class MetaManager
{
public:
    static MetaManager& Instance() {
        static MetaManager mm;
        return mm;
    }

    Meta& AddMeta(const TypeId& id, const std::string& name);

    const Meta* Get(const TypeId& id) const
    {
        auto iter = metaMapIds_.find(id.hash_code());
        return iter == metaMapIds_.end() ? nullptr : iter->second;
    }


    bool IsClassExists(const TypeId& id) noexcept
    {
        return !(metaMapIds_.find(id.hash_code()) == metaMapIds_.end());
    }

    bool IsClassExists(const std::string& name) {
        return !(metaMapNames_.find(name) == metaMapNames_.end());
    }

private:
    std::map<std::string, Meta*> metaMapNames_;
    std::map<std::size_t, Meta*> metaMapIds_;
};

}

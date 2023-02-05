#include "MetaManager.h"
#include "../Meta/Meta.hpp"

namespace SPing::RTTI
{

Meta& MetaManager::AddMeta(const TypeId& id, const std::string& name)
{
    if (IsClassExists(id) || IsClassExists(name)) {
            RTTI_ERROR("ADD META ERROR");
        }

        Meta* meta = new Meta(id, name);
        metaMapIds_.insert({id.hash_code(), meta});
        metaMapNames_.insert({name, meta});
}



}
#include "MetaManager.h"
#include "Meta.h"

namespace reflect
{

Meta& MetaManager::AddMeta(const TypeId& id, const std::string& name)
{
    if (IsClassExists(id) || IsClassExists(name)) {
            RTTI_ERROR("ADD META ERROR");
        }

        Meta* meta = new Meta(id, name);
        meta_ids_.insert({id.hash_code(), meta});
        meta_names_.insert({name, meta});
}



}
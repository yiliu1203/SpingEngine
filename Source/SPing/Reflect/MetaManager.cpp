#include "MetaManager.h"
#include "Meta.h"




namespace reflect {

Meta& MetaManager::AddMeta(const TypeId& id, const std::string& name)
{
    ASSERT(!(IsClassExists(id) || IsClassExists(name)), "ADD META ERROR ", "Param name:", name)
    Meta* meta = new Meta(id, name);
    meta_ids_.insert({id.hash_code(), meta});
    meta_names_.insert({name, meta});
    return *meta;
}




}   // namespace reflect
#pragma once
#include "MetaManager.h"
#include "TypeId.hpp"
#include "Macro.h"
#include <vector>
#include <map>


namespace reflect
{

template <typename T> class MetaBuilder;
class Property;
class Function;

class SP_API Meta
{
    struct BaseInfo
    {
        const Meta* base;
        int offset;
    };

    Meta(const TypeId& id, const std::string& name) : id_{id}, name_{name}
    {
    }


    public:
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
    

    public:
        size_t sizeT_{0};
    private:
        const TypeId id_;
        const std::string name_;
        std::vector<BaseInfo> base_list_;
        // std::map<std::string, >




};


    
} // namespace SPing::RTTI



#include "reflect.hpp"

namespace reflect {

namespace detail {

void Registry::Register(std::unique_ptr<TypeDescriptor> desc)
{
    if (desc.get()) {
        // 【unique_ptr注意】这里也要用move,否则生命周期过后就销毁了
        type_descs_.insert({desc->name(), std::move(desc)});
    }
}

TypeDescriptor* Registry::Find(const std::string& name)
{
    auto item = type_descs_.find(name);
    if (item == type_descs_.end()) {
        return nullptr;
    }
    return item->second.get();
}

std::ostream& operator<<(std::ostream& cout, const TypeDescriptor& typeDescriptor)
{
    cout << "--------type info for " << typeDescriptor.name_ << "------------" << std::endl;
    for (auto item = typeDescriptor.member_vars_.begin(); item != typeDescriptor.member_vars_.end();
         item++) {
        cout << "Membervariable name:" << item->name() << std::endl;
    };

    for (auto item = typeDescriptor.member_funcs_.begin();
         item != typeDescriptor.member_funcs_.end();
         item++) {
        cout << "MemberFunc name:" << item->name() << " isconst:" << item->is_const() << std::endl;
    };
    return cout;
}


}   // namespace detail

}   // namespace reflect
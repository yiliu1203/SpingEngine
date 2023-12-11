#include "Registry.h"
#include "TypeDescriptor.h"


namespace Refl
{

    Registry& Registry::Register(std::unique_ptr<TypeDescriptor> type_desc)
    {
        REFL_ASSERT(_descs.find(type_desc->GetName()) == _descs.end());
        _descs.insert({type_desc->GetName(), std::move(type_desc)});
        return *this;
    }

    


}
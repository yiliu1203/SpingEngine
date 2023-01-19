#pragma once
#include "SPingPre.h"
#include "Object.h"

namespace SPing
{

class SP_API Context : public RefCount {
friend class Object;

public:
    void RegSubSystem(Object* object);
    // void RemoveSubSystem(StringHash)
};
    
}
// namespace Sping

#include "Utils.h"

namespace SPing {

std::ostream& operator<<(std::ostream& os, const TypeId& typeId)
{
    os << typeId.hash_code();
    return os;
}


}   // namespace SPing
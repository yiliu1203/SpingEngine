#include "StringHash.h"

namespace SPing {

std::ostream& operator << (std::ostream& out, const StringHash& val) {
    out << val.value_;
    return out;
}

}
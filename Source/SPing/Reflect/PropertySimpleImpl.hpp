#pragma once
#include "Property.h"

namespace reflect {
namespace detail {



template <typename GETSET_ASSESSOR>
class SimplePropertyImpl : public Property
{
public:
    SimplePropertyImpl(const std::string& name, GETSET_ASSESSOR accessor)
        : Property(name, GETSET_ASSESSOR::PropTraits::ExposedTraits::valueKind)
        , accessor_{accessor}
    {}

    ~SimplePropertyImpl() {}

    bool isReadAble() const final { return true; }

    bool isWriteAble() const final { return GETSET_ASSESSOR::PropTraits::isWriteable; }

    Value getValue(void* obj) const final
    {
        return Value{accessor_.accessor_.getter(*(static_cast<typename GETSET_ASSESSOR::ClassType*>(obj)))};
    }

    void setValue(void* obj, const Value& val) const final
    {
        val.To<typename GETSET_ASSESSOR::InterfaceType::SetType>();
        accessor_.accessor_.setter(*(static_cast<typename GETSET_ASSESSOR::ClassType*>(obj)),
                                   val.To<typename GETSET_ASSESSOR::InterfaceType::SetType>());
    }

private:
    GETSET_ASSESSOR accessor_;
};

}   // namespace detail
}   // namespace reflect
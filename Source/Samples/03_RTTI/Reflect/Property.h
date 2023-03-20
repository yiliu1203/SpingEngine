#pragma once
#include "Macro.h"
#include "TypeId.hpp"
#include "ValueWrap.hpp"

namespace reflect
{

class SP_API Property
{

public:
    ~Property(){}
    const std::string& name() const { return name_;}
    const ValueKind kind() const { return value_kind_;}
    Value get(void* obj) const {
        return getValue(obj);
    }

    void set(void* obj, const Value& val) const {
        setValue(obj, val);
    }

protected:
    template <typename T> friend class ClassBuilder;
    Property(const std::string& name, ValueKind kind): name_(name), value_kind_(kind) {
    }
    virtual bool isReadAble() const;
    virtual bool isWriteAble() const;

    virtual Value getValue(void* obj) const = 0;
    virtual void setValue(void* obj, const Value& val) const = 0;


private:

    std::string name_;
    ValueKind value_kind_;

};

}
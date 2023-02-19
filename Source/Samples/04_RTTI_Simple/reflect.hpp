#pragma once


#include <any>
#include <functional>
#include <iostream>
#include <memory>
#include <string>
#include <tuple>
#include <unordered_map>
#include <vector>

namespace reflect
{

namespace detail
{

class TypeDescriptor;

class MemberVariable
{
public:

    template<typename C, typename R>
    MemberVariable(R C::*var)
    {
        getter_ = [var](std::any obj)-> std::any {
            return std::any_cast<const C* >(obj)->(*var);
        };

        setter_ = [var](std::any obj, std::any val) {
            auto *self = std::any_cast<const C*> obj;
            self->*var = std::any_cast<R>(val);
        }
    }
    
    /**
     * 这里就很难受了， 还得用GetValue<R>(obj) 这种形式。 如果要统一起来的话，需要一个统一的Value和Object
    */
    template<typename C, typename R>
    R GetValue(const C& c)
    {
        return std::any_cast<R>(getter_(&c));
    }

    template <typename C, typename T>
    void SetValue(C& c, T val)
    {
        setter_(&c, val);
    }


private:
    std::string name_;
    std::function<std::any(std::any)> getter_;
    std::function<std::any(std::any, std::any)> setter_;
};

template <typename C, typename R, typename... Args>
class MemberFunction
{
public:



private:
    std::string name_;
    bool is_const_;
    std::function<std::any(std::any)> fn_{nullptr};

};


class RawTypeDescriptorBuilder
{
public:
    explicit RawTypeDescriptorBuilder(const std::string& name){
    }

    template <typename T, typename C>
    void AddMemberVar(const std::string& name, T C::*var) 
    {
    }

    template <typename T, typename FUNC>
    void AddMemberFunc(const std::string& name, FUNC func)
    {

    }

    
};

}   // detail

template <typename T>
class TypeDescriptorBuilder
{
public:
    explicit TypeDescriptorBuilder(const std::string& name): raw_builder_{name}
    {
    }

    template <typename V, typename C>
    TypeDescriptorBuilder& AddMemberVar(const std::string& name, V C::*var)
    {
        raw_builder_.AddMemberVar(name, var);
        return *this;
    }

    template <typename FUNC>
    TypeDescriptorBuilder& AddMemberFunc(const std::string& name, FUNC func) {
        raw_builder_.AddMemberFunc(name, func);
        return *this;
    }

private:
    detail::RawTypeDescriptorBuilder raw_builder_;

};

template <typename T>
TypeDescriptorBuilder<T> AddClass(const std::string& name)
{
    TypeDescriptorBuilder<T> builder{name};
    return builder;
}


} // reflect
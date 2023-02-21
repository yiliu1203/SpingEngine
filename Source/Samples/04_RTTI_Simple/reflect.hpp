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

/**
 * MemberVariable 本身只是存储了一个名字，通过模板元的技术，生成匹配各种 
*/

class MemberVariable
{
public:
    template<typename C, typename R>
    MemberVariable(R C::*var)
    {
        getter_ = [var](std::any obj)-> R {
            return std::any_cast<const C* >(obj)->*var;
        };

        setter_ = [var](std::any obj, std::any val) -> std::any {
            C* c = std::any_cast<C* > (obj);
            c->*var = std::any_cast<R>(val);
            return std::any{};
        };
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
    friend class RawTypeDescriptorBuilder;
    std::string name_;
    std::function<std::any(std::any)> getter_;
    std::function<std::any(std::any, std::any)> setter_;
};


class MemberFunction
{
public:

    template<typename C, typename R, typename... Args>
    explicit MemberFunction(R (C::*func)(Args...)) {
        fn_ = [func](std::any any_obj) ->std::any
        {
            using tuple_t = std::tuple<C&, Args...>;
            auto *tp_ptr = std::any_cast<tuple_t*>(obj_args)
            return std::apply(func, *tp_ptr);
        }
        is_const_ = false;
    }

    template<typename C, typename R, typename... Args>
    explicit MemberFunction(R (C::*func)(Args...) const) {
        fn_ = [func](std::any any_obj) ->std::any
        {
            using tuple_t = std::tuple<C&, Args...>;
            auto *tp_ptr = std::any_cast<tuple_t*>(obj_args)
            return std::apply(func, *tp_ptr);
        }
        is_const_ = true;
    }

    template<typename C, typename... Args>
    std::any Invoke(C& c, Args&&... args)
    {
        if (is_const_)
        {
            auto tp = std::make_tuple(std::reference_wrapper<const C>(c), args...); // 这里成了右边值
            return fn_(&tp);
        }
        else 
        {
            auto tp = std::make_tuple(std::reference_wrapper<C>(c), args...);
            return fn_(&tp);    // 这里成了右值
        }
    }

private:

    friend class RawTypeDescriptorBuilder;

    std::string name_;
    bool is_const_;
    std::function<std::any(std::any)> fn_{nullptr};

};

class TypeDescriptor
{
public:



private:

    friend class RawTypeDescriptorBuilder;
    std::string name_;
    std::vector<MemberVariable> member_vars_;
    std::vector<MemberFunction> member_funcs_;
};






class RawTypeDescriptorBuilder
{
public:
    explicit RawTypeDescriptorBuilder(const std::string& name){
        desc_ = std::make_unique<TypeDescriptor>();
        desc_->name_ = name;
    }

    template <typename T, typename C>
    void AddMemberVar(const std::string& name, T C::*var) 
    {
        MemberVariable mv{var};
        mv.name_ = name;
        /** 这里用移动构造，隐式定义的移动构造会调用各个成员的移动构造 */
        desc_->member_vars_.push_back(std::move(mv));
    }

    template <typename T, typename FUNC>
    void AddMemberFunc(const std::string& name, FUNC func)
    {

    }

    // ~RawTypeDescriptorBuilder();


private:
    std::unique_ptr<TypeDescriptor> desc_{nullptr};
    
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


}
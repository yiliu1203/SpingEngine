#pragma once

#include <any>
#include <functional>
#include <iostream>
#include <memory>
#include <string>
#include <tuple>
#include <unordered_map>
#include <vector>
#include <type_traits>
#include <optional>
#include <format>
#include <string_view>

namespace reflect
{

namespace detail
{


class TypeDescriptor;


class Registry {
public:
    static Registry& instance() {
        static Registry inst;
        return inst;
    };

    TypeDescriptor* Find(const std::string& name);
    void Register(std::unique_ptr<TypeDescriptor> desc);

private:
    std::unordered_map<std::string, std::unique_ptr<TypeDescriptor>> type_descs_;
};


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

    const std::string& name() const
    {
        return name_;
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
            auto *tp_ptr = std::any_cast<tuple_t*>(any_obj);
            if constexpr (std::is_void_v<R>) {
                std::apply(func, *tp_ptr);
                return {};
            }
            else {
                return std::apply(func, *tp_ptr);
            }
        };
        is_const_ = false;
    }

    template<typename C, typename R, typename... Args>
    explicit MemberFunction(R (C::*func)(Args...) const) {
        fn_ = [func](std::any any_obj) -> std::any
        {
            using tuple_t = std::tuple<C&, Args...>;
            auto *tp_ptr = std::any_cast<tuple_t*>(any_obj);
            // 【注意这里一定要加 constexpr, 否则这里 一定为false, 看起来就是用于进入else分支】
            // 而且要加上（）： if constexpr (...)
            if constexpr (std::is_void_v<R>) {
                std::apply(func, *tp_ptr);
                return {};
            }
            else {
                return std::any{std::apply(func, *tp_ptr)};
            }
            
        };
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

    const std::string& name() const
    {
        return name_;
    }
    bool is_const() const
    {
        return is_const_;
    }

private:

    friend class RawTypeDescriptorBuilder;

    std::string name_;
    bool is_const_;
    // 【这里没有模板生成对应的类型，就得用给一个统一个类型了】
    std::function<std::any(std::any)> fn_{nullptr};

};

class TypeDescriptor
{
public:

    TypeDescriptor() = default;
    TypeDescriptor(const TypeDescriptor&) = default;
    std::string& name() {return name_;}

    ~TypeDescriptor(){
        member_vars_.clear();
        member_funcs_.clear();
    }

    friend std::ostream& operator << (std::ostream& cout, const TypeDescriptor& typeDescriptor);

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

    // 【移动构造函数参数不要加const】
    RawTypeDescriptorBuilder(RawTypeDescriptorBuilder&& right) = default;
    RawTypeDescriptorBuilder& operator= (const RawTypeDescriptorBuilder&) = delete;
    RawTypeDescriptorBuilder& operator= (RawTypeDescriptorBuilder&&) = default;



    template <typename T, typename C>
    void AddMemberVar(const std::string& name, T C::*var) 
    {
        MemberVariable mv{var};
        mv.name_ = name;
        /** 这里用移动构造，隐式定义的移动构造会调用各个成员的移动构造 */
        desc_->member_vars_.push_back(std::move(mv));
    }

    template <typename FUNC>
    void AddMemberFunc(const std::string& name, FUNC func)
    {
        MemberFunction mf{func};
        mf.name_ = name;
        desc_->member_funcs_.push_back(std::move(mf));
    }

    /** 
     * 这里定义了析构之后 默认的构造函数似乎就不再生成了，编译报错了，所以要手动定义下几个构造函数
     * 【特殊的】这里禁用了赋值构造和赋值运算符，主要是 unique_ptr 结构是禁用拷贝的，所以用移动构造。当然也不符合这里的设计思想
    */
    ~RawTypeDescriptorBuilder(){
        Registry::instance().Register(std::move(desc_));
    }


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

    TypeDescriptorBuilder(TypeDescriptorBuilder&& builder): raw_builder_(std::move(builder.raw_builder_)){
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
    return std::move(builder);
}


}
#pragma once
#include "ReflectMacro.h"
#include <any>
#include <array>
#include <cassert>
#include <functional>
#include <iostream>
#include <tuple>
#include <type_traits>
#include <utility>


namespace reflect {

enum class ERefType
{
    NoneRef,
    LeftRef,
    RightRef,
};

namespace trait {

template <typename T>
struct RefTrait : public std::integral_constant<ERefType, ERefType::NoneRef>
{};

template <typename T>
struct RefTrait<T&> : public std::integral_constant<ERefType, ERefType::LeftRef>
{};

template <typename T>
struct RefTrait<T&&> : public std::integral_constant<ERefType, ERefType::RightRef>
{};


template <typename T>
struct IsConst : public std::false_type
{};

template <typename T>
struct IsConst<T&> : public std::false_type
{};

template <typename T>
struct IsConst<T*> : public std::false_type
{};

template <typename T>
struct IsConst<const T*> : public std::true_type
{};

template <typename T>
struct IsConst<const T&> : public std::true_type
{};

}   // namespace trait


/**对 一个Param的包装，完美转发， 区分值类型，引用类型，左值引用还是右值引用， 是否const。
 * Value 的核心是 需要把输入类型转换到函数参数的类型，这个本来是由编译器做，现在要用Value暂存，然后去做这个转换
 **/
class SP_API Value
{

public:
    template <typename T>
    // 【如果匹配到 const int *, 则这里的 T == const int *&,  实际上这里都要么是 &， 要么是 &&】
    Value(T&& val)
    {
        ref_type_ = trait::RefTrait<T>::value;
        is_const_ = trait::IsConst<T>::value;

        // [实际不可能出现]
        if (ref_type_ == ERefType::NoneRef) {
            storage_ = val;
        }
        else {
            storage_ = &val;
        }
    }

    Value(Value&& other)
    {
        std::swap(storage_, other.storage_);
        std::swap(is_const_, other.is_const_);
        std::swap(ref_type_, other.ref_type_);
    }

    Value(const Value& other)
        : storage_{other.storage_}
        , is_const_{other.is_const_}
        , ref_type_{other.ref_type_}
    {}

    /**To 目标类型，可能是值，可能是左值引用，可能是右值引用
     **/
    template <typename T>
    T To() const
    {
        constexpr ERefType tRefType = trait::RefTrait<T>::value;
        constexpr bool     tIsConst = trait::IsConst<T>::value;
        using RawT                  = std::remove_cv_t<std::remove_reference_t<T>>;
        if constexpr (tRefType == ERefType::NoneRef) {
            if (ref_type_ == ERefType::NoneRef) {
                if (is_const_) {
                    return std::any_cast<std::add_const_t<RawT>>(storage_);
                }
                else {
                    return std::any_cast<RawT>(storage_);
                }
            }
            else if (ref_type_ == ERefType::LeftRef || ref_type_ == ERefType::RightRef) {
                if (is_const_) {
                    // 这里会做一次复制拷贝构造
                    return *std::any_cast<const RawT*>(storage_);
                }
                else {
                    return *std::any_cast<RawT*>(storage_);
                }
            }
            else {
                std::runtime_error("Value::To()");
                return {};
            }
        }
        else if constexpr (tRefType == ERefType::LeftRef) {

            ASSERT(ref_type_ != ERefType::NoneRef, "Value::To() Because [target is Ref, And Self is Copy, HasError]");
            ASSERT(!(is_const_ && !tIsConst), "Value::To(): Because const to NoneConst");

            if (is_const_) {
                return *std::any_cast<const RawT*>(storage_);
            }
            else {
                return *std::any_cast<RawT*>(storage_);
            }
        }
        else if constexpr (tRefType == ERefType::RightRef) {
            ASSERT(ref_type_ != ERefType::NoneRef, "Value::To() Because [target is Ref, And Self is Copy, HasError]");
            if (ref_type_ == ERefType::LeftRef) {
                if (is_const_)
                    return std::move(*std::any_cast<const RawT*>(storage_));
                else {
                    return std::move(*std::any_cast<RawT*>(storage_));
                }
            }
            else if (ref_type_ == ERefType::RightRef) {
                if (is_const_) {
                    return std::move(*std::any_cast<const RawT*>(storage_));
                }
                else {
                    return std::move(*std::any_cast<RawT*>(storage_));
                }
            }
        }
        else {
            throw std::runtime_error("Value::To()");
            return {};
        }
    }
    // [不支持使用 T*类型, 要使用引用类型]
    template <typename T>
    Value(const T* val) = delete;

    bool IsConst() { return is_const_; }
    int  RefType() { return static_cast<int>(ref_type_); }

private:
    std::any storage_{};
    bool     is_const_{false};
    ERefType ref_type_{ERefType::NoneRef};
};

template <typename... Args, size_t N, size_t... Is>
std::tuple<Args...> AsTuple(std::array<Value, N>& arr, std::index_sequence<Is...>)
{
    return std::forward_as_tuple(arr[Is].template To<Args>()...);
}


template <typename... Args, size_t N, typename = std::enable_if_t<N == sizeof...(Args)>>
std::tuple<Args...> AsTuple(std::array<Value, N>& arr)
{
    return AsTuple<Args...>(arr, std::make_index_sequence<N>{});
}

class FuncWrap
{
public:
    template <typename... Args>
    explicit FuncWrap(void (*func)(Args...))
    {
        n_args_ = sizeof...(Args);
        func_   = [func](void* args_ptr) {
            // Value 作为桥梁，实参列表解包-》Value-》形参类型-》打包
            auto& args = *static_cast<std::array<Value, sizeof...(Args)>*>(args_ptr);
            auto  tp   = AsTuple<Args...>(args);
            std::apply(func, tp);
        };
    }

    template <typename... Args>
    void Invoke(Args&&... args)
    {
        ASSERT(n_args_ == sizeof...(Args), "Args Size Error");
        // 实参参数包 -> 类型为Value的array
        std::array<Value, sizeof...(Args)> arr = {Value{std::forward<Args>(args)...}};
        func_(&arr);
    }

private:
    std::function<void(void*)> func_{nullptr};
    int                        n_args_{0};
};


}   // namespace reflect
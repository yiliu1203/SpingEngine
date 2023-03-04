#include <any>
#include <array>
#include <functional>
#include <iostream>
#include <tuple>
#include <type_traits>
#include <utility>

namespace reflect
{

enum class ReferenceType
{
    NoneRef,
    LeftRef,
    RightRef,
};

namespace trait 
{
    
    template <typename T>
    struct RefTrait : public std::integral_constant<ReferenceType, ReferenceType::NoneRef>{};

    template <typename T>
    struct RefTrait<T&> : public std::integral_constant<ReferenceType, ReferenceType::LeftRef>{};

    template <typename T>
    struct RefTrait<T&&> : public std::integral_constant<ReferenceType, ReferenceType::RightRef>{};
    

    template <typename T>
    struct IsConst {};

    template <typename T>
    struct IsConst<T&> : public std::false_type {};

    template <typename T>
    struct IsConst<T*> : public std::false_type {};

    template <typename T>
    struct IsConst<const T*> : public std::true_type {};

    template <typename T>
    struct IsConst<const T&> : public std::true_type {};

}

namespace detail
{




/**
 * 对 一个Param的包装，完美转发， 区分值类型，引用类型，左值引用还是右值引用， 是否const。
 *
*/

class Value
{

public:

    template <typename T>
    // 【如果匹配到 const int *, 则这里的 T == const int *&】
    Value(T&& val)
    {
        ref_type_ = trait::RefTrait<T>::value;
        is_const_ = trait::IsConst<T>::value;

        if (ref_type_ == ReferenceType::NoneRef) {
            storage_ = val;
        }
        else {
            storage_ = &val;
        }
    }

    /* To 目标类型，可能是值，可能是左值引用，可能是右值引用*/
    template <typename T>
    T To() 
    {
        constexpr ReferenceType tRefType = trait::RefTrait<T>::value;
        constexpr ReferenceType tIsConst = trait::IsConst<T>::value;
        if constexpr (tRefType == ReferenceType::NoneRef) {

        }
        else if constexpr (tRefType == ReferenceType::LeftRef) {

        }
        else if constexpr (tRefType == ReferenceType::RightRef) {

        }
        else {
            std::runtime_error(" T To() Error");
            return {};
        }



    }


    // [不支持使用 T*类型, 要使用引用类型]
    template <typename T>
    Value(const T* val) = delete;


    bool IsConst() {
        return is_const_;
    }

    int RefType() {
        return static_cast<int>(ref_type_);
    }





private:
    std::any storage_{};
    bool is_const_{false};
    ReferenceType ref_type_{ReferenceType::NoneRef};
    

};


}

}
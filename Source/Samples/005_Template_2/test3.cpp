
#include <string>
#include <iostream>
#include <type_traits>
#include <vector>
#include <compare> 
#include <algorithm> 

#include <array>
#include <functional>
#include <iterator>
#include <string_view>
#include <cassert>



template <size_t N>
struct fixed_string {
    char _chars[N+1];

    using type = fixed_string;
    // constexpr auto size = char;
    constexpr fixed_string(const char (&array)[N + 1]) noexcept
    {
      std::copy(std::begin(array), std::end(array), _chars);
    }

    constexpr size_t size() const {
        return N;
    }
};

template <size_t N>
fixed_string(const char (&arr)[N])-> fixed_string<N-1>;


template <typename C, typename R, typename... A>
struct MemberFuncDetail
{
    typedef R ReturnType;
    explicit constexpr MemberFuncDetail(R (C::*func)(A...) const) {
    }
    explicit constexpr MemberFuncDetail(R (C::*func)(A...)) {
    }
};







template <typename T>
struct TypeInfo {
    typedef T type; 
    template <auto>
    struct MemberField {
        // static_assert(S.size() <= 0, "input string should be in member_filed_list");
    };

    template <fixed_string S>
    struct MemberField<typename decltype(S)::type> {            // 做不到。。。。
        static_assert(S.size() <= 0, "input string should be in member_filed_list");
        // static constexpr std::string_view FieldName{""};
        // static constexpr auto pointer{nullptr}; 
    };

    template <size_t N>
    struct MemberField<N> {
        static_assert(N < 0, "input index should be in member_filed_list");
    };

    // template<> struct MemberField<"name">{
    //     static constexpr auto FieldName {"name"};
    //     static constexpr auto pointer{&type::name};
    // };

    // template<> struct MemberField<0>{
    //     static constexpr auto FieldName {"name"};
    // };
    static constexpr size_t MemberCount = 0;
};

// #define TYPE_BEGIN(TypeName) \
//     template <> struct TypeInfo<TypeName> {                \
//         typedef TypeName type;                          \
//         typedef TypeInfo MetaType;                      \
//         template <fixed_string S>                       \
//         struct MemberField {                            \
//             static_assert(S.size() <= 0, "input string should be in member_filed_list");    \
//             static constexpr std::string_view FieldName{""};        \
//             static constexpr auto pointer{nullptr};     \
//         };                                              \
//         template <size_t N>                             \
//         struct IndexMemberField {                       \
//         };                     \

// #define TYPE_FIELD(FIELD)                                   \
//         template<> struct MemberField<#FIELD>{              \
//         static constexpr std::string_view FieldName {#FIELD};           \
//         static constexpr auto pointer {&type::FIELD};               \
//         };                                                      \
//         template<> struct IndexMemberField<__COUNTER__>{        \
//             static constexpr std::string_view FieldName {#FIELD};    \
//             static constexpr auto pointer {&type::FIELD};       \
//         };                                                      \

// #define TYPE_FUNC(FUNC_NAME)                                   \
//         template<> struct MemberField<#FUNC_NAME>{              \
//         static constexpr std::string_view FieldName {#FUNC_NAME};       \
//         using return_type = typename std::type_identity<decltype(MemberFuncDetail(&type::FUNC_NAME))>::type::ReturnType; \
//         };                                                      \

// #define TYPE_END                                                \
//         static constexpr size_t MemberCount{__COUNTER__};       \
//     };                                                          \

// using return_type = decltype(type().FUNC_NAME());

struct People
{
	std::string name;
	int age;
	std::string get_name() const { return name; };
};

// TYPE_BEGIN(People)
//     TYPE_FIELD(name)
//     TYPE_FIELD(age)
//     TYPE_FUNC(get_name)
// TYPE_END



template <typename T, size_t N>
void travel_type_field(const T& t) {

    if constexpr (N < 0) {
    }

    else if constexpr (N == 0) {
        std::cout << TypeInfo<T>::template IndexMemberField<0>::FieldName << ":" << &t->*(TypeInfo<T>::template IndexMemberField<0>::pointer) << std::endl;
    }
    else {
        travel_type_field<T, N-1>(t);
        std::cout << TypeInfo<T>:: template IndexMemberField<N>::FieldName << ":" << &t->*(TypeInfo<T>::template IndexMemberField<N>::pointer) << std::endl;
    }
}


template<typename T>
void travel_type(const T& t) {
    travel_type_field<T, 1>(t);
}



// ----TEST fixed_string -----
template <fixed_string>
struct Literal {
    using type = char;
};
//---------------------------

int main() 
{

    // -------- TEST fixed_string----------------
    fixed_string str{""};
    std::cout << str.size();
    std::cout << typeid(Literal<"hello">::type).name() << std::endl;
    std::cout << "---------------"<< std::endl;
    // ----------------------------------------------

    // part 1
	People p{ "Jim", 20 };

	// std::cout << TypeInfo<People>::MemberField<0>::FieldName;
    return 0;
}

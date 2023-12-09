#include <iostream>
#include <cmath>
#include <functional>
#include <tuple>
#include <string_view>

template<size_t N>
struct StringLiteral {
    constexpr StringLiteral(const char (&str)[N]) {
        std::copy_n(str, N, value);
    }
    char value[N];
};

#define TSTR(s) ([] { struct tmp { static constexpr auto get() { return std::basic_string_view{s}; } }; \
  return TSTRH(tmp{}); }())
template<typename C, C... chars> struct TStr { using Char = C;
    template<typename T> static constexpr bool Is(T = {}) { return std::is_same_v<T, TStr>; }
    static constexpr const Char* Data() { return data; } static constexpr std::size_t Size() { return sizeof...(chars); }
    static constexpr std::basic_string_view<Char> View() { return data; }
  private: static constexpr Char data[]{ chars...,Char(0) }; };
  template<typename Char, typename T, std::size_t... Ns> constexpr auto TSTRHI(std::index_sequence<Ns...>) { return TStr<Char, T::get()[Ns]...>{}; }
  template<typename T> constexpr auto TSTRH(T){return TSTRHI<typename decltype(T::get())::value_type,T>(std::make_index_sequence<T::get().size()>{});}

template<typename Name, typename T>
struct Field {
    T value;
    using TName = Name;
    constexpr Field(Name, T value) : value{ value } {}
    static constexpr std::string_view name = Name::View();
};

template<typename... Elems>
struct FieldList {
    std::tuple<Elems...> elems;
    static constexpr std::size_t size = sizeof...(Elems);
    constexpr FieldList(Elems... elems) : elems{ elems... } {}

    template<typename Name>
    constexpr const auto& Find(Name) const {
        constexpr std::size_t idx = []() {
            constexpr decltype(Name::View()) names[]{ Elems::name... };
            for (std::size_t i = 0; i < sizeof...(Elems); i++) {
                if (Name::View() == names[i])
                    return i;
            }
            return static_cast<std::size_t>(-1);
        }();
        static_assert(idx != static_cast<std::size_t>(-1));
        return Get<idx>();
    }

    template<std::size_t N>
    constexpr const auto& Get() const {
        return std::get<N>(elems);
    }

    template<typename T>
    constexpr void ForEachPrint(const T& obj) const {
        // 构造匿名函数，输出成员值
        auto output = [&obj](const auto& field) {
            // std::cout << std::is_member_pointer_v<decltype(field.value)> << std::endl;
            if constexpr (!std::is_member_function_pointer_v<decltype(field.value)>) {
                std::cout << field.name << " : " << obj.*(field.value) << std::endl;
            }
        };
        // 折叠表达式
        auto wrap = [&output](auto&&... args) {
            (output(std::forward<decltype(args)>(args)), ...);
        };
        std::apply(wrap, elems);
    }
};

template<typename T>
struct TypeInfo;

template<typename T, typename... Bases>
struct TypeInfoBase {
    using Type = T;
    static constexpr FieldList member = { Bases{}... };
};

struct People
{
	std::string name;
	int age;
	std::string get_name() const { return name; };
	int get_age() const { return age; };
};

template<>
struct TypeInfo<People> : TypeInfoBase<People>
{
    static constexpr FieldList member = {
        Field {TSTR("name"), &Type::name},
        Field {TSTR("age"), &Type::age},
        Field {TSTR("get_name"), &Type::get_name},
        Field {TSTR("get_age"), &Type::get_age},
    };

    // 特例化时才执行
    template<StringLiteral N>
    struct MemberField {
        static constexpr const auto& self = member.Find(TSTR(N.value));
        static constexpr const auto& FieldName = self.name;
        using return_type = std::invoke_result_t<decltype(self.value), Type>;
    };
};

template<typename T>
void travel_type(const T& obj) {
    TypeInfo<T>{}.member.ForEachPrint(obj);
}

int main()
{
	//part 1
	People p{ "Jim", 20 };

	static_assert(TypeInfo<People>::MemberField<"name">::FieldName  == "name");
	static_assert(TypeInfo<People>::MemberField<"age">::FieldName  == "age");
	// static_assert( TypeInfo<People>::MemberField<"test">::FieldName == "test");	// static_assert failed: 'input string should be in member_filed_list'
	static_assert( std::is_same_v<TypeInfo<People>::MemberField<"get_name">::return_type, std::string>);
	static_assert( std::is_same_v<TypeInfo<People>::MemberField<"get_age">::return_type, int>);

	//part 2
    travel_type(p);

	return 1;
}



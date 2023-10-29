#include <iostream>
#include <algorithm>

#include <type_traits>
#include <vector>
#include <tuple>


template<size_t N>
struct const_string {
	constexpr const_string(const char(&str)[N]) {
		std::copy_n(str, N, value);
	}
	size_t size = N;
	char value[N];

	template<size_t M>
	constexpr bool operator==(const char(&str)[M]) const {
		if constexpr (N != M) {
			return false;
		}
		else {
			for (size_t i = 0; i < M; i++) {
				if (value[i] != str[i]) {
					return false;
				}
			}
			return true;
		}
	}


	explicit constexpr operator const char* () const noexcept
	{
		return value;
	}

	explicit operator std::string() const noexcept
	{
		return value;
	}
	explicit operator std::string() noexcept
	{
		return value;
	}

};


template <typename T>
struct TypeInfo {

};

template<typename T>
struct FalseTypeCheck {
	constexpr FalseTypeCheck() {
		static_assert(std::is_same<T,std::true_type>::value, "input string should be in member_filed_list");
	}

	template<size_t M>
	constexpr bool operator==(const char(&str)[M]) const {
		static_assert(std::is_same<T, std::true_type>::value, "input string should be in member_filed_list");
		return false;
	}
};

enum MemberType {
	Field,
	Function,
};


#define GENTYPE(TypeName) \
template <> \
struct TypeInfo<TypeName> { \
	typedef TypeName ClassType; \
	TypeInfo<ClassType>() = default; \
    template <int>\
	struct _MemberField;\
	template<const_string>\
	struct MemberField;\
	constexpr static const int memberOff = __COUNTER__ + 1;\
	template<const_string name>\
	struct MemberField : std::false_type \
	{\
		typedef MemberField<name> FalseMemberField;\
		static constexpr FalseTypeCheck<FalseMemberField> FieldName;\
	};

#define ENDTYPE() \
	constexpr static const int memberCount = __COUNTER__ - memberOff;\
	template< size_t... Idx>\
	static std::tuple<TypeInfo<ClassType>::_MemberField<Idx>...> EnumerateMembers(std::index_sequence<Idx...>) {};\
	struct DeclaredMemberList \
	{ using type = decltype(EnumerateMembers(std::make_index_sequence<TypeInfo<ClassType>::memberCount>{})); };\
};

template <typename T>
using ReflField = TypeInfo< T>::DeclaredMemberList::type;

#define FIELD(name) \
	constexpr static const int name##Indext = __COUNTER__ - memberOff;\
	template<>\
	struct _MemberField<name##Indext>\
	{\
		static constexpr MemberType type = MemberType::Field;\
		static constexpr const_string FieldName = #name;\
		typedef decltype(ClassType::name) FieldType;\
		static constexpr auto pointer{ &ClassType::name };\
		static FieldType Get(ClassType* value)\
		{\
			return (FieldType)(value)->name;\
		}\
	};\
	typedef _MemberField<name##Indext> name##Type;\
	template<>\
	struct MemberField<#name> : name##Type{};

#define FUNCTION(name) \
	constexpr static const int name##Indext = __COUNTER__ - memberOff;\
	template<>\
	struct _MemberField<name##Indext>\
	{\
		static constexpr MemberType type = MemberType::Function;\
		static constexpr const_string FieldName = #name;\
		static constexpr auto pointer{ &ClassType::name };\
		typedef std::invoke_result_t< decltype(&ClassType::name), ClassType> return_type;\
		static return_type Get(ClassType* value)\
		{\
			return (return_type)(value)->name();\
		};\
	};\
	typedef _MemberField<name##Indext> name##Type;\
	template<>\
	struct MemberField<#name> : name##Type{};

template <size_t N, typename T, typename P>
void PrintTuple(T t, P p) {
	constexpr int index = N - 1;
	if constexpr (index > 0)
		PrintTuple<index>(t, p);

	if (std::get<index>(t).type == MemberType::Field)
		std::cout << (std::string)std::get<index>(t).FieldName << "=" << std::get<index>(t).Get(&p) << std::endl;
}

template <size_t Idx,typename T, typename P>
void __PrintTupleEx(T t, P p)
{
	if (std::get<Idx>(t).type == MemberType::Field)
		std::cout << (std::string)std::get<Idx>(t).FieldName << "=" << std::get<Idx>(t).Get(&p) << std::endl;
}

template <typename T, typename P, size_t... Idx>
void PrintTupleEx(T t, P p, std::index_sequence<Idx...>) {
	(__PrintTupleEx<Idx>(t, p), ...);
}

struct People
{
	std::string name;
	int age;
	std::string get_name() const { return name; };
};


GENTYPE(People)
FIELD(name)
FIELD(age)
FUNCTION(get_name)
ENDTYPE()

void travel_type(People& p)
{
	ReflField<People> a;
	//PrintTuple<std::tuple_size<decltype(a)>::value>(a, p);
	PrintTupleEx(a, p, std::make_index_sequence<std::tuple_size<decltype(a)>::value>{});
}

int main()
{
	//part 1
	People p{ "Jim", 20 };
	static_assert(TypeInfo<People>::MemberField<"name">::FieldName == "name");
	//static_assert( TypeInfo<People>::MemberField<"test">::FieldName == "test");	// static_assert failed: 'input string should be in member_filed_list'
	static_assert(std::is_same_v<TypeInfo<People>::MemberField<"get_name">::return_type, std::string>);

	//part 2
	travel_type(p);

	return 1;
}
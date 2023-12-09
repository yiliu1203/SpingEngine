// class Foo;
// class type_info__;

// namespace refl_impl::metadata {
//     template<> struct type_info__<Foo> {
//         typedef Foo type;
//         static constexpr auto name{ ::refl::util::make_const_string("Foo") };
//         static constexpr size_t member_index_offset = 1213 + 1;
//         template <size_t, typename = void> struct member {};
        
//         template<typename Unused__> struct member<285 - member_index_offset, Unused__> {
//         typedef ::refl::member::field member_type;
//         static constexpr auto name{ ::refl::util::make_const_string("x") };
//         static constexpr auto attributes{ ::refl::detail::make_attributes<::refl::attr::usage::field>() };
//         public:
//             typedef decltype(type::x) value_type;
//             static constexpr auto pointer{ &type::x };
//         template <typename Proxy> struct remap {
//             template <typename... Args> decltype(auto) x(Args&&... args) {
//                 return Proxy::invoke_impl(static_cast<Proxy&>(*this), ::std::forward<Args>(args)...);
//             } template <typename... Args> decltype(auto) x(Args&&... args) const {
//                 return Proxy::invoke_impl(static_cast<const Proxy&>(*this), ::std::forward<Args>(args)...);
//             }
//         };
//         };
        
       

//         template<typename Unused__> struct member<213 - member_index_offset, Unused__> {
//         typedef ::refl::member::function member_type;
//         static constexpr auto name{ ::refl::util::make_const_string("f") };
//         static constexpr auto attributes{ ::refl::detail::make_attributes<::refl::attr::usage::function>() };
//             public:
//                 template<typename Self, typename... Args> static constexpr auto invoke(Self&& self, Args&&... args) -> decltype(::refl::detail::forward_cast<Self, type>(self).f(::std::forward<Args>(args)...)) {
//                 return ::refl::detail::forward_cast<Self, type>(self).f(::std::forward<Args>(args)...);
//                 }
//                 template<typename... Args> static constexpr auto invoke(Args&&... args) -> decltype(::refl::detail::head_t<type, Args...>::f(::std::declval<Args>()...)) {
//                     return ::refl::detail::head_t<type, Args...>::f(::std::forward<Args>(args)...);
//         } template <typename Dummy = void> static constexpr auto pointer() -> decltype(&::refl::detail::head_t<type, Dummy>::f) {
//             return &::refl::detail::head_t<type, Dummy>::f;
//         } template <typename Pointer> static constexpr auto resolve() -> ::std::decay_t<decltype(Pointer(&type::f))> {
//             return Pointer(&type::f);
//         } template <typename Proxy> struct remap {
//             template <typename... Args> decltype(auto) f(Args&&... args) {
//                 return Proxy::invoke_impl(static_cast<Proxy&>(*this), ::std::forward<Args>(args)...);
//             } template <typename... Args> decltype(auto) f(Args&&... args) const {
//                 return Proxy::invoke_impl(static_cast<const Proxy&>(*this), ::std::forward<Args>(args)...);
//             }
//         };
//         };
        
        
//         static constexpr size_t member_count{ 236 - member_index_offset };
//     };
// }

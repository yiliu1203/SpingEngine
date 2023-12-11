#include <any>
#include <functional>
#include <string>
#include <tuple>

namespace Refl
{

class MemberFunction
{

public:
    MemberFunction() = delete;

    template<typename C, typename R, typename ...Args>
    explicit MemberFunction(R (C::*func)(Args...)) : _is_const{false}, _is_void{std::is_void_v<R>}
    {
        using args_t = std::tuple<C&, Args...>;
        _function = [this, func](std::any args) -> std::any {
            auto * p_args = std::any_cast<args_t*>(args);
            if constexpr(std::is_void_v<R>)
            {
                std::apply(func, *p_args);
                return {};
            }
            else
            {
                return std::apply(func, *p_args);
            }
        };
    }

    template<typename C, typename R, typename ...Args>
    explicit MemberFunction(R (C::*func)(Args...) const ) : _is_const{true}, _is_void{std::is_void_v<R>}
    {

        using args_t = std::tuple<const C&, Args...>;
        _function = [this, func](std::any args) -> std::any {
            auto * p_args = std::any_cast<args_t*>(args);
            if constexpr(std::is_void_v<R>)
            {
                std::apply(func, *p_args);
                return {};
            }
            else
            {
                return std::apply(func, *p_args);
            }
        };
    }

    template<typename C, typename ...Args>
    std::any Invoke(C& c, Args... args)
    {
        if (_is_const) {

            // auto args_tuple = std::forward_as_tuple(std::reference_wrapper<const C>(c), args...);
            auto args_tuple = std::make_tuple(std::reference_wrapper<const C>(c), args...);
            return _function(&args_tuple);
        }
        else {

            // auto args_tuple = std::forward_as_tuple(std::reference_wrapper<C>(c), args...);
            auto args_tuple = std::make_tuple(std::reference_wrapper<C>(c), args...);
            return _function(&args_tuple);
        }
    }

private:

    const std::string _name;
    const bool _is_const;
    const bool _is_void;
    std::function<std::any(std::any obj)> _function;
};


}
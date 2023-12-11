#include <any>
#include <functional>
#include <string>


namespace Refl
{

class MemeberVariable
{
public:
    MemeberVariable() = delete;

    template<typename C, typename Var>
    explicit MemeberVariable(Var C::*var)
    {
        _getter = [var](std::any obj) -> std::any
        {
            return std::any_cast<const C*>(obj)->*var;
        };

        _setter = [var](std::any obj, std::any val)
        {
            auto *self = set::any_cast<const C*>(obj);
            self->*val = std::any_cast<Var>(val);
        }
        
    }

    const std::string& GetName() const
    {
        return _name;
    }

    template<typename C, typename Var>
    Var GetValue(const C& obj) const
    {
        return std::any_cast<Var>(_getter(&obj));
    }

    template<typename C, typename Var>
    void SetValue(C& obj, Var value)
    {
        _setter(&obj, value);
    }

private:
    const std::string _name;
    std::function<std::any(std::any)> _getter { nullptr };
    std::function<void(std::any, std::any)> _setter {nullptr};
};


}
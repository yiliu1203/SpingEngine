#pragma once
#include "SPingPre.h"

namespace SPing
{

enum class EventType
{
    None = 0,
    WindowClose, WindowResize, WindowFocus, WindowLostFocus, WindowMoved,
    AppTick, AppUpdate, AppRender,
    KeyPressed, KeyReleased, KeyTyped,
    MouseButtonPressed, MouseButtonReleased, MouseMoved, MouseScrolled,
};

// enum EventCategory
// {
//     None=0,
//     EventCategoryApplication    = BIT(0),
//     EventCategoryInput          = BIT(1),
//     EventCategoryKeyboard       = BIT(2),
//     EventCategoryMouse          = BIT(3),
//     EventCategoryMouseButton    = BIT(4),
// };

class Event
{
public:
    virtual ~Event() = default;
    bool Handled = false;
    virtual EventType GetEventType() const = 0;
    virtual const char* GetName() const = 0;
    virtual const std::string ToString() const { return GetName();}
};

}
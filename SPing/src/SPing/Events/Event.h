#ifndef SP_EVENT_H
#define SP_EVENT_H

#include "SPingPre.h"
#include "SPing/Core.h"
#include "spdlog/fmt/fmt.h"

namespace SPing {

	enum class EventType
	{
		None = 0,
		WindowClose, WindowResize, WindowFocus, WindowLostFocus, WindowMoved,
		AppTick, AppUpdate, AppRender,
		KeyPressed, KeyReleased,
		MouseButtonPressed, MouseButtonReleased, MouseMoved, MouseScolled,

	};

	enum EventCategory
	{
		None = 0,
		EventCategoryApplication = BIT(0),
		EventCategoryInput = BIT(1),
		EventCategoryKeyboard = BIT(2),
		EvnetCategoryMouse = BIT(3),
		EventCategoryMouseButton = BIT(4),

	};


#define EVENT_CLASS_TYPE(typeName)  static EventType GetStaticType(){return EventType::##typeName;}\
									virtual EventType GetEventType() const override {return GetStaticType();}\
									virtual const char * GetName() const override {return #typeName;}\

#define EVENT_CLASS_CATEGORY(category) virtual int GetCategoryFlags() const override {return category;}
	

	class SP_API Event
	{
		friend class EventDispatcher;
	public:
		virtual EventType GetEventType() const = 0;
		virtual const char* GetName() const = 0;
		virtual int GetCategoryFlags() const = 0;
		virtual std::string ToString() const { return GetName(); }

		inline bool IsInCategory(EventCategory category) { return GetCategoryFlags() & category; }

	protected:
		bool m_handled = false;
		

	};
							

	class SP_API EventDispatcher
	{
		template <typename T>
		using EventFn = std::function<bool(T&)>;

	public:
		EventDispatcher(Event& event) : _Event(event) {}

		template<typename T>
		bool Dispatch(EventFn<T> func)
		{
			if (_Event.GetEventType() == T::GetStaticType())
			{
				_Event.m_handled = func(*(T*)(&_Event));

				SP_CORE_INFO("{0} Be Handled", _Event.GetName());

				return true;
			}
			return false;
		}

	private:
		Event& _Event;
	
	};





	template <typename T>
	struct fmt::formatter<T, std::enable_if_t<std::is_base_of<SPing::Event, T>::value, char>> :
		fmt::formatter<std::string> {
		template <typename FormatCtx>
		auto format(const SPing::Event& a, FormatCtx& ctx) {
			return fmt::formatter<std::string>::format(a.ToString(), ctx);
		}
	};



}





#endif

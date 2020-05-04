#ifndef SP_WINDOW_H
#define SP_WINDOW_H

#include "SPingPre.h"
#include "SPing/Core.h"
#include "SPing/Events/Event.h"

namespace SPing
{
	class SP_API WindowProps
	{
	public:
		WindowProps(const std::string& title = "Hello SPing", unsigned int width = 1334, unsigned int height = 750) :
			Title(title), Width(width), Height(height) {

		}

		std::string Title;
		unsigned int Width;
		unsigned int Height;

	};

	class SP_API Window
	{
	public:
		using EventCallbackFn = std::function<void(Event&)>;

		virtual ~Window()
		{
		}

		virtual void OnUpdate() = 0;
		virtual unsigned int GetWidth() const = 0;
		virtual unsigned int GetHeight() const = 0;
		
		virtual void SetEventCallback(const EventCallbackFn& callback) = 0;
		virtual void SetVSync(bool enabled) = 0;
		virtual bool IsVSync() const = 0;

		static Window* Create(const WindowProps& props = WindowProps());

	};



}


#endif

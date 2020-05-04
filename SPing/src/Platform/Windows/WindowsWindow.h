#ifndef SP_WINDOWSWINDOW_H
#define SP_WINDOWSWINDOW_H

#include "SPing/Window.h"
#include "GLFW/glfw3.h"


namespace SPing
{

	class SP_API WindowsWindow : public Window
	{
	public:
		WindowsWindow(const WindowProps&);
		virtual ~WindowsWindow();

		void OnUpdate() override;
		unsigned int GetWidth() const override { return _Data.Width; }
		unsigned int GetHeight() const override { return _Data.Height; }

		void SetEventCallback(const EventCallbackFn& callback) override { _Data.EventCallback = callback; }
		void SetVSync(bool enabled) override;
		bool IsVSync() const override { return _Data.VSync; }

	private:
		virtual void Init(const WindowProps& props);
		virtual void ShutDown();

	private:

		GLFWwindow* _Window;

		struct WindowData
		{
			std::string Title;
			unsigned int Width, Height;
			bool VSync;
			
			EventCallbackFn EventCallback;

		};

		WindowData _Data;


	};




}

#endif

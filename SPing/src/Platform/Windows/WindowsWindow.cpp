#include "SPingPre.h"
#include "WindowsWindow.h"

namespace SPing {

	static bool s_GLFWInitialized = false;

	Window* Window::Create(const WindowProps& props /* = WindowProps() */)
	{
		return new WindowsWindow(props);
	}

	WindowsWindow::WindowsWindow(const WindowProps& props)
	{
		Init(props);
	}

	WindowsWindow::~WindowsWindow()
	{
		ShutDown();
	}

	void WindowsWindow::Init(const WindowProps& props)
	{
		_Data.Width = props.Width;
		_Data.Height = props.Height;
		_Data.Title = props.Title;

		SP_INFO("Init Window {0}, {1}, {2}", props.Title, props.Width, props.Height);

		if (!s_GLFWInitialized)
		{
			int success = glfwInit();
			SP_ASSERT(success, "GLFW INIT FAILED");
			s_GLFWInitialized = true;
		}

		_Window = glfwCreateWindow(_Data.Width, _Data.Height, _Data.Title.c_str(), nullptr, nullptr);
		glfwMakeContextCurrent(_Window);
		glfwSetWindowUserPointer(_Window, &_Data);
		SetVSync(true);
	}

	void WindowsWindow::ShutDown()
	{
		glfwDestroyWindow(_Window);
	}

	void WindowsWindow::OnUpdate()
	{
		glfwPollEvents();
		glfwSwapBuffers(_Window);
	}

	void WindowsWindow::SetVSync(bool enabled)
	{
		if (enabled)
			glfwSwapInterval(1);
		else
			glfwSwapInterval(0);
		_Data.VSync = enabled;
	}













}
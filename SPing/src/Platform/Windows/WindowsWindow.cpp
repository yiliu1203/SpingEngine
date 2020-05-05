#include "SPingPre.h"
#include "WindowsWindow.h"
#include "SPing/Events/ApplicationEvent.h"
#include "SPing/Events/KeyEvent.h"
#include "SPing/Events/MouseEvent.h"

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
		
		glfwSetWindowCloseCallback(_Window, [](GLFWwindow* _glfwWindow) {
			WindowCloseEvent e;
			WindowData& data = *(WindowData*)glfwGetWindowUserPointer(_glfwWindow);
			data.EventCallback(e);
			});
		
		glfwSetWindowSizeCallback(_Window, [](GLFWwindow* _glfwWindow, int width, int height) {
			WindowData& data = *(WindowData*)glfwGetWindowUserPointer(_glfwWindow);
			data.Height = height;
			data.Width = width;
			WindowResizeEvent e(width, height);
			data.EventCallback(e);
			});

		glfwSetKeyCallback(_Window, []	(GLFWwindow * _glfwWindow, int key, int scancode, int action, int mods) 
			{
				WindowData& data = *(WindowData*)glfwGetWindowUserPointer(_glfwWindow);
				switch (action)
				{
					case GLFW_PRESS:
					{
						KeyPressedEvent e(key, 0);
						data.EventCallback(e);
						break;
					}

					case GLFW_RELEASE:
					{
						KeyReleaseedEvent e(key);
						data.EventCallback(e);
						break;
					}

					case GLFW_REPEAT:
					{
						KeyPressedEvent e(key, 1);
						data.EventCallback(e);
						break;
					}
				}
			});

		glfwSetMouseButtonCallback(_Window, [](GLFWwindow * _glfwWindow,  int button, int action, int mods) 
			{
				WindowData& data = *(WindowData*)glfwGetWindowUserPointer(_glfwWindow);

				switch (action)
				{
					case GLFW_PRESS:
					{
						MouseButtonPressedEvent e(button);
						data.EventCallback(e);
						break;
					}

					case GLFW_RELEASE:
					{
						MouseButtonPressedEvent e(button);
						data.EventCallback(e);
						break;
					}
				}
			});

		glfwSetCursorPosCallback(_Window, [](GLFWwindow* _glfwWindow, double xpos, double ypos) {
			WindowData& data = *(WindowData*)glfwGetWindowUserPointer(_glfwWindow);
			MouseMovedEvent e((float)xpos, (float)ypos);
			data.EventCallback(e);
			});
		
	

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
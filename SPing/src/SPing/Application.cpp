#include "SPingPre.h"
#include "Application.h"
#include "SPing/Log.h"
#include "SPing/Events/ApplicationEvent.h"
#include "GLFW/glfw3.h"

namespace SPing {

	

	Application::Application()
	{
		//_Window = std::make_unique<Window>(Window::Create());
		_Window = std::unique_ptr<Window>(Window::Create());

	}

	Application::~Application()
	{
	}

	void Application::Run()
	{
		WindowResizeEvent e(600, 800);
		SP_INFO(e);

		while (_IsRunning)
		{
			glClearColor(1, 0, 0, 1);
			glClear(GL_COLOR_BUFFER_BIT);
			_Window->OnUpdate();
		}
	}

}
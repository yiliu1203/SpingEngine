#include "SPingPre.h"
#include "Application.h"
#include "SPing/Log.h"
#include "SPing/Events/ApplicationEvent.h"

namespace SPing {

	Application::Application()
	{

	}

	Application::~Application()
	{
	}

	void Application::Run()
	{
		WindowResizeEvent e(600, 800);
		SP_CLIENT_INFO(e);

		while (true);
	}

}
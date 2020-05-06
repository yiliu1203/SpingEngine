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
		_Window->SetEventCallback(std::bind(&Application::OnEvent, this, std::placeholders::_1));

	}

	Application::~Application()
	{
	}

	void Application::OnEvent(Event& event)
	{
		SP_CORE_INFO("Event: ({0})", event);

		EventDispatcher eventDisPatcher(event);
		eventDisPatcher.Dispatch<WindowCloseEvent>([this](WindowCloseEvent & e) ->bool
			{
				Close();
				return true;
			});
		
		for (auto it = _LayerStack.end(); it != _LayerStack.begin();)
		{
			(*--it)->OnEvent(event);
			if (event.Handled)
				break;
		}
	}

	void Application::Run()
	{
		WindowResizeEvent e(600, 800);
		SP_INFO(e);

		while (_IsRunning)
		{
			glClearColor(1, 0, 0, 1);
			glClear(GL_COLOR_BUFFER_BIT);
			
			for (Layer* layer : _LayerStack)
				layer->OnUpdate();

			_Window->OnUpdate();

		}
	}

	void Application::Close()
	{
		_IsRunning = false;
	}

	void Application::PushLayer(Layer* layer)
	{
		_LayerStack.PushLayer(layer);
	}

	void Application::PushOverLayer(Layer* layer)
	{
		_LayerStack.PushOverlay(layer);
	}

}
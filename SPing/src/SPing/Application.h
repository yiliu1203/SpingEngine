#ifndef SP_APPLICATION_H

#define SP_APPLICATION_H

#include "Core.h"
#include "Window.h"
#include "SPing/Events/Event.h"
#include "SPing/LayerStack.h"


namespace SPing {

	class SP_API Application
	{
	public:
		Application();
		virtual  ~Application();
		void Run();

		void Close();

		void OnEvent(Event& event);

		void PushLayer(Layer* layer);
		void PushOverLayer(Layer* layer);


	private:
		std::unique_ptr<Window> _Window;
		bool _IsRunning;
		LayerStack _LayerStack;

	};
	
	Application* CreateApplication();

}



#endif

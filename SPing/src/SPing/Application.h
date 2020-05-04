#ifndef SP_APPLICATION_H

#define SP_APPLICATION_H

#include "Core.h"
#include "Window.h"

//#define SP_API __declspec(dllexport)  // ∆Ê›‚¡À°£°£°£

namespace SPing {

	class SP_API Application
	{
	public:
		Application();
		virtual  ~Application();
		void Run();

	private:
		std::unique_ptr<Window> _Window;
		bool _IsRunning;

	};
	
	Application* CreateApplication();

}



#endif

#include "App.h"
#include <iostream>
#include <sstream>

App::App() : appWindow(800, 600, "hello World")
{
}

int App::Go()
{
	MSG msg = { 0 };
	BOOL result = { 0 };
	

	while (true)
	{
		auto r = appWindow.ProcessMessage();
		if(r != std::nullopt)
		{
			return *r;
		}
		_DoFrame();
	}
	return 0;
}

void App::_DoFrame()
{
	const float c = 0.1f;
	appWindow.GetGraphics().ClearBuffer(c, c, c);
	//appWindow.GetGraphics().DrawTestTriangle();
	appWindow.GetGraphics().EndFrame();

}


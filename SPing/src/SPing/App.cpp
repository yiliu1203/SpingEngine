#include "App.h"
#include <iostream>
#include <sstream>
#include "SPingPre.h"
#include "Core/Thread.h"
#include "Core/WorkQueue.h"
#include "Core/Delegate.h"
#include "Core/Context.h"
#include "Core/ComponentBase.h"

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
		try
		{
			_DoFrame();
		}
		catch (LS3DException& e)
		{
			MessageBox(nullptr, e.what(), e.GetType(), MB_OK | MB_ICONEXCLAMATION);
		}
		catch (std::exception& e)
		{
			MessageBox(nullptr, e.what(), "Standard Exception", MB_OK | MB_ICONEXCLAMATION);
		}
		catch (...)
		{
			MessageBox(nullptr, "UnKnow ExceptionType", "UnKnow Exception", MB_OK | MB_ICONEXCLAMATION);
		}
	}
	return 0;
}

void App::_DoFrame()
{
	const float c = 0.1f;
	appWindow.GetGraphics().ClearBuffer(c, c, c);
	appWindow.GetGraphics().DrawTestTriangle();
	appWindow.GetGraphics().EndFrame();

}


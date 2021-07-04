#include "Window.h"
#include <Windows.h>
#include "WindowsMsgMap.h"
#include <iostream>
#include <sstream>
#include "App.h"


int CALLBACK WinMain(HINSTANCE hInstance, HINSTANCE prewInstance, LPSTR lpCmdLine, int nCmdShow)
{
	try
	{
		App app{};
		app.Go();

	}
	catch (LS3DException& e)
	{
		MessageBox(nullptr, e.what(), e.GetType(), MB_OK| MB_ICONEXCLAMATION);
	}
	catch (std::exception& e)
	{
		MessageBox(nullptr, e.what(), "Standard Exception", MB_OK | MB_ICONEXCLAMATION);
	}
	catch (...)
	{
		MessageBox(nullptr, "UnKnow ExceptionType", "UnKnow Exception", MB_OK | MB_ICONEXCLAMATION);
	}
	return -1;
	
	

}
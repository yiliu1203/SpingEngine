#include "Window.h"
#include <Windows.h>
#include "WindowsMsgMap.h"
#include <iostream>
#include <sstream>
#include "App.h"


int CALLBACK WinMain(HINSTANCE hInstance, HINSTANCE prewInstance, LPSTR lpCmdLine, int nCmdShow)
{

	App app{};
	app.Go();
	return -1;
	
}
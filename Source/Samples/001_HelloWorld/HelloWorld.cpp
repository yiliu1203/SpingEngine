#include <Windows.h>
#include "Engine/Application.h"
using namespace SPing;

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE prevInstance, PSTR cmdLine, int showCmd)
{
	Application app;
	app.Run();
	return 2;
}

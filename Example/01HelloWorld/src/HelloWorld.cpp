
#ifdef SP_PLATFORM_WIN
#include <Windows.h>
#endif



#include "Test.h"
#include "SPing/App.h"

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE prevInstance, PSTR cmdLine, int showCmd)
{
	App app;
	app.Go();
	return 1;
}
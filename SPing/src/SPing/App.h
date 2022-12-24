#pragma once
#include "Window.h"
#include "SPingPre.h"

class SP_API App
{
public:
	App();
	int Go();
private:
	void _DoFrame();

private:
	Window appWindow;
};
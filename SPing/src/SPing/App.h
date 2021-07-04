#pragma once
#include "Window.h"

class App
{
public:
	App();
	int Go();
private:
	void _DoFrame();

private:
	Window appWindow;
};
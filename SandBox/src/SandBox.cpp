#include <iostream>

#include "SPing.h"


class Sandbox : public SPing::Application
{
public:
	Sandbox()
	{

	}
	~Sandbox()
	{

	}

};


SPing::Application* SPing::CreateApplication()
{
	return new Sandbox();
}
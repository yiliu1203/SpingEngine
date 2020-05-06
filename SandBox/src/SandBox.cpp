#include <iostream>

#include "SPing.h"


class ExampleLayer : public SPing::Layer
{
public:
	ExampleLayer():Layer("ExampleLayer"){}

	void OnEvent(SPing::Event& event) override
	{
		SP_INFO("ExampleLayer OnEvent: {0}", event);
	}

};



class Sandbox : public SPing::Application
{
public:
	Sandbox()
	{
		PushLayer(new ExampleLayer());

	}
	~Sandbox()
	{

	}

};


SPing::Application* SPing::CreateApplication()
{
	return new Sandbox();
}
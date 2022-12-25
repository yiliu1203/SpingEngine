#include "Application.h"


namespace SPing
{


Application::Application()
    :window(800, 600, "Hello World"), exitCode_(0)
{
}

int Application::Run()
{
    SetUp();
    Start();
    while(window.ProcessMessage() != 0) {
        DoFrame();
    }
    Stop();
    return 1;
}

void Application::DoFrame() 
{    
}

}
#include "Application.h"


namespace SPing
{


Application::Application()
    :window_(800, 600, "Hello World"), exitCode_(0), engine_{}
{
}

int Application::Run()
{
    SetUp();
    Start();
    while(window_.ProcessMessage() != 0) {
        engine_.RunFrame();
    }
    Stop();
    return 1;
}


}
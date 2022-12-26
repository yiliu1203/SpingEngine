#pragma once

#include "SPingPre.h"
#include "WinWindow.h"
#include "Engine.h"

namespace SPing 
{

class SP_API Application {

public:
    explicit Application();
    int Run();

protected:
    virtual void SetUp() {};
    virtual void Start() {};
    virtual void Stop() {};

    int exitCode_;

private:
    WinWindow window_;
    Engine engine_;

};

}
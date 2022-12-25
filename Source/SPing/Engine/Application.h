#pragma once

#include "SPingPre.h"
#include "WinWindow.h"

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
    void DoFrame();

    int exitCode_;

private:
    WinWindow window;

};

}
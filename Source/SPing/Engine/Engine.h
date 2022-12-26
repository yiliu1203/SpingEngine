#pragma once

#include "SPingPre.h"

namespace SPing
{
    
class SP_API Engine 
{

public:
    Engine();
    ~Engine();
    bool Initialize();
    void RunFrame();
    
};

}


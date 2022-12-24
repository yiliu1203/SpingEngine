#pragma once

#include "SPingPre.h"

namespace SPing {

    class SP_API Application {
    
    public:
        explicit Application();
        virtual void SetUp() {};
        virtual void Start() {};
        virtual void Stop() {};
        int Run();

    private:
        void _DoFrame();

    };

}
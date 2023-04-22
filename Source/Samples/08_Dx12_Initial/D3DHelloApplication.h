#pragma once
#include "stdafx.h"

#include "DXSample.h"

class HelloApplication : public DXSample
{
public:
    HelloApplication(int width, int height, const std::string name);
    void OnInit() override;
    void OnDestroy() override;
    void OnKeyDown(UINT8 wparam) override;
    void OnKeyUp(UINT8 wparam) override;

    void OnUpdate() override;
    void OnRender() override;
};
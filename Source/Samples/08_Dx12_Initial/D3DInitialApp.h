#pragma once
#include "stdafx.h"

#include "DXSample.h"

class D3DInitialApp : public DXSample
{
public:
    D3DInitialApp(int width, int height, const std::string name);
    void OnInit() override;
    void OnDestroy() override;
    void OnKeyDown(UINT8 wparam) override;
    void OnKeyUp(UINT8 wparam) override;

    void OnUpdate() override;
    void OnRender() override;

private:
    static constexpr uint32_t FrameCount = 2;
    // D3DX12_VIEWPORT           viewport_;
};
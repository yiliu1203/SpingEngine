#pragma once
#include "Win32Application.h"
#include "stdafx.h"


class DXSample
{
public:
    DXSample(int width, int height, std::string name);
    virtual ~DXSample();

    virtual void OnInit()                = 0;
    virtual void OnKeyDown(UINT8 wparam) = 0;
    virtual void OnKeyUp(UINT8 wparam)   = 0;
    virtual void OnUpdate()              = 0;
    virtual void OnRender()              = 0;

    virtual void OnDestroy() = 0;

    const char* GetTitle() { return title_.c_str(); }
    int         GetWidth() { return width_; }
    int         GetHeight() { return height_; }

private:
    int         width_;
    int         height_;
    std::string title_;
};
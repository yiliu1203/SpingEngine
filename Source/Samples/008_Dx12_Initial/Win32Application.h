#pragma once
#include "DXSample.h"
#include "stdafx.h"


class DXSample;

class Win32Application
{
public:
    static int  Run(DXSample* pSample, HINSTANCE hInstance, int nCmdShow);
    static HWND GetHwnd() { return m_hwnd; }

protected:
    static LRESULT CALLBACK WindowProc(HWND hWnd, uint32_t message, WPARAM wParam, LPARAM lParam);

private:
    static HWND m_hwnd;
};

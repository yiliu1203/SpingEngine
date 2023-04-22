#include "D3DHelloApplication.h"
#include "stdafx.h"


_Use_decl_annotations_ int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE, LPSTR, int nCmdShow)
{
    HelloApplication sample(640, 480, "D3D12 Hello Triangle");
    return Win32Application::Run(&sample, hInstance, nCmdShow);
}
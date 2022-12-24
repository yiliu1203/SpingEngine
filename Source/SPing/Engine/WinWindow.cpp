#include "SPingPre.h"
#include "Engine/WinWindow.h"

namespace SPing
{

WinWindow::WindowClass WinWindow::WindowClass::wndClass;

const char* WinWindow::WindowClass::GetName() noexcept {
    return wndClassName;
}

const HINSTANCE WinWindow::WindowClass::GetInstance() noexcept {
    return wndClass.hInstance;
}
    
} // namespace SPing



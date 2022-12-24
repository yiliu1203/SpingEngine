#pragma once
#include "SPingPre.h"

namespace SPing 
{

class SP_API WinWindow
{
public:
    explicit WinWindow(int width, int height, const char* name);
    ~WinWindow();
    WinWindow(const WinWindow&) = delete;
    WinWindow& operator= (const WinWindow&) = delete;
    void SetTitile(const char* title) const noexcept;

private:
    int width_;
    int height_;
    HWND hWnd_;


private:
    class WindowClass {
    public:
        static const char* GetName() noexcept;
        static const HINSTANCE GetInstance() noexcept;
    public:
        WindowClass();
        ~WindowClass();
        static constexpr const char* wndClassName = "LD3D";
        static WindowClass wndClass;
        HINSTANCE hInstance;
    };
};
}


// tips: noexcept, delete
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


WinWindow::WindowClass::WindowClass()
    : hInstance(GetModuleHandle(nullptr))
{
    WNDCLASSEX wc = { sizeof(WNDCLASSEX) };  // cbsize 必须被设置为 sizeof(WNDCLASSEX)
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hbrBackground = nullptr;
	wc.hCursor = nullptr;
	wc.hIcon = nullptr;
	wc.hInstance = GetInstance();  // 应用程序实例的句柄
	wc.lpfnWndProc = HandleMsgSetup;  // 消息处理函数
	wc.lpszClassName = GetName();  // 窗口类的名字， 上面三个属性最重要了
	wc.hCursor = nullptr;
	wc.style = CS_OWNDC;
	//wc.hIconSm = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_APPLICATION));
	RegisterClassExA(&wc);
}

WinWindow::WindowClass::~WindowClass()
{
	UnregisterClass(GetName(), GetInstance());
}

WinWindow::WinWindow(int width, int height, const char* name) 
	:width_(width), height_(height)
{
	RECT wr;
	wr.left = 100;
	wr.right = width + wr.left;
	wr.top = 100;
	wr.bottom = height + wr.top;

	AdjustWindowRect(&wr, WS_CAPTION | WS_MINIMIZEBOX | WS_SYSMENU, FALSE);

	hWnd_ = CreateWindowEx(0, WindowClass::GetName(), name, WS_CAPTION | WS_MINIMIZEBOX | WS_SYSMENU,
		200, 200, wr.right - wr.left, wr.bottom - wr.top, nullptr, nullptr, WindowClass::GetInstance(), this);
	
	ShowWindow(hWnd_, SW_SHOWDEFAULT);
	SetWindowTextA(hWnd_, name);
}

WinWindow::~WinWindow()
{
}

void WinWindow::SetTitle(const char* title) const
{
	SetWindowTextA(hWnd_, title);
}

int WinWindow::ProcessMessage() const 
{
	MSG msg = { 0 };
	while (PeekMessage(&msg, nullptr, 0, 0, PM_NOREMOVE))  // PeekMessage 不会阻塞, 这个有bug ？？ 没有收到 WM_QUIT
	{
		int res = GetMessage(&msg, NULL, 0, 0);
		if (res)
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		else
		{
			break;
		}
	}
	if (msg.message == WM_QUIT)
		return msg.wParam;  // exist code， 也可能就是 0
	return 1;

}


LRESULT CALLBACK WinWindow::HandleMsgSetup(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) noexcept
{
	if (msg == WM_NCCREATE)  // 第一个Message
	{
		const CREATESTRUCT* const pCreate = reinterpret_cast<CREATESTRUCT*>(lParam);
		WinWindow* const pWnd = static_cast<WinWindow*>(pCreate->lpCreateParams);
		SetWindowLongPtr(hWnd, GWLP_USERDATA, reinterpret_cast<LONG_PTR>(pWnd));
		//SetWindowLongPtr(hWnd, GWLP_WNDPROC, reinterpret_cast<LONG_PTR>(&Window::HandleMsgTrans)); // 还可以修改这个
		return pWnd->HandleMsg(hWnd, msg, wParam, lParam);
	}

	else
	{
		WinWindow* const pWnd = reinterpret_cast<WinWindow*>(GetWindowLongPtr(hWnd, GWLP_USERDATA));
		return pWnd->HandleMsg(hWnd, msg, wParam, lParam);
	}

	return DefWindowProc(hWnd, msg, wParam, lParam);
}

LRESULT WinWindow::HandleMsg(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) noexcept
{
    switch (msg)
    {
    case WM_CLOSE:
        PostQuitMessage(0);
        break;
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    
    default:
        break;
    }
	return DefWindowProc(hWnd, msg, wParam, lParam);
}



    
} // namespace SPing



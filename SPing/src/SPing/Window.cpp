#include "Window.h"
#include "WindowsMsgMap.h"

Window::WindowClass Window::WindowClass::wndClass;

const char* Window::WindowClass::GetName() noexcept
{
	return wndClassName;
}

HINSTANCE Window::WindowClass::GetInstance() noexcept
{
	return wndClass.hInst;
}

Window::WindowClass::WindowClass() noexcept
	: hInst(GetModuleHandle(nullptr))
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
	RegisterClassEx(&wc);
}



Window::WindowClass::~WindowClass() noexcept
{
	UnregisterClass(GetName(), GetInstance());
}

Window::Window(int width, int height, const char* name)
	:width(width), height(height)
{
	//throw LS3DWIN_EXCEPT(1)   // 要测试需要先取消 noexcept 的修饰， 否则直接被系统abort 捕获， 
	RECT wr;
	wr.left = 100;
	wr.right = width + wr.left;
	wr.top = 100;
	wr.bottom = height + wr.top;

	WIN_ASSERT_BOOL(AdjustWindowRect(&wr, WS_CAPTION | WS_MINIMIZEBOX | WS_SYSMENU, FALSE))

		hWnd = CreateWindowEx(0, WindowClass::GetName(), name, WS_CAPTION | WS_MINIMIZEBOX | WS_SYSMENU,
			200, 200, wr.right - wr.left, wr.bottom - wr.top, nullptr, nullptr, WindowClass::GetInstance(), this);

	WIN_ASSERT_NULL(hWnd)

		ShowWindow(hWnd, SW_SHOWDEFAULT);


	pGrpahics = std::make_unique<Graphics>(hWnd);

}

Window::~Window()
{
	DestroyWindow(hWnd);
}

void Window::SetTitle(const char* title) const noexcept
{
	WIN_ASSERT_BOOL(SetWindowTextA(hWnd, title))
}

std::optional<int> Window::ProcessMessage() const noexcept
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
	return {};
}

Graphics& Window::GetGraphics()
{
	return *pGrpahics;
}

LRESULT CALLBACK Window::HandleMsgSetup(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) noexcept
{
	if (msg == WM_NCCREATE)  // 第一个Message
	{
		const CREATESTRUCTW* const pCreate = reinterpret_cast<CREATESTRUCTW*>(lParam);
		Window* const pWnd = static_cast<Window*>(pCreate->lpCreateParams);
		SetWindowLongPtr(hWnd, GWLP_USERDATA, reinterpret_cast<LONG_PTR>(pWnd));
		//SetWindowLongPtr(hWnd, GWLP_WNDPROC, reinterpret_cast<LONG_PTR>(&Window::HandleMsgTrans)); // 还可以修改这个
		return pWnd->HandleMsg(hWnd, msg, wParam, lParam);
	}

	else
	{
		Window* const pWnd = reinterpret_cast<Window*>(GetWindowLongPtr(hWnd, GWLP_USERDATA));
		return pWnd->HandleMsg(hWnd, msg, wParam, lParam);
	}

	return DefWindowProc(hWnd, msg, wParam, lParam);
}

LRESULT Window::HandleMsg(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) noexcept
{
	switch (msg)
	{
	case WM_CLOSE:
		// 点击关闭的时候 产生 wm_close, 默认的处理会产生 wm_destroy, 
		PostQuitMessage(0);
		break;
	case WM_DESTROY:
		// 默认不会处理 wm_destroy, 这里释放资源，所以要手动 产生 wm_quit, 操作系统才会清理窗口资源，外面的循环退出
		PostQuitMessage(0);
		break;

	case WM_KILLFOCUS:
		kbd.ClearState();
		break;

	case WM_SYSKEYDOWN:
		if ((lParam & 1 << 30) != 0 || kbd.autoRepeatEnabled)
			kbd.OnKeyPressed(static_cast<unsigned int> (wParam));
		break;

	case WM_SYSKEYUP:
		kbd.OnkeyRelease(static_cast<unsigned int> (wParam));
		break;

	case WM_KEYDOWN:
		if ((lParam & 1 << 30) != 0 || kbd.autoRepeatEnabled)
			kbd.OnKeyPressed(static_cast<unsigned int> (wParam));
		break;

	case WM_KEYUP:
		kbd.OnkeyRelease(static_cast<unsigned int> (wParam));
		break;

	case WM_CHAR:
		kbd.OnChar(static_cast<char> (wParam));
		break;

	case WM_MOUSEMOVE:
	{
		POINTS p = MAKEPOINTS(lParam);
		mouse.OnMouseMove(p.x, p.y);
		break;
	}
	case WM_LBUTTONDOWN:
	{
		POINTS P = MAKEPOINTS(lParam);
		mouse.OnLeftPressed(P.x, P.y);
		break;
	}

	case WM_LBUTTONUP:
	{
		POINTS P = MAKEPOINTS(lParam);
		mouse.OnLeftReleased(P.x, P.y);
		break;
	}

	case WM_RBUTTONDOWN:
	{
		POINTS P = MAKEPOINTS(lParam);
		mouse.OnRightPressed(P.x, P.y);
		break;
	}

	case WM_RBUTTONUP:
	{
		POINTS P = MAKEPOINTS(lParam);
		mouse.OnLeftReleased(P.x, P.y);
		break;
	}

	case WM_MOUSEWHEEL:
	{
		int zDelta = GET_WHEEL_DELTA_WPARAM(wParam);
		POINTS p = MAKEPOINTS(lParam);
		mouse.OnWheelDelta(p.x, p.y, zDelta);
		break;
	}

	default:
		break;
	}

	auto windowsMsgMap = WindowsMsgMap();
	//OutputDebugString(windowsMsgMap(msg, wParam, lParam).c_str());
	return DefWindowProc(hWnd, msg, wParam, lParam);
}


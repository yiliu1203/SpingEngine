#pragma once
#include <d3d11.h>
#include "DxgiInfoManager.h"
#include "d3dcompiler.h"

#pragma comment(lib, "d3d11.lib")
#pragma comment(lib, "D3DCompiler.lib")

class Graphics
{
public:
	Graphics(HWND hwnd);
	~Graphics() noexcept;
	Graphics(const Graphics&) = delete;
	Graphics& operator =(const Graphics&) = delete;
	void EndFrame();
	void ClearBuffer(float r, float g, float b) noexcept;

	void DrawTestTriangle();

protected:
private:

	wrl::ComPtr<ID3D11Device> comDevice;
	wrl::ComPtr<ID3D11DeviceContext> comDeviceContext;
	wrl::ComPtr<IDXGISwapChain> comDxgiSwapChain;
	wrl::ComPtr<ID3D11RenderTargetView> comTargetView;
};
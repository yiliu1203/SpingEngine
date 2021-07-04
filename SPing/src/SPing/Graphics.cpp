#include "Graphics.h"
#include "LS3DException.h"

Graphics::Graphics(HWND hwnd)
{
	DXGI_SWAP_CHAIN_DESC sd = {};
	sd.BufferDesc.Width = 0;
	sd.BufferDesc.Height = 0;
	sd.BufferDesc.Format = DXGI_FORMAT_B8G8R8A8_UNORM;
	sd.BufferDesc.RefreshRate.Numerator = 0;
	sd.BufferDesc.RefreshRate.Denominator = 0;
	sd.BufferDesc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;
	sd.BufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
	sd.SampleDesc.Count = 1;
	sd.SampleDesc.Quality = 0;
	sd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	sd.BufferCount = 1;
	sd.OutputWindow = hwnd;
	sd.Windowed = TRUE;
	sd.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;
	sd.Flags = 0;

	UINT flag = D3D11_CREATE_DEVICE_DEBUG;

	GFX_ASSERT_HR(D3D11CreateDeviceAndSwapChain(nullptr, D3D_DRIVER_TYPE_HARDWARE, nullptr, D3D11_CREATE_DEVICE_DEBUG, nullptr, 0,
		D3D11_SDK_VERSION, &sd, comDxgiSwapChain.GetAddressOf(), comDevice.GetAddressOf(), nullptr, comDeviceContext.GetAddressOf())
	);

	wrl::ComPtr<ID3D11Resource> comBackBuffer;
	GFX_ASSERT_HR(comDxgiSwapChain->GetBuffer(0, __uuidof(ID3D11Resource), reinterpret_cast<void**> (comBackBuffer.GetAddressOf())));
	GFX_ASSERT_HR(comDevice->CreateRenderTargetView(comBackBuffer.Get(), nullptr, comTargetView.GetAddressOf()));
}

void Graphics::EndFrame()
{
	GFX_ASSERT_HR(comDxgiSwapChain->Present(1u, 0));
}

void Graphics::ClearBuffer(float r, float g, float b) noexcept
{
	float color[4] = { r, g, b, 1.f };
	comDeviceContext->ClearRenderTargetView(comTargetView.Get(), color);

}

void Graphics::DrawTestTriangle()
{
	struct vertex
	{
		float x;
		float y;
		float z;
	};

	vertex vertices[] = {
		{0.0f, 0.5f, 0.5f},
		{0.5f, -0.5f, 0.5f},
		{-0.5f, -0.5f, 0.5f},
	};

	D3D11_BUFFER_DESC  buffDesc = { 0 };
	buffDesc.ByteWidth = sizeof vertices;
	buffDesc.StructureByteStride = sizeof vertex;
	buffDesc.Usage = D3D11_USAGE_DEFAULT;
	buffDesc.CPUAccessFlags = 0;
	buffDesc.MiscFlags = 0;
	buffDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;

	//create buffer
	wrl::ComPtr<ID3D11Buffer> comBuffer;
	D3D11_SUBRESOURCE_DATA sd = { 0 };
	sd.pSysMem = vertices;
	comDevice->CreateBuffer(&buffDesc, &sd, comBuffer.GetAddressOf());

	// create shader
	wrl::ComPtr<ID3D11VertexShader> vertexShader;
	wrl::ComPtr<ID3DBlob> blob;
	GFX_ASSERT_HR(D3DReadFileToBlob(L"VertexShader.cso", blob.GetAddressOf()));
	GFX_ASSERT_HR(comDevice->CreateVertexShader(blob->GetBufferPointer(), blob->GetBufferSize(), nullptr, vertexShader.GetAddressOf()));
	GFX_ASSERT_HR_ONLY_INFO(comDeviceContext->VSSetShader(vertexShader.Get(), nullptr, 0u));

	// create vertex input layout
	wrl::ComPtr< ID3D11InputLayout> comLayout;
	D3D11_INPUT_ELEMENT_DESC inputDesc[] = {
		{"POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0},
	};
	// 这里又需要 shader 是为了再做一次 符号检查
	comDevice->CreateInputLayout(inputDesc, 1u, blob->GetBufferPointer(), blob->GetBufferSize(), comLayout.GetAddressOf());
	// bind vertex input layout
	comDeviceContext->IASetInputLayout(comLayout.Get());


	wrl::ComPtr<ID3D11PixelShader> pixShader;
	GFX_ASSERT_HR(D3DReadFileToBlob(L"PixelShader.cso", blob.GetAddressOf()));
	GFX_ASSERT_HR(comDevice->CreatePixelShader(blob->GetBufferPointer(), blob->GetBufferSize(), nullptr, pixShader.GetAddressOf()));

	GFX_ASSERT_HR_ONLY_INFO(comDeviceContext->PSSetShader(pixShader.Get(), nullptr, 0u));

	GFX_ASSERT_HR_ONLY_INFO(comDeviceContext->OMSetRenderTargets(1u, comTargetView.GetAddressOf(), nullptr));



	UINT stride = sizeof vertex;
	UINT offset = 0u;
	// input-assample buffer
	comDeviceContext->IASetVertexBuffers(0, 1, comBuffer.GetAddressOf(), &stride, &offset);

	// set topplogy
	comDeviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

	D3D11_VIEWPORT vp;
	vp.Width = 800;
	vp.Height = 600;
	vp.MinDepth = 0;
	vp.MaxDepth = 1;
	vp.TopLeftX = 0;
	vp.TopLeftY = 0;
	comDeviceContext->RSSetViewports(1u, &vp);

	GFX_ASSERT_HR_ONLY_INFO(comDeviceContext->Draw(std::size(vertices), 0u));


}

Graphics::~Graphics() noexcept
{
}

#include "DxgiInfoManager.h"
#include "LS3DException.h"
#include <memory>

#pragma comment(lib, "dxguid.lib")

DxgiInfo::DxgiInfo()
{
	//using DXGIGetDebugInterface = (HRESULT WINAPI * ) (REFIID, void**);
	typedef HRESULT(WINAPI* DXGIGetDebugInterface) (REFIID, void**);
	const auto hDxgiDebug = LoadLibraryEx("dxgidebug.dll", nullptr, LOAD_LIBRARY_SEARCH_SYSTEM32);
	WIN_ASSERT_NULL(hDxgiDebug);
	const auto dxgiGetInfoInterface = reinterpret_cast<DXGIGetDebugInterface>((reinterpret_cast<void*> (GetProcAddress(hDxgiDebug, "DXGIGetDebugInterface"))));
	WIN_ASSERT_NULL(dxgiGetInfoInterface);
	GFX_ASSERT_HR_NO_INFO(dxgiGetInfoInterface(__uuidof(IDXGIInfoQueue), (void**)&pIdxgiInfoQueue));
}

DxgiInfo::~DxgiInfo()
{
	if (pIdxgiInfoQueue != nullptr)
		pIdxgiInfoQueue->Release();
}

bool DxgiInfo::IsEmpty() const noexcept
{
	std::vector<std::string> vectorMessage;
	auto end = pIdxgiInfoQueue->GetNumStoredMessages(DXGI_DEBUG_ALL);
	return end == next;
}

void DxgiInfo::Set() noexcept
{
	next = pIdxgiInfoQueue->GetNumStoredMessages(DXGI_DEBUG_ALL);
}

std::vector<std::string> DxgiInfo::GetMesage() const noexcept
{
	std::vector<std::string> vectorMessage;
	auto end = pIdxgiInfoQueue->GetNumStoredMessages(DXGI_DEBUG_ALL);
	
	for (auto i = next; i < end; i++)
	{
		SIZE_T messageLength;
		pIdxgiInfoQueue->GetMessage(DXGI_DEBUG_ALL, i, nullptr, &messageLength);
		auto bytes = std::make_unique<byte[]>(messageLength);  // 用這個方式創建一個連續的內存
		auto pMessage = reinterpret_cast<DXGI_INFO_QUEUE_MESSAGE*>(bytes.get());
		pIdxgiInfoQueue->GetMessage(DXGI_DEBUG_ALL, i, pMessage, &messageLength);
		vectorMessage.emplace_back(pMessage->pDescription);
	}
	return vectorMessage;
}

std::string DxgiInfo::GetStringMesage() const noexcept
{
	std::vector<std::string> message = this->GetMesage();
	std::string info;
	for (auto& m : message)
	{
		info += m;
		info.push_back('\n');
	}
	return info;
}



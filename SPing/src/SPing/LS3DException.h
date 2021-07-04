#pragma once
#include <exception>
#include <string>
#include <Windows.h>
#include "DxgiInfoManager.h"

class LS3DException : public std::exception
{
public:
	LS3DException(int line, const char* file) noexcept;
	const char* what() const noexcept override;
	virtual const char* GetType() const noexcept;
	int GetLine() const noexcept;
	const std::string& GetFile() const noexcept;
	std::string GetOriginString() const noexcept;

private:
	int line;
	std::string file;
protected:
	mutable std::string whatBuffer;  // 因为在 what() const 里面被修改了，这里显示声明为mutable
};


class HrException : public LS3DException
{
public:
	HrException(int line, const char* file, HRESULT hr) noexcept;
	virtual const char* what() const noexcept override;
	HRESULT GetErrorCode() const noexcept;
	std::string GetErrorString() const noexcept;
private:
	HRESULT hr;
};


class WinException : public HrException
{
	using HrException::HrException;
	const char* GetType() const noexcept override;
};

class GfxException : public HrException
{
public:
	using HrException::HrException;
	GfxException(int line, const char* file, std::string message) noexcept;
	virtual const char* what() const noexcept override;
	const char* GetType() const noexcept override;
};


#define WIN_EXCEPT(hr) HrException(__LINE__, __FILE__, hr)
#define WIN_LAST_EXCEPT(hr) HrException(__LINE__, __FILE__, GetLastError())

#define WIN_ASSERT_BOOL(x) if (x == 0) throw WinException(__LINE__, __FILE__, GetLastError());
#define WIN_ASSERT_HR(hr) if (FAILED(hr)) throw WinException(__LINE__, __FILE__, hr);
#define WIN_ASSERT_NULL(N) if(N == nullptr) throw WinException(__LINE__, __FILE__, GetLastError());
#define GFX_ASSERT_HR(hr) DxgiInfoManager::Instance().Set(); if (FAILED(hr)) throw GfxException(__LINE__, __FILE__, hr);
#define GFX_ASSERT_HR_ONLY_INFO(call) DxgiInfoManager::Instance().Set();\
(call);\
if (!DxgiInfoManager::Instance().IsEmpty()) throw GfxException(__LINE__, __FILE__, DxgiInfoManager::Instance().GetStringMesage());

#define GFX_ASSERT_HR_NO_INFO(hr) if (FAILED(hr)) throw GfxException(__LINE__, __FILE__, hr);

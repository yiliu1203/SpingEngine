#include "LS3DException.h"
#include <iostream>
#include <sstream>

LS3DException::LS3DException(int line, const char* file) noexcept
	:line(line), file(file)
{
}

const char* LS3DException::what() const noexcept
{
	std::ostringstream oss;
	oss << "[line] : " << line << "," << "  [file] : " << file.c_str();
	whatBuffer = oss.str();
	return whatBuffer.c_str();
}

const char* LS3DException::GetType() const noexcept
{
	return "LS3D EXCEPTION";
}

int LS3DException::GetLine() const noexcept
{
	return line;
}

const std::string& LS3DException::GetFile() const noexcept
{
	return file;
}

std::string LS3DException::GetOriginString() const noexcept
{
	return whatBuffer;
}

HrException::HrException(int line, const char* file, HRESULT hr) noexcept
	: LS3DException(line, file), hr(hr)
{
}

const char* HrException::what() const noexcept
{
	std::ostringstream oss;
	oss << GetType() << std::endl;
	oss << "[file] " << GetFile() << "   [line] " << GetLine() << std::endl;
	oss << "[errorCode] " << ":" << GetErrorCode() << std::endl;
	oss << "[description] " << ":" << GetErrorString() << std::endl;

	whatBuffer = oss.str();
	return whatBuffer.c_str();
}

HRESULT HrException::GetErrorCode() const noexcept
{
	return hr;
}

std::string HrException::GetErrorString() const noexcept
{
	char* pMsgBuff = nullptr;
	auto len = FormatMessage(FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS,
		nullptr, hr, MAKELANGID(LANG_ENGLISH, SUBLANG_DEFAULT), reinterpret_cast<LPSTR>(&pMsgBuff), 0, nullptr);
	if (len == 0)
	{
		return "undefined error code";
	}
	std::string errorString = pMsgBuff;
	LocalFree(pMsgBuff);
	return errorString;
}

const char* WinException::GetType() const noexcept
{
	return "WINDOWS EXCEPTION";
}

GfxException::GfxException(int line, const char* file, std::string message) noexcept
	: GfxException(line, file, 0) 
{
	std::ostringstream oss;
	oss << GetType() << std::endl;
	oss << "[file] " << GetFile() << "   [line] " << GetLine() << std::endl;
	oss << "[errorCode] " << ":" << GetErrorCode() << std::endl;
	oss << "[dxgiinfo] " << ":" << message << std::endl;
	whatBuffer = oss.str();
}

const char* GfxException::what() const noexcept
{
	if (whatBuffer.empty())
	{
		std::ostringstream oss;
		oss << GetType() << std::endl;
		oss << "[file] " << GetFile() << "   [line] " << GetLine() << std::endl;
		oss << "[errorCode] " << ":" << GetErrorCode() << std::endl;
		oss << "[description] " << ":" << GetErrorString() << std::endl;
		oss << "[dxgiinfo] " << ":";
		auto infoVector = DxgiInfoManager::Instance().GetMesage();
		for (auto& info : infoVector)
			oss << info << std::endl;

		whatBuffer = oss.str();
	}
	
	return whatBuffer.c_str();
}

const char* GfxException::GetType() const noexcept
{
	return "Graphics Exception";
}

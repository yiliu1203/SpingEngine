#pragma once
#include <vector>
#include <string>
#include "LSWin.h"
#include "Singleton.h"

class DxgiInfo
{
public:
	friend class Singleton<DxgiInfo>;
	DxgiInfo(const DxgiInfo&) = delete;
	DxgiInfo& operator =(const DxgiInfo&) = delete;
	
	bool IsEmpty() const noexcept;
	void Set() noexcept;
	std::vector<std::string> GetMesage() const noexcept;
	std::string GetStringMesage() const noexcept;
	
private:
	DxgiInfo();
	~DxgiInfo();
	unsigned long long next = 0;
	struct IDXGIInfoQueue* pIdxgiInfoQueue;
};

using DxgiInfoManager = Singleton<DxgiInfo>;
#include "WindowsMsgMap.h"
#include <iomanip>

WindowsMsgMap::WindowsMsgMap()
{
}

std::string WindowsMsgMap::operator()(const UINT& msg, const WPARAM& wparam, const LPARAM& lparam)
{
	auto item = MSG_MAP.find(msg);
	std::ostringstream oss;

	if (item == MSG_MAP.end())
	{
		std::ostringstream tmp;
		tmp << "Unknow:" << std::hex << msg;
		oss << std::left << std::setw(30) << tmp.str() << std::right;
	}
	else
	{
		std::ostringstream tmp;
		tmp << item->second << ":" << std::hex << msg;
		oss << std::left << std::setw(30) << tmp.str() << std::right;
	}

	oss << std::right << " LP:0x" << std::setw(8) << std::hex << std::setfill('0') << lparam;
	oss << std::right << " WP:0x" << std::setw(8) << std::hex << std::setfill('0') << wparam << std::endl;
	return oss.str();
		
}

WindowsMsgMap::~WindowsMsgMap()
{
}


#include "Log.h"
#include "spdlog/sinks/stdout_color_sinks.h"

namespace SPing
{
	std::shared_ptr<spdlog::logger> Log::s_CoreLogger(nullptr);
	std::shared_ptr<spdlog::logger> Log::s_ClientLogger(nullptr);

	Log::Log()
	{
	}

	Log::~Log()
	{
	}

	void Log::Init()
	{
		spdlog::set_pattern("[%H:%M:%S] %^%l: %v %$ ");
		s_CoreLogger = spdlog::stdout_color_mt("SPing");
		s_CoreLogger->set_level(spdlog::level::trace);

		s_ClientLogger = spdlog::stdout_color_mt("APP");
		s_ClientLogger->set_level(spdlog::level::trace);
	}


}



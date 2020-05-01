#ifndef SP_LOG_H
#define SP_LOG_H

#include "Core.h"
#include "spdlog/spdlog.h"

namespace SPing
{

	class SP_API Log
	{
	public:
		Log();
		~Log();

		static void Init();
		inline static std::shared_ptr<spdlog::logger>& GetCoreLogger() { return s_CoreLogger; }
		inline static std::shared_ptr<spdlog::logger>& GetClientLogger() { return s_ClientLogger; }


	private:

		static std::shared_ptr<spdlog::logger> s_CoreLogger;
		static std::shared_ptr<spdlog::logger> s_ClientLogger;


	};

}


#define SP_CORE_ERROR(...)			::SPing::Log::GetCoreLogger()->error(__VA_ARGS__)
#define SP_CORE_WARN(...)			::SPing::Log::GetCoreLogger()->warn(__VA_ARGS__)
#define SP_CORE_TRACE(...)			::SPing::Log::GetCoreLogger()->trace(__VA_ARGS__)
#define SP_CORE_INFO(...)			::SPing::Log::GetCoreLogger()->info(__VA_ARGS__)


#define SP_ERROR(...)				::SPing::Log::GetClientLogger()->error(__VA_ARGS__)
#define SP_WARN(...)				::SPing::Log::GetClientLogger()->warn(__VA_ARGS__)
#define SP_TRACE(...)				::SPing::Log::GetClientLogger()->trace(__VA_ARGS__)
#define SP_INFO(...)				::SPing::Log::GetClientLogger()->info(__VA_ARGS__)

#endif

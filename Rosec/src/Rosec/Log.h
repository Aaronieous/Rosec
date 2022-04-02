#pragma once

#include "spdlog/spdlog.h"
#include "spdlog/fmt/ostr.h"

namespace Rosec {

	class ROSEC_API Log
	{
	public:
		static void Init();

		inline static std::shared_ptr<spdlog::logger>& GetCoreLogger() { return s_CoreLogger; }
		inline static std::shared_ptr<spdlog::logger>& GetClientLogger() { return s_ClientLogger; }

	private:
		static std::shared_ptr<spdlog::logger> s_CoreLogger;
		static std::shared_ptr<spdlog::logger> s_ClientLogger;
	};

}

#define RSC_CORE_CRITICAL(...)   ::Rosec::Log::GetCoreLogger()->critical(__VA_ARGS__)
#define RSC_CORE_ERROR(...)      ::Rosec::Log::GetCoreLogger()->error(__VA_ARGS__)
#define RSC_CORE_WARN(...)       ::Rosec::Log::GetCoreLogger()->warn(__VA_ARGS__)
#define RSC_CORE_INFO(...)       ::Rosec::Log::GetCoreLogger()->info(__VA_ARGS__)
#define RSC_CORE_TRACE(...)      ::Rosec::Log::GetCoreLogger()->trace(__VA_ARGS__)

#define RSC_CRITICAL(...) ::Rosec::Log::GetClientLogger()->critical(__VA_ARGS__)
#define RSC_ERROR(...)    ::Rosec::Log::GetClientLogger()->error(__VA_ARGS__)
#define RSC_WARN(...)     ::Rosec::Log::GetClientLogger()->warn(__VA_ARGS__)
#define RSC_INFO(...)     ::Rosec::Log::GetClientLogger()->info(__VA_ARGS__)
#define RSC_TRACE(...)    ::Rosec::Log::GetClientLogger()->trace(__VA_ARGS__)





#ifdef RSC_DIST
	#define RSC_CORE_CRITICAL(...)   
	#define RSC_CORE_ERROR(...)      
	#define RSC_CORE_WARN(...)       
	#define RSC_CORE_INFO(...)       
	#define RSC_CORE_TRACE(...)      
	
	#define RSC_CLIENT_CRITICAL(...) 
	#define RSC_CLIENT_ERROR(...)    
	#define RSC_CLIENT_WARN(...)     
	#define RSC_CLIENT_INFO(...)     
	#define RSC_CLIENT_TRACE(...)    
#endif
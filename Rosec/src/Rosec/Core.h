#pragma once

#ifdef RSC_PLATFORM_WINDOWS
	#ifdef RSC_BUILD_DLL
		#define ROSEC_API __declspec(dllexport)
	#else
		#define ROSEC_API __declspec(dllimport)
	#endif
#else
	#error Rosec only supported on windows!
#endif

#define BIT(x) (1 << x)

#ifdef RSC_DEBUG
	#define RSC_ASSERT(x, ...)       { if(!(x)) { RSC_CLIENT_ERROR("Assertion Failed: {0}", __VA_ARGS__); __debugbreak(); } }
	#define RSC_CORE_ASSERT(x, ...)  { if(!(x)) { RSC_CORE_ERROR("Assertion Failed: {0}", __VA_ARGS__); __debugbreak(); } }
#else
	#define RSC_ASSERT(x, ...)       x
	#define RSC_CORE_ASSERT(x, ...)  x
#endif

#ifndef BIND_EVENT_FN
	#define RSC_BIND_FN(x) std::bind(&x, this, std::placeholders::_1)
#endif
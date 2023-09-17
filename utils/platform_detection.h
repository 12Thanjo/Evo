#pragma once


//////////////////////////////////////////////////////////////////////
// compilers

#ifdef _MSC_VER
	#define EVO_COMPILER_MSVC
#elif __clang__
	#define EVO_COMPILER_CLANG
#elif __GNUG__
	#define EVO_COMPILER_GCC
#else
	#error Unknown or unsupported compiler
#endif


//////////////////////////////////////////////////////////////////////
// OS


#if defined(WIN32) || defined(_WIN32) || defined(__WIN32__)
	#define EVO_PLATFORM_WINDOWS
	
	#ifndef _WIN32
		#error "64-bit is required on Windows"
	#endif

#elif defined(__linux__) || defined(__gnu_linux__)
	#define EVO_PLATFORM_LINUX

	#if defined(__ANDROID__)
		#define EVO_PLATFORM_ANDROID
	#endif

#elif defined(__unix__)
	#define EVO_PLATFORM_UNIX

#elif __APPLE__

	#define EVO_PLATFROM_APPLE

	#include <TargetConditionals.h>
	
	#if TARGET_IPHONE_SIMULATOR
		#define EVO_PLATFORM_IOS
		#define EVO_PLATFORM_IOS_SIMULATOR

	#elif TARGET_OS_IPHONE
		#define EVO_PLATFORM_IOS

	#elif TARGET_OS_MAC
		#define EVO_PLATFORM_MAC
	
	#else
		#error "Unknown Apple platform"
	#endif

#else
	#error "Unknown platform"

#endif




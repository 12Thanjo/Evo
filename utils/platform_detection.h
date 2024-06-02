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
	#define EVO_COMPILER_UNKNOWN
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

	#endif

#else
	#define EVO_PLATFORM_UNKNOWN
#endif



//////////////////////////////////////////////////////////////////////
// architecture 

#if defined(i386)          || defined(__i386__)  || defined(__i386)   || \
    defined(__i486__)      || defined(__i586__)  || defined(__i686__) || \
    defined(_M_IX86)       || defined(_X86_)     || defined(__I86__)  || \
    defined(__THW_INTEL__) || defined(__INTEL__)

    #define EVO_ARCH_X86_32

#elif defined(__x86_64)  || defined(__x86_64__) || \
      defined(__amd64__) || defined(__amd64)    || \
      defined(_M_X64)

    #define EVO_ARCH_X86_64

#elif defined(__ARM_ARCH)          || defined(_M_ARM)            || \
      defined(__TARGET_ARCH_THUMB) || defined(__TARGET_ARCH_ARM) || \
      defined(__arm__)             || defined(__arm64)           || defined(__thumb__)     || \
      defined(__ARM_ARCH_4T__)     || defined(__ARM_ARCH_4__)    || \
      defined(__ARM_ARCH_5TE__)    || defined(__ARM_ARCH_5TEJ__) || \
      defined(__ARM_ARCH_6KZ__)    || defined(__ARM_ARCH_6T2__)  || \
      defined(__ARM_ARCH_6K__)     || defined(__ARM_ARCH_6Z__)   || \
      defined(__ARM_ARCH_7R__)     || defined(__ARM_ARCH_7M__)   || \
      defined(__ARM_ARCH_7__)      || defined(__ARM_ARCH_7A__)

    #define EVO_ARCH_ARM

#elif defined(_M_ARM64) || defined(__aarch64__) || defined(__AARCH64EL__)

    #define EVO_ARCH_ARM64


#elif defined(__riscv)
    #define EVO_ARCH_RISCV

#else
	#define EVO_ARCH_UNKNOWN
#endif








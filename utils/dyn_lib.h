#pragma once

#if defined(EVO_IGNORE_DYN_LIB)
	#define EVO_DYN_LIB
	#define EVO_DYN_LIB_HIDDEN
#else
	#if defined(EVO_PLATFORM_WINDOWS)
		#if defined(WIN_EXPORT)
			#if defined(EVO_COMPILER_CLANG) || defined(EVO_COMPILER_GCC)
				#define EVO_DYN_LIB __attribute__ ((dllexport))
			#elif defined(EVO_COMPILER_MSVC)
				#define EVO_DYN_LIB __declspec(dllexport)
	      	#else
	      		#define EVO_DYN_LIB
			#endif
		#else
			#if defined(EVO_COMPILER_CLANG) || defined(EVO_COMPILER_GCC)
				#define EVO_DYN_LIB __attribute__ ((dllimport))
			#elif defined(EVO_COMPILER_MSVC)
				#define EVO_DYN_LIB __declspec(dllimport)
	      	#else
	      		#define EVO_DYN_LIB
			#endif
		#endif
		#define EVO_DYN_LIB_HIDDEN
	#else
	   	#if defined(EVO_COMPILER_MSVC) || defined(EVO_COMPILER_CLANG) || defined(EVO_COMPILER_GCC)
			#define EVO_DYN_LIB __attribute__ ((visibility ("default")))
			#define EVO_DYN_LIB_HIDDEN  __attribute__ ((visibility ("hidden")))
	    #else
			#define EVO_DYN_LIB
			#define EVO_DYN_LIB_HIDDEN
	    #endif
	#endif
	
#endif
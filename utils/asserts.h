#pragma once


//////////////////////////////////////////////////////////////////////
// breakpoints

#ifdef EVO_COMPILER_MSVC
	#include <intrin.h>
	#define EVO_BREAK() __debugbreak()
#else
	#define EVO_BREAK() __builtin_trap()
#endif


//////////////////////////////////////////////////////////////////////
// asserts


#define EVO_ASSERT(conditional) \
	if(!(conditional)){ \
		EVO_BREAK(); \
	}


#ifdef EVO_CONFIG_DEBUG
	#define EVO_DEBUG_ASSERT(conditional) \
		if(!(conditional)){ \
			EVO_BREAK(); \
		}
#else
	#define EVO_DEBUG_ASSERT(conditional)
		
#endif

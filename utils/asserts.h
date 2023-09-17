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




namespace evo{

	//////////////////////////////////////////////////////////////////////
	// breakpoints

	inline auto breakpoint() noexcept -> void {
		#if defined(EVO_CONFIG_DEBUG)
			#if defined(EVO_COMPILER_MSVC)
				__debugbreak();
			#else
				__builtin_trap();
			#endif
		#else
			std::exit(EXIT_FAILURE);
		#endif
	};




	//////////////////////////////////////////////////////////////////////
	// asserts


	inline auto assert(bool conditional) noexcept -> void {
		if(conditional == false){
			breakpoint();
		}
	};



	inline auto debugAssert(bool conditional) noexcept -> void {
		#if defined(PH_CONFIG_DEBUG)
			evo::assert(conditional);
		#endif
	};


};



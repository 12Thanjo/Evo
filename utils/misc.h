#pragma once

#include "../defines.h"
#include <vector>


//////////////////////////////////////////////////////////////////////
//                                                                  //
// misc. functions                                                  //
//                                                                  //
//////////////////////////////////////////////////////////////////////




namespace evo{

	template<typename T>
	inline auto vector_dealloc(std::vector<T>& vec) noexcept -> void {
		vec.clear();
		vec.shrink_to_fit();
	};


	[[noreturn]]
	constexpr auto unreachable() noexcept -> void {
		#if defined(EVO_COMPILER_MSVC)
			__assume(false);
		#else
			__builtin_unreachable();
		#endif
	};

	
};
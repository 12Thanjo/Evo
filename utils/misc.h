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


	
	EVO_NORETURN constexpr auto unreachable() noexcept -> void {
		#if defined(EVO_COMPILER_MSVC)
			__assume(false);
		#else
			__builtin_unreachable();
		#endif
	};



	// version of C++23's std::to_underlying
	template<class Enum>
	EVO_NODISCARD constexpr auto to_underlying(Enum e) noexcept -> std::underlying_type_t<Enum> {
		return static_cast<std::underlying_type_t<Enum>>(e);
	};

	
};
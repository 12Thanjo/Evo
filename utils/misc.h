#pragma once

#include "defines.h"
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

	
};
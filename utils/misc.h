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




	constexpr auto hashCombine(size_t lhs, size_t rhs) noexcept -> size_t {
		return lhs ^ (rhs << 1);
	};

	constexpr auto hashCombine(std::initializer_list<size_t> list) noexcept -> size_t {
		size_t output = *list.begin();

		bool left = true;
		for(size_t i = 1; i < list.size(); i+=1){
			if(left){
				output ^= list.begin()[i] << 1;
			}else{
				output ^= list.begin()[i] >> 1;
			}

			left = !left;
		}

		return output;
	};

	
};
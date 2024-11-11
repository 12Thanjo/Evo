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




	EVO_NODISCARD constexpr auto hashCombine(size_t lhs, size_t rhs) noexcept -> size_t {
		return lhs ^ (rhs << 1);
	};

	EVO_NODISCARD constexpr auto hashCombine(std::initializer_list<size_t> list) noexcept -> size_t {
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


	///////////////////////////////////
	// bitCast

	template<class TO, class FROM>
	EVO_NODISCARD constexpr auto bitCast(const FROM& from) -> const TO& {
		static_assert(sizeof(FROM) == sizeof(TO), "Cannot bitcast to type of different size");
		static_assert(std::is_trivially_destructible<FROM>(), "Cannot bitcast from a non-trivially-destructible type");

		return *(const TO*)&from;
	}


	template<class TO, class FROM>
	EVO_NODISCARD constexpr auto bitCast(FROM& from) -> TO& {
		static_assert(sizeof(FROM) == sizeof(TO), "Cannot bitcast to type of different size");
		static_assert(std::is_trivially_destructible<FROM>(), "Cannot bitcast from a non-trivially-destructible type");

		return *(TO*)&from;
	}


	template<class TO, class FROM>
	EVO_NODISCARD constexpr auto unsafeBitCast(const FROM& from) -> const TO& {
		static_assert(sizeof(FROM) == sizeof(TO), "Cannot unsafe-bitcast to type of different size");

		return *(const TO*)&from;
	}


	template<class TO, class FROM>
	EVO_NODISCARD constexpr auto unsafeBitCast(FROM& from) -> TO& {
		static_assert(sizeof(FROM) == sizeof(TO), "Cannot unsafe-bitcast to type of different size");

		return *(TO*)&from;
	}
	
};
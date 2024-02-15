#pragma once

#include <stdint.h>

namespace evo{

	using i8 = int8_t;
	using i16 = int16_t;
	using i32 = int32_t;
	using i64 = int64_t;

	using ui8  = uint8_t;
	using ui16 = uint16_t;
	using ui32 = uint32_t;
	using ui64 = uint64_t;


	using f32 = float;
	using f64 = double;
	using f128 = long double;


	static_assert(sizeof(i8) == 1, "Expected i8 to be 1 byte - " __FILE__);
	static_assert(sizeof(i16) == 2, "Expected i16 to be 2 bytes - " __FILE__);
	static_assert(sizeof(i32) == 4, "Expected i32 to be 4 bytes - " __FILE__);
	static_assert(sizeof(i64) == 8, "Expected i64 to be 8 bytes - " __FILE__);

	static_assert(sizeof(ui8) == 1, "Expected ui8 to be 1 byte - " __FILE__);
	static_assert(sizeof(ui16) == 2, "Expected ui16 to be 2 bytes - " __FILE__);
	static_assert(sizeof(ui32) == 4, "Expected ui32 to be 4 bytes - " __FILE__);
	static_assert(sizeof(ui64) == 8, "Expected ui64 to be 8 bytes - " __FILE__);


	static_assert(sizeof(f32) == 4, "Expected f32 to be 4 bytes - " __FILE__);
	static_assert(sizeof(f64) == 8, "Expected f64 to be 8 bytes - " __FILE__);	
	static_assert(sizeof(f128) == 16, "Expected f64 to be 16 bytes - " __FILE__);


	using byte = ui8;
	using uint = unsigned int;
};



#if defined(EVO_GLOBAL_NUMERIC_TYPES)
	using evo::i8;
	using evo::i16;
	using evo::i32;
	using evo::i64;
	using evo::ui8;
	using evo::ui16;
	using evo::ui32;
	using evo::ui64;
	using evo::f32;
	using evo::f64;
	using evo::byte;
	using evo::uint;
#endif



namespace evo{
	using float32_t = evo::f32;
	using float64_t = evo::f64;
	using float128_t = evo::f128;
};


#if ((defined(_MSVC_LANG) && _MSVC_LANG >= 202101L) || __cplusplus >= 202101L)
	using evo::float32_t;
	using evo::float64_t;
	using evo::float128_t;
#else
	#include <stdfloat>
#endif




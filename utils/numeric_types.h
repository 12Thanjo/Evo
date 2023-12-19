#pragma once



namespace evo{

	using i8 = signed char;
	using i16 = signed short;
	using i32 = signed long;
	using i64 = signed long long;

	using ui8  = unsigned char;
	using ui16 = unsigned short;
	using ui32 = unsigned long;
	using ui64 = unsigned long long;


	using f32 = float;
	using f64 = double;
	using f128 = long double;


	static_assert(sizeof(i8) == 1, "Expected i8 (signed char) to be 1 byte - " __FILE__);
	static_assert(sizeof(i16) == 2, "Expected i16 (signed short) to be 2 bytes - " __FILE__);
	static_assert(sizeof(i32) == 4, "Expected i32 (signed long) to be 4 bytes - " __FILE__);
	static_assert(sizeof(i64) == 8, "Expected i64 (signed long long) to be 8 bytes - " __FILE__);

	static_assert(sizeof(ui8) == 1, "Expected ui8 (unsigned char) to be 1 byte - " __FILE__);
	static_assert(sizeof(ui16) == 2, "Expected ui16 (unsigned short) to be 2 bytes - " __FILE__);
	static_assert(sizeof(ui32) == 4, "Expected ui32 (unsigned long) to be 4 bytes - " __FILE__);
	static_assert(sizeof(ui64) == 8, "Expected ui64 (unsigned long long) to be 8 bytes - " __FILE__);


	static_assert(sizeof(f32) == 4, "Expected f32 (float) to be 4 bytes - " __FILE__);
	static_assert(sizeof(f64) == 8, "Expected f64 (float) to be 8 bytes - " __FILE__);	


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

using evo::float32_t;
using evo::float64_t;
using evo::float128_t;

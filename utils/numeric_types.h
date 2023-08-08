#pragma once



#ifndef EVO_GLOBAL_NUMERIC_TYPES
namespace evo{
#endif
	
	using i8 = signed char;
	using i16 = signed short;
	using i32 = signed int;
	using i64 = signed long long;

	using ui8  = unsigned char;
	using ui16 = unsigned short;
	using ui32 = unsigned int;
	using ui64 = unsigned long long;


	using f32 = float;
	using f64 = double;



	static_assert(sizeof(i8) == 1, "Expected i8 (signed char) to be 1 byte - ./engine/src/defines.h");
	static_assert(sizeof(i16) == 2, "Expected i16 (signed short) to be 2 bytes - ./engine/src/defines.h");
	static_assert(sizeof(i32) == 4, "Expected i32 (signed int) to be 4 bytes - ./engine/src/defines.h");
	static_assert(sizeof(i64) == 8, "Expected i64 (signed long long) to be 8 bytes - ./engine/src/defines.h");

	static_assert(sizeof(ui8) == 1, "Expected ui8 (unsigned char) to be 1 byte - ./engine/src/defines.h");
	static_assert(sizeof(ui16) == 2, "Expected ui16 (unsigned short) to be 2 bytes - ./engine/src/defines.h");
	static_assert(sizeof(ui32) == 4, "Expected ui32 (unsigned int) to be 4 bytes - ./engine/src/defines.h");
	static_assert(sizeof(ui64) == 8, "Expected ui64 (unsigned long long) to be 8 bytes - ./engine/src/defines.h");


	static_assert(sizeof(f32) == 4, "Expected f32 (float) to be 4 bytes - ./engine/src/defines.h");
	static_assert(sizeof(f64) == 8, "Expected f64 (float) to be 8 bytes - ./engine/src/defines.h");	


	using byte = ui8;


#ifndef EVO_GLOBAL_NUMERIC_TYPES
};
#endif
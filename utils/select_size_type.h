#pragma once


namespace evo{

	// adapted from: https://stackoverflow.com/a/7039269



	//////////////////////////////////////////////////////////////////////
	// impl

	template<size_t Capacity>
	struct CapacityRequiredSize {
	    enum {
	    	bits = Capacity <= std::numeric_limits<ui8>::max()  ? (sizeof(ui8)  * 8) :
	        	   Capacity <= std::numeric_limits<ui16>::max() ? (sizeof(ui16) * 8) :
	        	   Capacity <= std::numeric_limits<ui32>::max() ? (sizeof(ui32) * 8) :
	        	   Capacity <= std::numeric_limits<ui64>::max() ? (sizeof(ui64) * 8) :
	        	   0,
	    };
	};

	template<size_t Bits>
	struct BitsRequiredSize {
	    enum {
	    	bits = Bits <= (sizeof(ui8)  * 8) ? (sizeof(ui8)  * 8) :
	        	   Bits <= (sizeof(ui16) * 8) ? (sizeof(ui16) * 8) :
	        	   Bits <= (sizeof(ui32) * 8) ? (sizeof(ui32) * 8) :
	        	   Bits <= (sizeof(ui64) * 8) ? (sizeof(ui64) * 8) :
	        	   0,
	    };
	};



	template<unsigned BITS> struct SelectType;
	template<> struct SelectType<sizeof(ui8) * 8>  { using type = ui8;  };
	template<> struct SelectType<sizeof(ui16) * 8> { using type = ui16; };
	template<> struct SelectType<sizeof(ui32) * 8> { using type = ui32; };
	template<> struct SelectType<sizeof(ui64) * 8> { using type = ui64; };




	//////////////////////////////////////////////////////////////////////
	// API

	template<size_t CAPACITY>
	struct CapacityType : SelectType<CapacityRequiredSize<CAPACITY>::bits> {};


	template<size_t BITS>
	struct BitsSize : SelectType<BitsRequiredSize<BITS>::bits> {};

};
#pragma once

#include "defines.h"
#include <optional>


namespace evo{

	EVO_NODISCARD constexpr auto stringSize(const char* str, size_t max_length = 100) noexcept -> size_t {
		for(size_t i = 0; i < max_length; i+=1){
			if(str[i] == '\0'){
				return i;
			}
		}

		return max_length;
	};



	// optional is nullopt if exceeds the max string length
	EVO_NODISCARD constexpr auto stringsEqual(const char* str1, const char* str2, size_t max_length = 100) noexcept -> std::optional<bool> {
		for(size_t i = 0; i < max_length; i+=1){
			if(str1[i] == str2[i]){
				if(str1[i] == '\0'){
					return true;
				}

				continue;
			}

			return false;
		}

		return std::nullopt;
	};






	EVO_NODISCARD constexpr auto isLowerLetter(char character) noexcept -> bool {
		switch(character){
			case 'a': case 'b':
			case 'c': case 'd':
			case 'e': case 'f':
			case 'g': case 'h':
			case 'i': case 'j':
			case 'k': case 'l':
			case 'm': case 'n':
			case 'o': case 'p':
			case 'q': case 'r':
			case 's': case 't':
			case 'u': case 'v':
			case 'w': case 'x':
			case 'y': case 'z':
				return true;
		};

		return false;
	};


	EVO_NODISCARD constexpr auto isUpperLetter(char character) noexcept -> bool {
		switch(character){
			case 'A': case 'B':
			case 'C': case 'D':
			case 'E': case 'F':
			case 'G': case 'H':
			case 'I': case 'J':
			case 'K': case 'L':
			case 'M': case 'N':
			case 'O': case 'P':
			case 'Q': case 'R':
			case 'S': case 'T':
			case 'U': case 'V':
			case 'W': case 'X':
			case 'Y': case 'Z':
				return true;
		};

		return false;
	};

	EVO_NODISCARD constexpr auto isLetter(char character) noexcept -> bool {
		return isLowerLetter(character) || isUpperLetter(character);
	};


	EVO_NODISCARD constexpr auto isNumber(char character) noexcept -> bool {
		switch(character){
			case '0':
			case '1':
			case '2':
			case '3':
			case '4':
			case '5':
			case '6':
			case '7':
			case '8':
			case '9':
				return true;
		};

		return false;
	};


	EVO_NODISCARD constexpr auto isAlphaNumberic(char character) noexcept -> bool {
		return isLetter(character) || isNumber(character);
	};


	EVO_NODISCARD constexpr auto isWhitespace(char character) noexcept -> bool {
		switch(character){
			case ' ':
			case '\n':
			case '\r':
			case '\t':
				return true;
		};

		return false;
	};



	
};
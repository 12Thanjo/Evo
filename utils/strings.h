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



	
};
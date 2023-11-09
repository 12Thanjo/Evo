#pragma once

#include "../defines.h"
#include <string>
#include <array>


namespace evo{
	
	class CStrProxy{
		public:
			CStrProxy() = default;
			~CStrProxy() = default;

			EVO_NODISCARD constexpr CStrProxy(const std::string& str) noexcept : using_ptr(true) { this->str_data.ptr = str.c_str();         };
			EVO_NODISCARD constexpr CStrProxy(const char* str) noexcept : using_ptr(true)        { this->str_data.ptr = str;                 };
			EVO_NODISCARD constexpr CStrProxy(char character) noexcept : using_ptr(false)        { this->str_data.array = {character, '\0'}; };

			template<size_t CAPACITY>
			EVO_NODISCARD constexpr CStrProxy(const StaticString<CAPACITY>& str) noexcept : using_ptr(true) { this->str_data.ptr = str.c_str(); };




			EVO_NODISCARD constexpr auto data() const noexcept -> const char* {
				if(this->using_ptr){
					return str_data.ptr;
				}else{
					return str_data.array.data();
				}
			};


		private:
			bool using_ptr;

			union {
				const char* ptr;
				std::array<char, 2> array;
			} str_data;
	};

};




template<>
struct std::hash<evo::CStrProxy>{
	auto operator()(const evo::CStrProxy& string) const noexcept -> size_t {
		return std::hash<const char*>{}(string.data());
	};
};


template<>
struct std::formatter<evo::CStrProxy>{
    constexpr auto parse(std::format_parse_context& ctx) const -> auto {
        return ctx.begin();
    }

    auto format(const evo::CStrProxy& string, std::format_context& ctx) const -> auto {
        return std::format_to(ctx.out(), "{}", string.data());
    }
};





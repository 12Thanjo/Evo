#pragma once


#include "../defines.h"



namespace evo{

	template<class... Ts>
	class Variant : public std::variant<Ts...> {
		public:
			
			EVO_NODISCARD auto getNative() noexcept -> std::variant<Ts...>& {
				return static_cast<std::variant<Ts...>&>(*this);
			};

			EVO_NODISCARD auto getNative() const noexcept -> const std::variant<Ts...>& {
				return static_cast<const std::variant<Ts...>&>(*this);
			};


			template<class T>
			EVO_NODISCARD constexpr auto is() const noexcept -> bool {
				return std::holds_alternative<T>(this->getNative());
			};



			template<class T>
			EVO_NODISCARD constexpr auto as() noexcept -> T& {
				debugAssert(this->is<T>(), "Variant is not of this type");
				return std::get<T>(this->getNative());
			};


			template<class T>
			EVO_NODISCARD constexpr auto as() const noexcept -> const T& {
				debugAssert(this->is<T>(), "Variant is not of this type");
				return std::get<T>(this->getNative());
			};
	
	};


};
#pragma once


#include "../defines.h"

#include <variant>

namespace evo{

	template<class... Ts>
	class Variant : public std::variant<Ts...> {
		public:
			using std::variant<Ts...>::variant;

			EVO_NODISCARD constexpr auto getNative() const& noexcept -> const std::variant<Ts...>& {
				return static_cast<const std::variant<Ts...>&>(*this);
			};
			
			EVO_NODISCARD constexpr auto getNative() & noexcept -> std::variant<Ts...>& {
				return static_cast<std::variant<Ts...>&>(*this);
			};

			EVO_NODISCARD constexpr auto getNative() && noexcept -> std::variant<Ts...>&& {
				return std::move(static_cast<std::variant<Ts...>&>(*this));
			};



			template<class T>
			EVO_NODISCARD constexpr auto is() const noexcept -> bool {
				return std::holds_alternative<T>(this->getNative());
			};




			template<class T>
			EVO_NODISCARD constexpr auto as() const& noexcept -> const T& {
				debugAssert(this->is<T>(), "Variant is not of this type");
				return std::get<T>(this->getNative());
			};

			template<class T>
			EVO_NODISCARD constexpr auto as() & noexcept -> T& {
				debugAssert(this->is<T>(), "Variant is not of this type");
				return std::get<T>(this->getNative());
			};


			template<class T>
			EVO_NODISCARD constexpr auto as() && noexcept -> T&& {
				debugAssert(this->is<T>(), "Variant is not of this type");
				return std::move(std::get<T>(this->getNative()));
			};



			constexpr auto visit(auto callable) noexcept {
				return std::visit(callable, this->getNative());
			};

			constexpr auto visit(auto callable) const noexcept {
				return std::visit(callable, this->getNative());
			};
	
	};


};


template<class... Ts>
struct std::hash<evo::Variant<Ts...>>{
	auto operator()(const evo::Variant<Ts...>& variant) const noexcept -> size_t {
		return std::hash<std::variant<Ts...>>{}(variant.getNative());
	};
};
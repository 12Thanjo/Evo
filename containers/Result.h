#pragma once


#include "../defines.h"



namespace evo{

	struct ResultError_t{};
	inline constexpr ResultError_t resultError{};

	template<class T>
	class Result{
		public:
			///////////////////////////////////
			// constructors / destructors

			EVO_NODISCARD constexpr Result(const T& value) noexcept : val(value) {};
			EVO_NODISCARD constexpr Result(T&& value) noexcept : val(std::move(value)) {};
			EVO_NODISCARD constexpr Result(ResultError_t) noexcept : val(std::nullopt) {};
			~Result() = default;

			EVO_NODISCARD static constexpr auto error() noexcept -> Result { return Result(); };


			///////////////////////////////////
			// checking

			EVO_NODISCARD inline constexpr auto isSuccess() const noexcept -> bool { return this->val.has_value(); };
			EVO_NODISCARD inline constexpr auto isError() const noexcept -> bool { return !this->isSuccess(); };


			///////////////////////////////////
			// getting value

			EVO_NODISCARD inline constexpr auto value() const noexcept -> const T& {
				EVO_DEBUG_ASSERT(this->isSuccess());
				return *this->val;
			};

			EVO_NODISCARD inline constexpr auto value() noexcept -> const T& {
				EVO_DEBUG_ASSERT(this->isSuccess());
				return *this->val;
			};

	
		private:
			std::optional<T> val;
	};


};
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

			EVO_NODISCARD constexpr Result(const Result<T>& rhs) noexcept : val(rhs.val) {};
			EVO_NODISCARD constexpr auto operator=(const Result<T>& rhs) noexcept {
				this->val = rhs.val;
			};

			EVO_NODISCARD constexpr Result(Result<T>&& rhs) noexcept : val(std::move(rhs.val)) {};




			///////////////////////////////////
			// checking

			EVO_NODISCARD constexpr auto isSuccess() const noexcept -> bool { return this->val.has_value(); };
			EVO_NODISCARD constexpr auto isError() const noexcept -> bool { return !this->isSuccess(); };


			///////////////////////////////////
			// getting value

			EVO_NODISCARD constexpr auto value() const noexcept -> const T& {
				EVO_DEBUG_ASSERT(this->isSuccess());
				return *this->val;
			};

			EVO_NODISCARD constexpr auto value() noexcept -> T& {
				EVO_DEBUG_ASSERT(this->isSuccess());
				return *this->val;
			};

			EVO_NODISCARD static constexpr auto error() noexcept -> Result { return Result(); };

	
		private:
			std::optional<T> val;
	};


};
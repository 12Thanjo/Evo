#pragma once


#include "../defines.h"



namespace evo{

	struct ResultError_t{};
	inline constexpr ResultError_t resultError{};

	template<class T = void>
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

			EVO_NODISCARD constexpr auto value() const& noexcept -> const T& {
				EVO_DEBUG_ASSERT(this->isSuccess());
				return *this->val;
			};

			EVO_NODISCARD constexpr auto value() & noexcept -> T& {
				EVO_DEBUG_ASSERT(this->isSuccess());
				return *this->val;
			};


			EVO_NODISCARD constexpr auto value() && noexcept -> T&& {
				EVO_DEBUG_ASSERT(this->isSuccess());
				return std::move(*this->val);
			};


			EVO_NODISCARD static constexpr auto error() noexcept -> Result<T> { return Result<T>(resultError); };


		private:
			std::optional<T> val;
	};


	template<>
	class Result<void>{
		public:
			///////////////////////////////////
			// constructors / destructors

			EVO_NODISCARD constexpr Result() : is_error(false) {}

			EVO_NODISCARD constexpr Result(ResultError_t) noexcept : is_error(true) {};
			~Result() = default;

			EVO_NODISCARD constexpr Result(const Result<void>& rhs) noexcept : is_error(rhs.is_error) {}
			EVO_NODISCARD constexpr auto operator=(const Result<void>& rhs) noexcept {
				this->is_error = rhs.is_error;
			};

			EVO_NODISCARD constexpr Result(Result<void>&& rhs) noexcept : is_error(std::move(rhs.is_error)) {};


			EVO_NODISCARD static constexpr auto fromBool(bool is_success) noexcept -> Result {
				return Result(!is_success);
			}


			///////////////////////////////////
			// checking

			EVO_NODISCARD constexpr auto isSuccess() const noexcept -> bool { return !this->is_error; };
			EVO_NODISCARD constexpr auto isError() const noexcept -> bool { return this->is_error; };


			///////////////////////////////////
			// getting value

			EVO_NODISCARD static constexpr auto error() noexcept -> Result<void> { return Result<void>(resultError); };


		private:
			EVO_NODISCARD constexpr Result(bool _is_error) : is_error(_is_error) {}
	
		private:
			bool is_error;
	};


};
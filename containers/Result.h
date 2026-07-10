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

			[[nodiscard]] constexpr Result(const T& value) noexcept : val(value) {};
			[[nodiscard]] constexpr Result(T&& value) noexcept : val(std::move(value)) {};
			[[nodiscard]] constexpr Result(ResultError_t) noexcept : val(std::nullopt) {};
			~Result() = default;

			[[nodiscard]] constexpr Result(const Result<T>& rhs) noexcept : val(rhs.val) {};
			constexpr auto operator=(const Result<T>& rhs) noexcept -> Result<T> {
				this->val = rhs.val;
				return *this;
			};

			[[nodiscard]] constexpr Result(Result<T>&& rhs) noexcept : val(std::move(rhs.val)) {};
			constexpr auto operator=(Result<T>&& rhs) noexcept -> Result<T> {
				this->val = std::move(rhs.val);
				return *this;
			};


			[[nodiscard]] constexpr auto operator=(ResultError_t) noexcept -> Result<T>& {
				this->val.reset();
				return *this;
			};




			///////////////////////////////////
			// checking

			[[nodiscard]] constexpr auto isSuccess() const noexcept -> bool { return this->val.has_value(); };
			[[nodiscard]] constexpr auto isError() const noexcept -> bool { return !this->isSuccess(); };


			///////////////////////////////////
			// getting value

			[[nodiscard]] constexpr auto value() const& noexcept -> const T& {
				EVO_DEBUG_ASSERT(this->isSuccess());
				return *this->val;
			};

			[[nodiscard]] constexpr auto value() & noexcept -> T& {
				EVO_DEBUG_ASSERT(this->isSuccess());
				return *this->val;
			};


			[[nodiscard]] constexpr auto value() && noexcept -> T&& {
				EVO_DEBUG_ASSERT(this->isSuccess());
				return std::move(*this->val);
			};


			[[nodiscard]] static constexpr auto error() noexcept -> Result<T> { return Result<T>(resultError); };


		private:
			std::optional<T> val;
	};


	template<>
	class Result<void>{
		public:
			///////////////////////////////////
			// constructors / destructors

			[[nodiscard]] constexpr Result() : is_error(false) {}

			[[nodiscard]] constexpr Result(ResultError_t) noexcept : is_error(true) {};
			~Result() = default;

			[[nodiscard]] constexpr Result(const Result<void>& rhs) noexcept : is_error(rhs.is_error) {}
			[[nodiscard]] constexpr auto operator=(const Result<void>& rhs) noexcept {
				this->is_error = rhs.is_error;
			};

			[[nodiscard]] constexpr Result(Result<void>&& rhs) noexcept : is_error(std::move(rhs.is_error)) {};


			[[nodiscard]] static constexpr auto fromBool(bool is_success) noexcept -> Result {
				return Result(!is_success);
			}


			///////////////////////////////////
			// checking

			[[nodiscard]] constexpr auto isSuccess() const noexcept -> bool { return !this->is_error; };
			[[nodiscard]] constexpr auto isError() const noexcept -> bool { return this->is_error; };


			///////////////////////////////////
			// getting value

			[[nodiscard]] static constexpr auto error() noexcept -> Result<void> { return Result<void>(resultError); };


		private:
			[[nodiscard]] constexpr Result(bool _is_error) : is_error(_is_error) {}
	
		private:
			bool is_error;
	};


};
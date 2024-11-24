#pragma once


#include "../defines.h"

#include <type_traits>


namespace evo{

	// reference: https://en.cppreference.com/w/cpp/utility/expected
	// A simplified version of C++23's std::expected / std::unexpected


	template<class E>
	class Unexpected{
		public:
			EVO_NODISCARD constexpr Unexpected(const Unexpected&) = default;
			EVO_NODISCARD constexpr Unexpected(Unexpected&&) = default;

			EVO_NODISCARD constexpr explicit Unexpected(const E& val) : value(val) {};
			EVO_NODISCARD constexpr explicit Unexpected(E&& val) : value(std::move(val)) {};


			EVO_NODISCARD constexpr auto error() const noexcept -> const E& { return this->value; };
			EVO_NODISCARD constexpr auto error() noexcept -> E& { return this->value; };


		private:
			E value;
	};





	template<class T, class E>
	class Expected{
		public:
			using value_type = T;
			using error_type = E;
			using unexpected_type = Unexpected<E>;

			//////////////////////////////////////////////////////////////////////
			// constructors / destructors

			EVO_NODISCARD constexpr Expected() noexcept : expected_val(), has_expected_value(true) {};

			constexpr ~Expected() noexcept {
				if(this->has_value()){
					std::destroy_at(&this->expected_val);
				}else{
					std::destroy_at(&this->error_val);
				}
			}


			///////////////////////////////////
			// copy

			EVO_NODISCARD constexpr Expected(const Expected& rhs) noexcept = default;

			constexpr auto operator=(const Expected& rhs) noexcept -> Expected {
				this->has_expected_value = rhs.has_expected_value;
				if(rhs.has_expected_value){
					this->expected_val = rhs.expected_val;
				}else{
					this->error_val = rhs.error_val;
				}

				return *this;
			};


			///////////////////////////////////
			// move

			EVO_NODISCARD constexpr Expected(Expected&& rhs) noexcept {
				this->has_expected_value = rhs.has_expected_value;
				if(rhs.has_expected_value){
					this->expected_val = std::move(rhs.expected_val);
				}else{
					this->error_val = std::move(rhs.error_val);
				}
			};

			constexpr auto operator=(Expected&& rhs) noexcept -> Expected {
				this->has_expected_value = rhs.has_expected_value;
				if(rhs.has_expected_value){
					this->expected_val = std::move(rhs.expected_val);
				}else{
					this->error_val = std::move(rhs.error_val);
				}

				return *this;
			};


			///////////////////////////////////
			// expected

			EVO_NODISCARD constexpr Expected(const T& val) noexcept
				: has_expected_value(true), expected_val(val) {};

			EVO_NODISCARD constexpr Expected(T&& val) noexcept
				: has_expected_value(true), expected_val(std::move(val)) {};


			///////////////////////////////////
			// unexpected

			EVO_NODISCARD constexpr Expected(const Unexpected<E>& val) noexcept
				: has_expected_value(false), error_val(val.error()) {};

			EVO_NODISCARD constexpr Expected(Unexpected<E>&& val) noexcept
				: has_expected_value(false), error_val(std::move(val.error())) {};






			///////////////////////////////////
			// deleted special member functions

			constexpr Expected(const Expected&&) = delete;
			constexpr Expected& operator=(const Expected&&) = delete;


			//////////////////////////////////////////////////////////////////////
			// observers

			///////////////////////////////////
			// dereference

			EVO_NODISCARD constexpr auto operator->() const noexcept -> const T* {
				EVO_DEBUG_ASSERT(this->has_value()); // attempted to get value of evo::Expected that currently has error value

				return *this->expected_val;
			};
			
			EVO_NODISCARD constexpr auto operator->() noexcept -> T* {
				EVO_DEBUG_ASSERT(this->has_value()); // attempted to get value of evo::Expected that currently has error value

				return *this->expected_val;
			};

			EVO_NODISCARD constexpr auto operator*() const noexcept -> const T& {
				EVO_DEBUG_ASSERT(this->has_value()); // attempted to get value of evo::Expected that currently has error value

				return this->expected_val;
			};

			EVO_NODISCARD constexpr auto operator*() noexcept -> T& {
				EVO_DEBUG_ASSERT(this->has_value()); // attempted to get value of evo::Expected that currently has error value

				return this->expected_val;
			};



			///////////////////////////////////
			// has value

			EVO_NODISCARD constexpr auto has_value() const noexcept -> bool { return this->has_expected_value; };


			///////////////////////////////////
			// value

			EVO_NODISCARD constexpr auto value() const noexcept -> const T& {
				EVO_DEBUG_ASSERT(this->has_value()); // attempted to get value of evo::Expected that currently has error value

				return this->expected_val;
			};
			EVO_NODISCARD constexpr auto value() noexcept -> T& {
				EVO_DEBUG_ASSERT(this->has_value()); // attempted to get value of evo::Expected that currently has error value

				return this->expected_val;
			};


			///////////////////////////////////
			// error

			EVO_NODISCARD constexpr auto error() const noexcept -> const E& {
				EVO_DEBUG_ASSERT(this->has_value() == false); // attempted to get error value of evo::Expected that currently has expected value

				return this->error_val;
			};
			EVO_NODISCARD constexpr auto error() noexcept -> E& {
				EVO_DEBUG_ASSERT(this->has_value() == false); // attempted to get error value of evo::Expected that currently has expected value

				return this->error_val;
			};

	
		private:
			bool has_expected_value;
			union{
				T expected_val;
				E error_val;
			};

	};


};
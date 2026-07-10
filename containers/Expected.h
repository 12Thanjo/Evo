#pragma once


#include "../defines.h"


namespace evo{

	// reference: https://en.cppreference.com/w/cpp/utility/expected
	// A simplified version of C++23's std::expected / std::unexpected


	template<class E>
	class Unexpected{
		public:
			[[nodiscard]] constexpr Unexpected(const Unexpected&) = default;
			[[nodiscard]] constexpr Unexpected(Unexpected&&) = default;

			[[nodiscard]] constexpr explicit Unexpected(const E& val) : value(val) {};
			[[nodiscard]] constexpr explicit Unexpected(E&& val) : value(std::move(val)) {};


			[[nodiscard]] constexpr auto error() const noexcept -> const E& { return this->value; };
			[[nodiscard]] constexpr auto error() noexcept -> E& { return this->value; };


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

			[[nodiscard]] constexpr Expected() noexcept : expected_val(), has_expected_value(true) {};

			constexpr ~Expected() noexcept {
				if(this->has_value()){
					std::destroy_at(&this->expected_val);
				}else{
					std::destroy_at(&this->error_val);
				}
			}


			///////////////////////////////////
			// copy

			[[nodiscard]] constexpr Expected(const Expected& rhs) noexcept {
				this->has_expected_value = rhs.has_expected_value;
				if(rhs.has_expected_value){
					this->expected_val = rhs.expected_val;
				}else{
					this->error_val = rhs.error_val;
				}
			}

			constexpr auto operator=(const Expected& rhs) noexcept -> Expected& {
				std::destroy_at(this);
				this->has_expected_value = rhs.has_expected_value;
				if(rhs.has_expected_value){
					this->expected_val = rhs.expected_val;
				}else{
					this->error_val = rhs.error_val;
				}

				return *this;
			}


			///////////////////////////////////
			// move

			[[nodiscard]] constexpr Expected(Expected&& rhs) noexcept {
				this->has_expected_value = rhs.has_expected_value;
				if(rhs.has_expected_value){
					this->expected_val = std::move(rhs.expected_val);
				}else{
					this->error_val = std::move(rhs.error_val);
				}
			};

			constexpr auto operator=(Expected&& rhs) noexcept -> Expected& {
				std::destroy_at(this);
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

			[[nodiscard]] constexpr Expected(const T& val) noexcept
				: has_expected_value(true), expected_val(val) {};

			[[nodiscard]] constexpr Expected(T&& val) noexcept
				: has_expected_value(true), expected_val(std::move(val)) {};


			///////////////////////////////////
			// unexpected

			[[nodiscard]] constexpr Expected(const Unexpected<E>& val) noexcept
				: has_expected_value(false), error_val(val.error()) {};

			[[nodiscard]] constexpr Expected(Unexpected<E>&& val) noexcept
				: has_expected_value(false), error_val(std::move(val.error())) {};






			///////////////////////////////////
			// deleted special member functions

			constexpr Expected(const Expected&&) = delete;
			constexpr Expected& operator=(const Expected&&) = delete;


			//////////////////////////////////////////////////////////////////////
			// observers

			///////////////////////////////////
			// dereference

			[[nodiscard]] constexpr auto operator->() const noexcept -> const T* {
				EVO_DEBUG_ASSERT(this->has_value()); // attempted to get value of evo::Expected that currently has error value

				return &this->expected_val;
			};
			
			[[nodiscard]] constexpr auto operator->() noexcept -> T* {
				EVO_DEBUG_ASSERT(this->has_value()); // attempted to get value of evo::Expected that currently has error value

				return &this->expected_val;
			};

			[[nodiscard]] constexpr auto operator*() const noexcept -> const T& {
				EVO_DEBUG_ASSERT(this->has_value()); // attempted to get value of evo::Expected that currently has error value

				return this->expected_val;
			};

			[[nodiscard]] constexpr auto operator*() noexcept -> T& {
				EVO_DEBUG_ASSERT(this->has_value()); // attempted to get value of evo::Expected that currently has error value

				return this->expected_val;
			};



			///////////////////////////////////
			// has value

			[[nodiscard]] constexpr auto has_value() const noexcept -> bool { return this->has_expected_value; };


			///////////////////////////////////
			// value

			[[nodiscard]] constexpr auto value() const noexcept -> const T& {
				EVO_DEBUG_ASSERT(this->has_value()); // attempted to get value of evo::Expected that currently has error value

				return this->expected_val;
			};
			[[nodiscard]] constexpr auto value() noexcept -> T& {
				EVO_DEBUG_ASSERT(this->has_value()); // attempted to get value of evo::Expected that currently has error value

				return this->expected_val;
			};


			///////////////////////////////////
			// error

			[[nodiscard]] constexpr auto error() const noexcept -> const E& {
				EVO_DEBUG_ASSERT(this->has_value() == false); // attempted to get error value of evo::Expected that currently has expected value

				return this->error_val;
			};
			[[nodiscard]] constexpr auto error() noexcept -> E& {
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






	template<class E>
	class Expected<void, E>{
		public:
			using value_type = void;
			using error_type = E;
			using unexpected_type = Unexpected<E>;

			//////////////////////////////////////////////////////////////////////
			// constructors / destructors

			[[nodiscard]] constexpr Expected() noexcept = default;

			constexpr ~Expected() noexcept = default;


			///////////////////////////////////
			// copy

			[[nodiscard]] constexpr Expected(const Expected& rhs) noexcept {
				this->error_val = rhs.error_val;
			};

			constexpr auto operator=(const Expected& rhs) noexcept -> Expected& {
				std::construct_at(this, rhs);
				return *this;
			};


			///////////////////////////////////
			// move

			[[nodiscard]] constexpr Expected(Expected&& rhs) noexcept {
				this->error_val = std::move(rhs.error_val);
			};

			constexpr auto operator=(Expected&& rhs) noexcept -> Expected& {
				std::construct_at(this, std::move(rhs));
				return *this;
			};



			///////////////////////////////////
			// unexpected

			[[nodiscard]] constexpr Expected(const Unexpected<E>& val) noexcept : error_val(val.error()) {};
			[[nodiscard]] constexpr Expected(Unexpected<E>&& val) noexcept : error_val(std::move(val.error())) {};



			///////////////////////////////////
			// deleted special member functions

			constexpr Expected(const Expected&&) = delete;
			constexpr Expected& operator=(const Expected&&) = delete;


			//////////////////////////////////////////////////////////////////////
			// observers



			///////////////////////////////////
			// has value

			[[nodiscard]] constexpr auto has_value() const noexcept -> bool { return !this->error_val.has_value(); };


			///////////////////////////////////
			// error

			[[nodiscard]] constexpr auto error() const noexcept -> const E& {
				EVO_DEBUG_ASSERT(this->has_value() == false); // attempted to get error value of evo::Expected that currently has expected value

				return *this->error_val;
			};
			[[nodiscard]] constexpr auto error() noexcept -> E& {
				EVO_DEBUG_ASSERT(this->has_value() == false); // attempted to get error value of evo::Expected that currently has expected value

				return *this->error_val;
			};

	
		private:
			std::optional<E> error_val{};
	};


};
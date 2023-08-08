#pragma once



namespace evo{
	namespace time{

		//////////////////////////////////////////////////////////////////////
		// time value types

		struct Nanoseconds;
		struct Milliseconds;
		struct Seconds;



		struct Nanoseconds{
			public:
				constexpr Nanoseconds()                       noexcept : value(0)         {};
				constexpr Nanoseconds(i64 time)               noexcept : value(time)      {};
				constexpr Nanoseconds(const Nanoseconds& rhs) noexcept : value(rhs.value) {};


				// time type conversion
				constexpr explicit operator Milliseconds() const noexcept;
				constexpr explicit operator Seconds() const noexcept;


				// arithmentic operators
				constexpr auto operator +(const Nanoseconds& rhs) const noexcept -> Nanoseconds { return Nanoseconds{this->value + rhs.value}; };
				constexpr auto operator -(const Nanoseconds& rhs) const noexcept -> Nanoseconds { return Nanoseconds{this->value - rhs.value}; };
				constexpr auto operator *(const Nanoseconds& rhs) const noexcept -> Nanoseconds { return Nanoseconds{this->value * rhs.value}; };
				constexpr auto operator /(const Nanoseconds& rhs) const noexcept -> Nanoseconds { return Nanoseconds{this->value / rhs.value}; };

				constexpr auto operator +=(const Nanoseconds& rhs) noexcept -> Nanoseconds& { this->value += rhs.value; return *this; };
				constexpr auto operator -=(const Nanoseconds& rhs) noexcept -> Nanoseconds& { this->value -= rhs.value; return *this; };
				constexpr auto operator *=(const Nanoseconds& rhs) noexcept -> Nanoseconds& { this->value *= rhs.value; return *this; };
				constexpr auto operator /=(const Nanoseconds& rhs) noexcept -> Nanoseconds& { this->value /= rhs.value; return *this; };


				// basic type conversion
				constexpr explicit operator i8() const noexcept  { return static_cast<i8>(this->value);  };
				constexpr explicit operator i16() const noexcept { return static_cast<i16>(this->value); };
				constexpr explicit operator i32() const noexcept { return static_cast<i32>(this->value); };
				constexpr explicit operator i64() const noexcept { return this->value; };

				constexpr explicit operator ui8() const noexcept  { return static_cast<ui8>(this->value);  };
				constexpr explicit operator ui16() const noexcept { return static_cast<ui16>(this->value); };
				constexpr explicit operator ui32() const noexcept { return static_cast<ui32>(this->value); };
				constexpr explicit operator ui64() const noexcept { return static_cast<ui64>(this->value); };

				constexpr explicit operator f32() const noexcept { return static_cast<f32>(this->value); };
				constexpr explicit operator f64() const noexcept { return static_cast<f64>(this->value); };


			private:
				i64 value;
		};




		struct Milliseconds{
			public:
				constexpr Milliseconds()                        noexcept : value(0)         {};
				constexpr Milliseconds(i64 time)                noexcept : value(time)      {};
				constexpr Milliseconds(const Milliseconds& rhs) noexcept : value(rhs.value) {};


				// time type conversion
				constexpr explicit operator Nanoseconds() const noexcept;
				constexpr explicit operator Seconds() const noexcept;


				// arithmentic operators
				constexpr auto operator +(const Milliseconds& rhs) const noexcept -> Milliseconds { return Milliseconds{this->value + rhs.value}; };
				constexpr auto operator -(const Milliseconds& rhs) const noexcept -> Milliseconds { return Milliseconds{this->value - rhs.value}; };
				constexpr auto operator *(const Milliseconds& rhs) const noexcept -> Milliseconds { return Milliseconds{this->value * rhs.value}; };
				constexpr auto operator /(const Milliseconds& rhs) const noexcept -> Milliseconds { return Milliseconds{this->value / rhs.value}; };

				constexpr auto operator +=(const Milliseconds& rhs) noexcept -> Milliseconds& { this->value += rhs.value; return *this; };
				constexpr auto operator -=(const Milliseconds& rhs) noexcept -> Milliseconds& { this->value -= rhs.value; return *this; };
				constexpr auto operator *=(const Milliseconds& rhs) noexcept -> Milliseconds& { this->value *= rhs.value; return *this; };
				constexpr auto operator /=(const Milliseconds& rhs) noexcept -> Milliseconds& { this->value /= rhs.value; return *this; };


				// basic type conversion
				constexpr explicit operator i8() const noexcept  { return static_cast<i8>(this->value);  };
				constexpr explicit operator i16() const noexcept { return static_cast<i16>(this->value); };
				constexpr explicit operator i32() const noexcept { return static_cast<i32>(this->value); };
				constexpr explicit operator i64() const noexcept { return this->value; };

				constexpr explicit operator ui8() const noexcept  { return static_cast<ui8>(this->value);  };
				constexpr explicit operator ui16() const noexcept { return static_cast<ui16>(this->value); };
				constexpr explicit operator ui32() const noexcept { return static_cast<ui32>(this->value); };
				constexpr explicit operator ui64() const noexcept { return static_cast<ui64>(this->value); };

				constexpr explicit operator f32() const noexcept { return static_cast<f32>(this->value); };
				constexpr explicit operator f64() const noexcept { return static_cast<f64>(this->value); };


			private:
				i64 value = 0;
		};




		struct Seconds{
			public:
				constexpr Seconds()                   noexcept : value(0)         {};
				constexpr Seconds(i64 time)           noexcept : value(time)      {};
				constexpr Seconds(const Seconds& rhs) noexcept : value(rhs.value) {};

				// time type conversion
				constexpr explicit operator Nanoseconds() const noexcept;
				constexpr explicit operator Milliseconds() const noexcept;


				// arithmentic operators
				constexpr auto operator +(const Seconds& rhs) const noexcept -> Seconds { return Seconds{this->value + rhs.value}; };
				constexpr auto operator -(const Seconds& rhs) const noexcept -> Seconds { return Seconds{this->value - rhs.value}; };
				constexpr auto operator *(const Seconds& rhs) const noexcept -> Seconds { return Seconds{this->value * rhs.value}; };
				constexpr auto operator /(const Seconds& rhs) const noexcept -> Seconds { return Seconds{this->value / rhs.value}; };

				constexpr auto operator +=(const Seconds& rhs) noexcept -> Seconds& { this->value += rhs.value; return *this; };
				constexpr auto operator -=(const Seconds& rhs) noexcept -> Seconds& { this->value -= rhs.value; return *this; };
				constexpr auto operator *=(const Seconds& rhs) noexcept -> Seconds& { this->value *= rhs.value; return *this; };
				constexpr auto operator /=(const Seconds& rhs) noexcept -> Seconds& { this->value /= rhs.value; return *this; };


				// basic type conversion
				constexpr explicit operator i8() const noexcept  { return static_cast<i8>(this->value);  };
				constexpr explicit operator i16() const noexcept { return static_cast<i16>(this->value); };
				constexpr explicit operator i32() const noexcept { return static_cast<i32>(this->value); };
				constexpr explicit operator i64() const noexcept { return this->value; };

				constexpr explicit operator ui8() const noexcept  { return static_cast<ui8>(this->value);  };
				constexpr explicit operator ui16() const noexcept { return static_cast<ui16>(this->value); };
				constexpr explicit operator ui32() const noexcept { return static_cast<ui32>(this->value); };
				constexpr explicit operator ui64() const noexcept { return static_cast<ui64>(this->value); };

				constexpr explicit operator f32() const noexcept { return static_cast<f32>(this->value); };
				constexpr explicit operator f64() const noexcept { return static_cast<f64>(this->value); };


			private:
				i64 value = 0;
		};





		//////////////////////////////////////////////////////////////////////
		// time value type conversion operator implementations

		constexpr Nanoseconds::operator Milliseconds() const noexcept { return Milliseconds{ static_cast<i64>(this->value / 1e6) }; };
		constexpr Nanoseconds::operator Seconds() const noexcept { return Seconds{ static_cast<i64>(this->value / 1e9) }; };

		constexpr Milliseconds::operator Nanoseconds() const noexcept { return Nanoseconds{ static_cast<i64>(this->value * 1e6) }; };
		constexpr Milliseconds::operator Seconds() const noexcept { return Seconds{ static_cast<i64>(this->value / 1e3) }; };

		constexpr Seconds::operator Nanoseconds() const noexcept { return Nanoseconds{ static_cast<i64>(this->value * 1e9) }; };
		constexpr Seconds::operator Milliseconds() const noexcept { return Milliseconds{ static_cast<i64>(this->value * 1e6) }; };



		//////////////////////////////////////////////////////////////////////
		// general functions

		EVO_NODISCARD auto now() noexcept -> Nanoseconds;


		struct CurrentTime{
			ui16 year;
			ui8 month;
			ui8 day;

			ui8 hours;
			ui8 minutes;
			ui8 seconds;
		};

		EVO_NODISCARD auto getCurrentTime() noexcept -> CurrentTime;


	};
};

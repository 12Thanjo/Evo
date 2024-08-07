#pragma once

#include "../defines.h"


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

				// comparison operators
				constexpr auto operator ==(const Nanoseconds& rhs) const noexcept -> bool { return this->value == rhs.value; }
				constexpr auto operator !=(const Nanoseconds& rhs) const noexcept -> bool { return this->value != rhs.value; }
				constexpr auto operator <(const Nanoseconds& rhs) const noexcept -> bool { return this->value < rhs.value; }
				constexpr auto operator <=(const Nanoseconds& rhs) const noexcept -> bool { return this->value <= rhs.value; }
				constexpr auto operator >(const Nanoseconds& rhs) const noexcept -> bool { return this->value > rhs.value; }
				constexpr auto operator >=(const Nanoseconds& rhs) const noexcept -> bool { return this->value > rhs.value; }

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
				constexpr explicit operator i8() const noexcept  { return i8(this->value);  };
				constexpr explicit operator i16() const noexcept { return i16(this->value); };
				constexpr explicit operator i32() const noexcept { return i32(this->value); };
				constexpr explicit operator i64() const noexcept { return this->value; };

				constexpr explicit operator ui8() const noexcept  { return ui8(this->value);  };
				constexpr explicit operator ui16() const noexcept { return ui16(this->value); };
				constexpr explicit operator ui32() const noexcept { return ui32(this->value); };
				constexpr explicit operator ui64() const noexcept { return ui64(this->value); };

				constexpr explicit operator f32() const noexcept { return f32(this->value); };
				constexpr explicit operator f64() const noexcept { return f64(this->value); };


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

				// comparison operators
				constexpr auto operator ==(const Milliseconds& rhs) const noexcept -> bool { return this->value == rhs.value; }
				constexpr auto operator !=(const Milliseconds& rhs) const noexcept -> bool { return this->value != rhs.value; }
				constexpr auto operator <(const Milliseconds& rhs) const noexcept -> bool { return this->value < rhs.value; }
				constexpr auto operator <=(const Milliseconds& rhs) const noexcept -> bool { return this->value <= rhs.value; }
				constexpr auto operator >(const Milliseconds& rhs) const noexcept -> bool { return this->value > rhs.value; }
				constexpr auto operator >=(const Milliseconds& rhs) const noexcept -> bool { return this->value > rhs.value; }

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
				constexpr explicit operator i8() const noexcept  { return i8(this->value);  };
				constexpr explicit operator i16() const noexcept { return i16(this->value); };
				constexpr explicit operator i32() const noexcept { return i32(this->value); };
				constexpr explicit operator i64() const noexcept { return this->value; };

				constexpr explicit operator ui8() const noexcept  { return ui8(this->value);  };
				constexpr explicit operator ui16() const noexcept { return ui16(this->value); };
				constexpr explicit operator ui32() const noexcept { return ui32(this->value); };
				constexpr explicit operator ui64() const noexcept { return ui64(this->value); };

				constexpr explicit operator f32() const noexcept { return f32(this->value); };
				constexpr explicit operator f64() const noexcept { return f64(this->value); };


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

				// comparison operators
				constexpr auto operator ==(const Seconds& rhs) const noexcept -> bool { return this->value == rhs.value; }
				constexpr auto operator !=(const Seconds& rhs) const noexcept -> bool { return this->value != rhs.value; }
				constexpr auto operator <(const Seconds& rhs) const noexcept -> bool { return this->value < rhs.value; }
				constexpr auto operator <=(const Seconds& rhs) const noexcept -> bool { return this->value <= rhs.value; }
				constexpr auto operator >(const Seconds& rhs) const noexcept -> bool { return this->value > rhs.value; }
				constexpr auto operator >=(const Seconds& rhs) const noexcept -> bool { return this->value > rhs.value; }

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
				constexpr explicit operator i8() const noexcept  { return i8(this->value);  };
				constexpr explicit operator i16() const noexcept { return i16(this->value); };
				constexpr explicit operator i32() const noexcept { return i32(this->value); };
				constexpr explicit operator i64() const noexcept { return this->value; };

				constexpr explicit operator ui8() const noexcept  { return ui8(this->value);  };
				constexpr explicit operator ui16() const noexcept { return ui16(this->value); };
				constexpr explicit operator ui32() const noexcept { return ui32(this->value); };
				constexpr explicit operator ui64() const noexcept { return ui64(this->value); };

				constexpr explicit operator f32() const noexcept { return f32(this->value); };
				constexpr explicit operator f64() const noexcept { return f64(this->value); };


			private:
				i64 value = 0;
		};





		//////////////////////////////////////////////////////////////////////
		// time value type conversion operator implementations

		constexpr Nanoseconds::operator Milliseconds() const noexcept { return Milliseconds{ i64(this->value / 1e6) }; };
		constexpr Nanoseconds::operator Seconds() const noexcept { return Seconds{ i64(this->value / 1e9) }; };

		constexpr Milliseconds::operator Nanoseconds() const noexcept { return Nanoseconds{ i64(this->value * 1e6) }; };
		constexpr Milliseconds::operator Seconds() const noexcept { return Seconds{ i64(this->value / 1e3) }; };

		constexpr Seconds::operator Nanoseconds() const noexcept { return Nanoseconds{ i64(this->value * 1e9) }; };
		constexpr Seconds::operator Milliseconds() const noexcept { return Milliseconds{ i64(this->value * 1e6) }; };



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



//////////////////////////////////////////////////////////////////////
// hashing for time types

template<>
struct std::hash<evo::time::Nanoseconds>{
	auto operator()(const evo::time::Nanoseconds& time) const noexcept -> size_t {
		return std::hash<int64_t>{}(evo::i64(time));
	};
};

template<>
struct std::hash<evo::time::Milliseconds>{
	auto operator()(const evo::time::Milliseconds& time) const noexcept -> size_t {
		return std::hash<int64_t>{}(evo::i64(time));
	};
};


template<>
struct std::hash<evo::time::Seconds>{
	auto operator()(const evo::time::Seconds& time) const noexcept -> size_t {
		return std::hash<int64_t>{}(evo::i64(time));
	};
};



//////////////////////////////////////////////////////////////////////
// string formatting for time types


template<>
struct std::formatter<evo::time::Nanoseconds> : std::formatter<int64_t> {
    auto format(const evo::time::Nanoseconds& time, std::format_context& ctx) const -> std::format_context::iterator {
        return std::formatter<int64_t>::format(evo::i64(time), ctx);
    };
};

template<>
struct std::formatter<evo::time::Milliseconds> : std::formatter<int64_t> {
    auto format(const evo::time::Milliseconds& time, std::format_context& ctx) const -> std::format_context::iterator {
        return std::formatter<int64_t>::format(evo::i64(time), ctx);
    };
};

template<>
struct std::formatter<evo::time::Seconds> : std::formatter<int64_t> {
    auto format(const evo::time::Seconds& time, std::format_context& ctx) const -> std::format_context::iterator {
        return std::formatter<int64_t>::format(evo::i64(time), ctx);
    };
};


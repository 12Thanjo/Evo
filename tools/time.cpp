#include "Evo.h"
#include "time.h"


#include <chrono>


namespace evo{
	namespace time{

		auto now() noexcept -> Nanoseconds {
			const ui64 time_now = std::chrono::time_point_cast<std::chrono::nanoseconds>(
				std::chrono::high_resolution_clock::now()
			).time_since_epoch().count();

			return Nanoseconds{i64(time_now)};
		};




		auto getCurrentTime() noexcept -> CurrentTime {
			const auto time_now = std::chrono::system_clock::now();
			const std::time_t current_time = std::chrono::system_clock::to_time_t(time_now);

			std::tm local_time;
			localtime_s(&local_time, &current_time);

			return CurrentTime{
				.year    = uint16_t( local_time.tm_year + 1900 ),
				.month   = uint8_t( local_time.tm_mon  ),
				.day     = uint8_t( local_time.tm_mday ),

				.hours   = uint8_t( local_time.tm_hour ),
				.minutes = uint8_t( local_time.tm_min  ),
				.seconds = uint8_t( local_time.tm_sec  ),
			};
		};
		


	};
};
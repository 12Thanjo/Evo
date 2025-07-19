#include "random.h"


#include <random>

namespace evo{
	
	static std::random_device random_device;
	static std::mt19937_64 random_engine{random_device()};

	auto random() noexcept -> ui64 {
		std::uniform_int_distribution<ui64> uniform_distribution{};
		return uniform_distribution(random_engine);
	};


	auto random(ui64 max) noexcept -> ui64 {
		std::uniform_int_distribution<ui64> uniform_distribution{0, max};
		return uniform_distribution(random_engine);
	};


	auto random(ui64 min, ui64 max) noexcept -> ui64 {
		std::uniform_int_distribution<ui64> uniform_distribution{min, max};
		return uniform_distribution(random_engine);
	};



	auto random01() noexcept -> f64 {
		return f64(random()) / f64(std::numeric_limits<uint64_t>::max());
	};
	


	auto randomBool() noexcept -> bool {
		return static_cast<bool>(evo::random(0, 1));
	};


};

#pragma once

#include "../defines.h"

#include "../utils/numeric_types.h"


namespace evo{


	[[nodiscard]] auto random() noexcept -> ui64;
	[[nodiscard]] auto random(ui64 max) noexcept -> ui64;
	[[nodiscard]] auto random(ui64 min, ui64 max) noexcept -> ui64;

	[[nodiscard]] auto random01() noexcept -> f64;
	
	[[nodiscard]] auto randomBool() noexcept -> bool;


};

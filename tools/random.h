#pragma once

#include "../defines.h"

#include "../utils/numeric_types.h"


namespace evo{


	EVO_NODISCARD auto random() noexcept -> ui64;
	EVO_NODISCARD auto random(ui64 max) noexcept -> ui64;
	EVO_NODISCARD auto random(ui64 min, ui64 max) noexcept -> ui64;


};


#include "../Evo.h"

enum class FlagsTest{
	A,
	B,
	C,

	_max,
};

auto main() noexcept -> int {
	evo::logTrace("logging test (Trace)");
	evo::logDebug("logging test (Debug)");
	evo::logInfo("logging test (Info)");
	evo::logWarning("logging test (Warning)");
	evo::logError("logging test (Error)");
	evo::logFatal("logging test (Fatal)");


	auto flags         = evo::Flags<FlagsTest>();
	auto static_string = evo::StaticString<5>{"hello"};
	auto static_vector = evo::StaticVector<int, 6>{};
	auto array_proxy   = evo::ArrayProxy<int>{static_vector};


	return 0;
};
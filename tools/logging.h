#pragma once

#include <string>

namespace evo{

	auto log(const std::string& message) noexcept -> void;
	auto log(const char* message) noexcept -> void;



	auto styleConsoleFatal() noexcept -> void;
	auto styleConsoleError() noexcept -> void;
	auto styleConsoleWarning() noexcept -> void;
	auto styleConsoleInfo() noexcept -> void;
	auto styleConsoleDebug() noexcept -> void;
	auto styleConsoleTrace() noexcept -> void;
	auto styleConsoleReset() noexcept -> void;


	
};

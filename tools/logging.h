#pragma once

#include <string>
#include <format>

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



	///////////////////////////////////
	// fatal

	inline auto logFatal(const std::string& message) noexcept -> void {
		styleConsoleFatal();
		log(message + '\n');
		styleConsoleReset();
	};

	inline auto logFatal(const char* message) noexcept -> void {
		styleConsoleFatal();
		log( std::format("{}\n", message) );
		styleConsoleReset();
	};


	///////////////////////////////////
	// error

	inline auto logError(const std::string& message) noexcept -> void {
		styleConsoleError();
		log(message + '\n');
		styleConsoleReset();
	};

	inline auto logError(const char* message) noexcept -> void {
		styleConsoleError();
		log( std::format("{}\n", message) );
		styleConsoleReset();
	};


	///////////////////////////////////
	// warning

	inline auto logWarning(const std::string& message) noexcept -> void {
		styleConsoleWarning();
		log(message + '\n');
		styleConsoleReset();
	};

	inline auto logWarning(const char* message) noexcept -> void {
		styleConsoleWarning();
		log( std::format("{}\n", message) );
		styleConsoleReset();
	};


	///////////////////////////////////
	// info

	inline auto logInfo(const std::string& message) noexcept -> void {
		styleConsoleInfo();
		log(message + '\n');
		styleConsoleReset();
	};

	inline auto logInfo(const char* message) noexcept -> void {
		styleConsoleInfo();
		log( std::format("{}\n", message) );
		styleConsoleReset();
	};


	///////////////////////////////////
	// debug

	inline auto logDebug(const std::string& message) noexcept -> void {
		#if defined(EVO_CONFIG_DEBUG)
			styleConsoleDebug();
			log(message + '\n');
			styleConsoleReset();
		#endif
	};

	inline auto logDebug(const char* message) noexcept -> void {
		#if defined(EVO_CONFIG_DEBUG)
			styleConsoleDebug();
			log( std::format("{}\n", message) );
			styleConsoleReset();
		#endif
	};



	inline auto logTrace(const std::string& message) noexcept -> void {
		#if defined(EVO_CONFIG_DEBUG)
			styleConsoleTrace();
			log(message + '\n');
			styleConsoleReset();
		#endif
	};

	inline auto logTrace(const char* message) noexcept -> void {
		#if defined(EVO_CONFIG_DEBUG)
			styleConsoleTrace();
			log( std::format("{}\n", message) );
			styleConsoleReset();
		#endif
	};


	
};

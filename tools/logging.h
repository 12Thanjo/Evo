#pragma once

#include <string>
#include <format>

#include "../defines.h"


namespace evo{

	auto log(CStrProxy message) noexcept -> void;


	auto styleConsoleFatal() noexcept -> void;
	auto styleConsoleError() noexcept -> void;
	auto styleConsoleWarning() noexcept -> void;
	auto styleConsoleInfo() noexcept -> void;
	auto styleConsoleSuccess() noexcept -> void;
	auto styleConsoleDebug() noexcept -> void;
	auto styleConsoleTrace() noexcept -> void;
	auto styleConsoleReset() noexcept -> void;




	inline auto logFatal(CStrProxy message) noexcept -> void {
		styleConsoleFatal();
		log( std::format("{}\n", message.data()) );
		styleConsoleReset();
	};

	inline auto logError(CStrProxy message) noexcept -> void {
		styleConsoleError();
		log( std::format("{}\n", message.data()) );
		styleConsoleReset();
	};

	inline auto logWarning(CStrProxy message) noexcept -> void {
		styleConsoleWarning();
		log( std::format("{}\n", message.data()) );
		styleConsoleReset();
	};

	inline auto logInfo(CStrProxy message) noexcept -> void {
		styleConsoleInfo();
		log( std::format("{}\n", message.data()) );
		styleConsoleReset();
	};

	inline auto logSuccess(CStrProxy message) noexcept -> void {
		styleConsoleSuccess();
		log( std::format("{}\n", message.data()) );
		styleConsoleReset();
	};

	inline auto logDebug(CStrProxy message) noexcept -> void {
		#if defined(EVO_CONFIG_DEBUG)
			styleConsoleDebug();
			log( std::format("{}\n", message.data()) );
			styleConsoleReset();
		#endif
	};

	inline auto logTrace(CStrProxy message) noexcept -> void {
		#if defined(EVO_CONFIG_DEBUG)
			styleConsoleTrace();
			log( std::format("{}\n", message.data()) );
			styleConsoleReset();
		#endif
	};



	//////////////////////////////////////////////////////////////////////
	// asserts, etc.

	inline auto Assert(bool conditional, CStrProxy message) noexcept -> void {
		if(conditional == false){
			logFatal(message);
			breakpoint();
		}
	};



	inline auto debugAssert([[maybe_unused]] bool conditional, [[maybe_unused]] CStrProxy message) noexcept -> void {
		#if defined(EVO_CONFIG_DEBUG)
			evo::Assert(conditional, message);
		#endif
	};


	// #if defined(EVO_CONFIG_DEBUG)
		#if defined(EVO_COMPILER_MSVC)
			#define EVO_FATAL_BREAK(msg) evo::logFatal(msg); evo::breakpoint(); __assume(false);
		#else
			#define EVO_FATAL_BREAK(msg) evo::logFatal(msg); evo::breakpoint(); __builtin_unreachable();
		#endif

	// #else
	// 	#define EVO_FATAL_BREAK(msg) evo::logFatal(msg); std::exit(EXIT_FAILURE);

	// #endif

};

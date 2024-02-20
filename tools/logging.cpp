#include "Evo.h"

#include "logging.h"



#if defined(EVO_PLATFORM_WINDOWS)
	#if !defined(NOMINMAX)
		#define WIN32_LEAN_AND_MEAN
	#endif

	#if !defined(NOMINMAX)
		#define NOCOMM
	#endif

	#if !defined(NOMINMAX)
		#define NOMINMAX
	#endif

	#include <windows.h>

#else
	#include <iostream>
#endif




namespace evo{

	#if defined(EVO_PLATFORM_WINDOWS)

		auto log(CStrProxy message) noexcept -> void {
			OutputDebugStringA(message.data());
			WriteConsoleA(GetStdHandle(STD_OUTPUT_HANDLE), message.data(), static_cast<DWORD>(stringSize(message.data(), UINT_MAX)), nullptr, nullptr);
		};


		auto styleConsoleFatal() noexcept -> void {
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE | BACKGROUND_RED);
		};

		auto styleConsoleError() noexcept -> void {
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED);
		};

		auto styleConsoleWarning() noexcept -> void {
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED | FOREGROUND_GREEN);
		};

		auto styleConsoleInfo() noexcept -> void {
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_BLUE | FOREGROUND_GREEN);
		};

		auto styleConsoleSuccess() noexcept -> void {
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_GREEN);
		};

		auto styleConsoleDebug() noexcept -> void {
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED | FOREGROUND_BLUE);
		};

		auto styleConsoleTrace() noexcept -> void {
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY);
		};

		auto styleConsoleReset() noexcept -> void {
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
		};

	#else
		auto log(CStrProxy message) noexcept -> void {
			std::cout << message.data();
		};


		auto styleConsoleFatal() noexcept -> void {
			std::cout << "\033[41m";
		};

		auto styleConsoleError() noexcept -> void {
			std::cout << "\033[31m";
		};

		auto styleConsoleWarning() noexcept -> void {
			std::cout << "\033[33m";
		};

		auto styleConsoleInfo() noexcept -> void {
			std::cout << "\033[36m";
		};

		auto styleConsoleSuccess() noexcept -> void {
			std::cout << "\033[32m";
		};

		auto styleConsoleDebug() noexcept -> void {
			std::cout << "\033[35m";
		};

		auto styleConsoleTrace() noexcept -> void {
			std::cout << "\033[30m";
		};

		auto styleConsoleReset() noexcept -> void {
			std::cout << "\033[0m";
		};

	#endif
	
};

#include "logging.h"

#include "utils/platform_detection.h"
#include "utils/strings.h"



#if defined(EVO_PLATFORM_WINDOWS)
	#define WIN32_LEAN_AND_MEAN
	#define NOCOMM
	#define NOMINMAX
	#include <windows.h>

#else
	#include <iostream>
#endif




namespace evo{

	#if defined(EVO_PLATFORM_WINDOWS)

		auto log(const std::string& message) noexcept -> void {
			log(message.c_str());
		};

		inline auto log(const char* message) noexcept -> void {
			OutputDebugStringA(message);
			WriteConsoleA(GetStdHandle(STD_OUTPUT_HANDLE), message, static_cast<DWORD>(stringSize(message, 1024)), nullptr, nullptr);
		};



		auto styleConsoleFatal() noexcept -> void {
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 71);
		};

		auto styleConsoleError() noexcept -> void {
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 4);
		};

		auto styleConsoleWarning() noexcept -> void {
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 6);
		};

		auto styleConsoleInfo() noexcept -> void {
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 3);
		};

		auto styleConsoleDebug() noexcept -> void {
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 5);
		};

		auto styleConsoleTrace() noexcept -> void {
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 8);
		};

		auto styleConsoleReset() noexcept -> void {
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
		};

	#else
		auto log(const std::string& message) noexcept -> void {
			std::cout << message;
		};

		auto log(const char* message) noexcept -> void {
			std::cout << message;
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

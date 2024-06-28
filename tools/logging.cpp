#include "Evo.h"

#include "logging.h"



#if defined(EVO_PLATFORM_WINDOWS)
	#if !defined(WIN32_LEAN_AND_MEAN)
		#define WIN32_LEAN_AND_MEAN
	#endif

	#if !defined(NOCOMM)
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


	auto printStdout(std::string_view message) noexcept -> void {
		#if defined(EVO_PLATFORM_WINDOWS)
			static auto handle = ::GetStdHandle(STD_OUTPUT_HANDLE);
			::WriteConsoleA(handle, message.data(), static_cast<DWORD>(message.size()), nullptr, nullptr);
		#else
			std::cout << message;
		#endif
	};

	auto printStderr(std::string_view message) noexcept -> void {
		#if defined(EVO_PLATFORM_WINDOWS)
			static auto handle = ::GetStdHandle(STD_ERROR_HANDLE);
			::WriteConsoleA(handle, message.data(), static_cast<DWORD>(message.size()), nullptr, nullptr);
		#else
			std::cerr << message;
		#endif
	};




	auto print(std::string_view message) noexcept -> void {
		#if defined(EVO_CONFIG_DEBUG) && defined(EVO_PLATFORM_WINDOWS)
			auto message_str = std::string(message);
			::OutputDebugStringA(message_str.c_str());
		#endif

		printStdout(message);
	};




	namespace log{

		static auto default_callback(const Message& message) noexcept -> void {
			const char* message_type_str = nullptr;

			switch(message.type){
				case Type::Fatal: {
					message_type_str = "<Fatal>  ";
					styleConsole::fatal();
				} break;

				case Type::Error: {
					message_type_str = "<Error>  ";
					styleConsole::error();
				} break;

				case Type::Warning: {
					message_type_str = "<Warning>";
					styleConsole::warning();
				} break;

				case Type::Success: {
					message_type_str = "<Success>";
					styleConsole::success();
				} break;

				case Type::Info: {
					message_type_str = "<Info>   ";
					styleConsole::info();
				} break;

				case Type::Debug: {
					message_type_str = "<Debug>  ";
					styleConsole::debug();
				} break;

				case Type::Trace: {
					message_type_str = "<Trace>  ";
					styleConsole::trace();
				} break;

			};

			print("{} {}\n", message_type_str, message.str);

			styleConsole::reset();
		};


		static std::mutex default_thread_safer_callback_lock{};
		static auto default_thread_safer_callback(const Message& message) noexcept -> void {
			const auto lock_guard = std::lock_guard(default_thread_safer_callback_lock);

			const char* message_type_str = nullptr;

			switch(message.type){
				case Type::Fatal: {
					message_type_str = "<Fatal>  ";
					styleConsole::fatal();
				} break;

				case Type::Error: {
					message_type_str = "<Error>  ";
					styleConsole::error();
				} break;

				case Type::Warning: {
					message_type_str = "<Warning>";
					styleConsole::warning();
				} break;

				case Type::Success: {
					message_type_str = "<Success>";
					styleConsole::success();
				} break;

				case Type::Info: {
					message_type_str = "<Info>   ";
					styleConsole::info();
				} break;

				case Type::Debug: {
					message_type_str = "<Debug>  ";
					styleConsole::debug();
				} break;

				case Type::Trace: {
					message_type_str = "<Trace>  ";
					styleConsole::trace();
				} break;

			};

			print("{} {}\n", message_type_str, message.str);

			styleConsole::reset();
		};



		static auto callback = std::function<void(const Message&)>(default_callback);


		auto setCallback(const std::function<void(const Message&)>& log_callback) noexcept -> void {
			callback = log_callback;
		};


		auto callCallback(const Message& msg) noexcept -> void {
			callback(msg);
		};


		auto setDefaultCallback() noexcept -> void {
			callback = default_callback;
		};

		auto setDefaultThreadSaferCallback() noexcept -> void {
			callback = default_thread_safer_callback;
		};

	};
	
};

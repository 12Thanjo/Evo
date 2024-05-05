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

		auto print(std::string_view message) noexcept -> void {
			#if defined(EVO_CONFIG_DEBUG)
				auto message_str = std::string(message);
				OutputDebugStringA(message_str.c_str());
			#endif

			WriteConsoleA(GetStdHandle(STD_OUTPUT_HANDLE), message.data(), static_cast<DWORD>(message.size()), nullptr, nullptr);
		};

	#else

		auto print(std::string_view message) noexcept -> void {
			std::cout << message;
		};


	#endif



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

			println("{} {}", message_type_str, message.str);

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

	};
	
};

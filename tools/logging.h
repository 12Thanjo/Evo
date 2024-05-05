#pragma once

#include <string>
#include <format>
#include <functional>

#include "../defines.h"
#include "../utils/misc.h"

#include "./time.h"


// I have no idea why this is needed, but for some reason std::format_string is defined
#if defined(EVO_COMPILER_MSVC)
	namespace std{
		template <class... _Args>
		using format_string = _Fmt_string<_Args...>;
	};
#endif

namespace evo{

	///////////////////////////////////
	// print

	auto print(std::string_view message) noexcept -> void;

	template<class... Args>
	inline auto print(std::format_string<Args...> fmt, Args&&... args) noexcept -> void {
		print(std::format(fmt, args...));
	};



	inline auto println(std::string_view message) noexcept -> void {
		print("{}\n", message);
	};

	template<class... Args>
	inline auto println(std::format_string<Args...> fmt, Args&&... args) noexcept -> void {
		print(std::format(fmt, args...) + '\n');
	};

	inline auto println() noexcept -> void {
		print("\n");
	};

	inline auto println(size_t num_newlines) noexcept -> void {
		switch(num_newlines){
			case 0: return;
			case 1: print("\n"); return;
			case 2: print("\n\n"); return;
			case 3: print("\n\n\n"); return;
			case 4: print("\n\n\n\n"); return;
			case 5: print("\n\n\n\n\n"); return;
			case 6: print("\n\n\n\n\n\n"); return;
			case 7: print("\n\n\n\n\n\n\n"); return;
		};

		const auto new_line_str = std::string(num_newlines, '\n');
		print(new_line_str);
	};

	

	///////////////////////////////////
	// stdout

	auto printStdout(std::string_view message) noexcept -> void;

	template<class... Args>
	inline auto printStdout(std::format_string<Args...> fmt, Args&&... args) noexcept -> void {
		printStdout(std::format(fmt, args...));
	};

	inline auto printlnStdout(std::string_view message) noexcept -> void {
		printStdout("{}\n", message);
	};

	template<class... Args>
	inline auto printlnStdout(std::format_string<Args...> fmt, Args&&... args) noexcept -> void {
		printStdout(std::format(fmt, args...) + '\n');
	};


	inline auto printlnStdout() noexcept -> void {
		printStdout("\n");
	};

	inline auto printlnStdout(size_t num_newlines) noexcept -> void {
		switch(num_newlines){
			case 0: return;
			case 1: printStdout("\n"); return;
			case 2: printStdout("\n\n"); return;
			case 3: printStdout("\n\n\n"); return;
			case 4: printStdout("\n\n\n\n"); return;
			case 5: printStdout("\n\n\n\n\n"); return;
			case 6: printStdout("\n\n\n\n\n\n"); return;
			case 7: printStdout("\n\n\n\n\n\n\n"); return;
		};

		const auto new_line_str = std::string(num_newlines, '\n');
		printStdout(new_line_str);
	};



	///////////////////////////////////
	// stderr

	auto printStderr(std::string_view message) noexcept -> void;

	template<class... Args>
	inline auto printStderr(std::format_string<Args...> fmt, Args&&... args) noexcept -> void {
		printStderr(std::format(fmt, args...));
	};

	inline auto printlnStderr(std::string_view message) noexcept -> void {
		printStderr("{}\n", message);
	};

	template<class... Args>
	inline auto printlnStderr(std::format_string<Args...> fmt, Args&&... args) noexcept -> void {
		printStderr(std::format(fmt, args...) + '\n');
	};

	inline auto printlnStderr() noexcept -> void {
		printStderr("\n");
	};

	inline auto printlnStderr(size_t num_newlines) noexcept -> void {
		switch(num_newlines){
			case 0: return;
			case 1: printStderr("\n"); return;
			case 2: printStderr("\n\n"); return;
			case 3: printStderr("\n\n\n"); return;
			case 4: printStderr("\n\n\n\n"); return;
			case 5: printStderr("\n\n\n\n\n"); return;
			case 6: printStderr("\n\n\n\n\n\n"); return;
			case 7: printStderr("\n\n\n\n\n\n\n"); return;
		};

		const auto new_line_str = std::string(num_newlines, '\n');
		printStderr(new_line_str);
	};




	//////////////////////////////////////////////////////////////////////
	// style console

	namespace styleConsole{
		inline auto reset() noexcept -> void { printStdout("\033[0m"); };

		namespace text{
			inline auto white()   noexcept -> void { printStdout("\033[37m"); };
			inline auto gray()    noexcept -> void { printStdout("\033[90m"); };
			inline auto black()   noexcept -> void { printStdout("\033[30m"); };

			inline auto red()     noexcept -> void { printStdout("\033[31m"); };
			inline auto yellow()  noexcept -> void { printStdout("\033[33m"); };
			inline auto green()   noexcept -> void { printStdout("\033[32m"); };
			inline auto cyan()    noexcept -> void { printStdout("\033[36m"); };
			inline auto blue()    noexcept -> void { printStdout("\033[34m"); };
			inline auto magenta() noexcept -> void { printStdout("\033[35m"); };
		};

		namespace background{
			inline auto white()   noexcept -> void { printStdout("\033[47m"); };
			inline auto gray()    noexcept -> void { printStdout("\033[100m"); };
			inline auto black()   noexcept -> void { printStdout("\033[40m"); };

			inline auto red()     noexcept -> void { printStdout("\033[41m"); };
			inline auto yellow()  noexcept -> void { printStdout("\033[43m"); };
			inline auto green()   noexcept -> void { printStdout("\033[42m"); };
			inline auto cyan()    noexcept -> void { printStdout("\033[46m"); };
			inline auto blue()    noexcept -> void { printStdout("\033[44m"); };
			inline auto magenta() noexcept -> void { printStdout("\033[45m"); };
		};


		inline auto fatal() noexcept -> void {
			text::white();
			background::red();
		};

		inline auto error() noexcept -> void {
			background::black();
			text::red();
		};

		inline auto warning() noexcept -> void {
			background::black();
			text::yellow();
		};

		inline auto info() noexcept -> void {
			background::black();
			text::cyan();
		};

		inline auto success() noexcept -> void {
			background::black();
			text::green();
		};

		inline auto debug() noexcept -> void {
			background::black();
			text::magenta();
		};

		inline auto trace() noexcept -> void {
			background::black();
			text::gray();
		};
	};


	//////////////////////////////////////////////////////////////////////
	// print colors


	inline auto printWhite(std::string_view msg) noexcept -> void {
		styleConsole::text::white();
		print(msg);
		styleConsole::reset();
	};

	template<class... Args>
	inline auto printWhite(std::format_string<Args...> fmt, Args&&... args) noexcept -> void {
		styleConsole::text::white();
		print(fmt, args...);
		styleConsole::reset();
	};



	inline auto printGray(std::string_view msg) noexcept -> void {
		styleConsole::text::gray();
		print(msg);
		styleConsole::reset();
	};

	template<class... Args>
	inline auto printGray(std::format_string<Args...> fmt, Args&&... args) noexcept -> void {
		styleConsole::text::gray();
		print(fmt, args...);
		styleConsole::reset();
	};



	inline auto printBlack(std::string_view msg) noexcept -> void {
		styleConsole::text::black();
		print(msg);
		styleConsole::reset();
	};

	template<class... Args>
	inline auto printBlack(std::format_string<Args...> fmt, Args&&... args) noexcept -> void {
		styleConsole::text::black();
		print(fmt, args...);
		styleConsole::reset();
	};




	inline auto printRed(std::string_view msg) noexcept -> void {
		styleConsole::text::red();
		print(msg);
		styleConsole::reset();
	};

	template<class... Args>
	inline auto printRed(std::format_string<Args...> fmt, Args&&... args) noexcept -> void {
		styleConsole::text::red();
		print(fmt, args...);
		styleConsole::reset();
	};



	inline auto printYellow(std::string_view msg) noexcept -> void {
		styleConsole::text::yellow();
		print(msg);
		styleConsole::reset();
	};

	template<class... Args>
	inline auto printYellow(std::format_string<Args...> fmt, Args&&... args) noexcept -> void {
		styleConsole::text::yellow();
		print(fmt, args...);
		styleConsole::reset();
	};



	inline auto printGreen(std::string_view msg) noexcept -> void {
		styleConsole::text::green();
		print(msg);
		styleConsole::reset();
	};

	template<class... Args>
	inline auto printGreen(std::format_string<Args...> fmt, Args&&... args) noexcept -> void {
		styleConsole::text::green();
		print(fmt, args...);
		styleConsole::reset();
	};



	inline auto printCyan(std::string_view msg) noexcept -> void {
		styleConsole::text::cyan();
		print(msg);
		styleConsole::reset();
	};

	template<class... Args>
	inline auto printCyan(std::format_string<Args...> fmt, Args&&... args) noexcept -> void {
		styleConsole::text::cyan();
		print(fmt, args...);
		styleConsole::reset();
	};



	inline auto printBlue(std::string_view msg) noexcept -> void {
		styleConsole::text::blue();
		print(msg);
		styleConsole::reset();
	};

	template<class... Args>
	inline auto printBlue(std::format_string<Args...> fmt, Args&&... args) noexcept -> void {
		styleConsole::text::blue();
		print(fmt, args...);
		styleConsole::reset();
	};



	inline auto printMagenta(std::string_view msg) noexcept -> void {
		styleConsole::text::magenta();
		print(msg);
		styleConsole::reset();
	};

	template<class... Args>
	inline auto printMagenta(std::format_string<Args...> fmt, Args&&... args) noexcept -> void {
		styleConsole::text::magenta();
		print(fmt, args...);
		styleConsole::reset();
	};






	inline auto printlnWhite(std::string_view msg) noexcept -> void {
		styleConsole::text::white();
		println(msg);
		styleConsole::reset();
	};

	template<class... Args>
	inline auto printlnWhite(std::format_string<Args...> fmt, Args&&... args) noexcept -> void {
		styleConsole::text::white();
		println(fmt, args...);
		styleConsole::reset();
	};



	inline auto printlnGray(std::string_view msg) noexcept -> void {
		styleConsole::text::gray();
		println(msg);
		styleConsole::reset();
	};

	template<class... Args>
	inline auto printlnGray(std::format_string<Args...> fmt, Args&&... args) noexcept -> void {
		styleConsole::text::gray();
		println(fmt, args...);
		styleConsole::reset();
	};



	inline auto printlnBlack(std::string_view msg) noexcept -> void {
		styleConsole::text::black();
		println(msg);
		styleConsole::reset();
	};

	template<class... Args>
	inline auto printlnBlack(std::format_string<Args...> fmt, Args&&... args) noexcept -> void {
		styleConsole::text::black();
		println(fmt, args...);
		styleConsole::reset();
	};




	inline auto printlnRed(std::string_view msg) noexcept -> void {
		styleConsole::text::red();
		println(msg);
		styleConsole::reset();
	};

	template<class... Args>
	inline auto printlnRed(std::format_string<Args...> fmt, Args&&... args) noexcept -> void {
		styleConsole::text::red();
		println(fmt, args...);
		styleConsole::reset();
	};



	inline auto printlnYellow(std::string_view msg) noexcept -> void {
		styleConsole::text::yellow();
		println(msg);
		styleConsole::reset();
	};

	template<class... Args>
	inline auto printlnYellow(std::format_string<Args...> fmt, Args&&... args) noexcept -> void {
		styleConsole::text::yellow();
		println(fmt, args...);
		styleConsole::reset();
	};



	inline auto printlnGreen(std::string_view msg) noexcept -> void {
		styleConsole::text::green();
		println(msg);
		styleConsole::reset();
	};

	template<class... Args>
	inline auto printlnGreen(std::format_string<Args...> fmt, Args&&... args) noexcept -> void {
		styleConsole::text::green();
		println(fmt, args...);
		styleConsole::reset();
	};



	inline auto printlnCyan(std::string_view msg) noexcept -> void {
		styleConsole::text::cyan();
		println(msg);
		styleConsole::reset();
	};

	template<class... Args>
	inline auto printlnCyan(std::format_string<Args...> fmt, Args&&... args) noexcept -> void {
		styleConsole::text::cyan();
		println(fmt, args...);
		styleConsole::reset();
	};



	inline auto printlnBlue(std::string_view msg) noexcept -> void {
		styleConsole::text::blue();
		println(msg);
		styleConsole::reset();
	};

	template<class... Args>
	inline auto printlnBlue(std::format_string<Args...> fmt, Args&&... args) noexcept -> void {
		styleConsole::text::blue();
		println(fmt, args...);
		styleConsole::reset();
	};



	inline auto printlnMagenta(std::string_view msg) noexcept -> void {
		styleConsole::text::magenta();
		println(msg);
		styleConsole::reset();
	};

	template<class... Args>
	inline auto printlnMagenta(std::format_string<Args...> fmt, Args&&... args) noexcept -> void {
		styleConsole::text::magenta();
		println(fmt, args...);
		styleConsole::reset();
	};




	//////////////////////////////////////////////////////////////////////
	// logging

	namespace log{

		enum class Type{
			Fatal,
			Error,
			Warning,
			Success,
			Info,
			Debug,
			Trace,
		};

		struct Message{
			Type type;
			std::string_view str;
		};


		auto setCallback(const std::function<const Message&>& log_callback) noexcept -> void;
		auto setDefaultCallback() noexcept -> void;

		auto callCallback(const Message& msg) noexcept -> void;




		inline auto fatal(std::string_view message) noexcept -> void {
			callCallback(Message(Type::Fatal, message));
		};

		template<class... Args>
		inline auto fatal(std::format_string<Args...> fmt, Args&&... args) noexcept -> void {
			const std::string message = std::format(fmt, args...);
			fatal(message);
		};


		inline auto error(std::string_view message) noexcept -> void {
			callCallback(Message(Type::Error, message));
		};

		template<class... Args>
		inline auto error(std::format_string<Args...> fmt, Args&&... args) noexcept -> void {
			const std::string message = std::format(fmt, args...);
			error(message);
		};


		inline auto warning(std::string_view message) noexcept -> void {
			callCallback(Message(Type::Warning, message));
		};

		template<class... Args>
		inline auto warning(std::format_string<Args...> fmt, Args&&... args) noexcept -> void {
			const std::string message = std::format(fmt, args...);
			warning(message);
		};


		inline auto success(std::string_view message) noexcept -> void {
			callCallback(Message(Type::Success, message));
		};

		template<class... Args>
		inline auto success(std::format_string<Args...> fmt, Args&&... args) noexcept -> void {
			const std::string message = std::format(fmt, args...);
			success(message);
		};


		inline auto info(std::string_view message) noexcept -> void {
			callCallback(Message(Type::Info, message));
		};

		template<class... Args>
		inline auto info(std::format_string<Args...> fmt, Args&&... args) noexcept -> void {
			const std::string message = std::format(fmt, args...);
			info(message);
		};


		inline auto debug(std::string_view message) noexcept -> void {
			#if defined(EVO_CONFIG_DEBUG) || defined(EVO_NO_LOG_FILTER)
				callCallback(Message(Type::Debug, message));
			#endif
		};

		template<class... Args>
		inline auto debug(std::format_string<Args...> fmt, Args&&... args) noexcept -> void {
			#if defined(EVO_CONFIG_DEBUG) || defined(EVO_NO_LOG_FILTER)
				const std::string message = std::format(fmt, args...);
				debug(message);
			#endif
		};


		inline auto trace(std::string_view message) noexcept -> void {
			#if defined(EVO_CONFIG_DEBUG) || defined(EVO_NO_LOG_FILTER)
				#if !defined(EVO_NO_LOG_TRACE)
					callCallback(Message(Type::Trace, message));
				#endif
			#endif
		};

		template<class... Args>
		inline auto trace(std::format_string<Args...> fmt, Args&&... args) noexcept -> void {
			#if defined(EVO_CONFIG_DEBUG) || defined(EVO_NO_LOG_FILTER)
				#if !defined(EVO_NO_LOG_TRACE)
					const std::string message = std::format(fmt, args...);
					trace(message);
				#endif
			#endif
		};

	};


	//////////////////////////////////////////////////////////////////////
	// asserts, etc.

	inline auto Assert(bool conditional, std::string_view message) noexcept -> void {
		if(conditional == false){
			styleConsole::fatal();
			print(message);
			styleConsole::reset();
			breakpoint();
		}
	};



	inline auto debugAssert([[maybe_unused]] bool conditional, [[maybe_unused]] std::string_view message) noexcept -> void {
		#if defined(EVO_CONFIG_DEBUG)
			evo::Assert(conditional, message);
		#endif
	};


	
	// kept for backwards compatibility - deprecated
	#define EVO_FATAL_BREAK(msg) ::evo::fatalBreak(msg)


	EVO_NORETURN inline auto fatalBreak(std::string_view msg) noexcept -> void {
		styleConsole::fatal();
		println(msg);
		styleConsole::reset();

		#if defined(EVO_CONFIG_DEBUG)
			breakpoint();
			unreachable();
		#else
			std::exit(1);
		#endif
	};


	EVO_NORETURN inline auto debugFatalBreak([[maybe_unused]] std::string_view msg) noexcept -> void {
		#if defined(EVO_CONFIG_DEBUG)
			styleConsole::fatal();
			println(msg);
			styleConsole::reset();

			breakpoint();
		#endif

		unreachable();
	};

};

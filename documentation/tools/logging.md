# Logging
### tools/Logging.h


## Macro definitions

### EVO_NO_


## Functions

### print
```C++
// 1
auto print(std::string_view message) noexcept -> void;

// 2
template<class... Args>
inline auto print(std::format_string<Args...> fmt, Args&&... args) noexcept -> void;
```
Prints a message to the console. On Windows in debug mode, will also print to the debug console. Overload `2` is equivalent to calling `print(std::format(fmt, args...)`.


### println
```C++
// 1
auto println(std::string_view message) noexcept -> void;

// 2
template<class... Args>
inline auto println(std::format_string<Args...> fmt, Args&&... args) noexcept -> void;

// 3
inline auto println() noexcept -> void;

// 4
inline auto println(size_t num_newlines) noexcept -> void;
```
Print a message to the console and append a newline. On windows in debug mode, will also print to the debug console.

- overload 2: equivalent to `println(std::format(fmt, args)`
- overload 3: just prints a single `\n` character
- overload 4: prints a number of `\n` characters. Optimizes 0-7.






### printStdout
```C++
// 1
auto printStdout(std::string_view message) noexcept -> void;

// 2
template<class... Args>
inline auto printStdout(std::format_string<Args...> fmt, Args&&... args) noexcept -> void;
```
Prints a message to standard out. Overload `2` is equivalent to calling `printStdout(std::format(fmt, args...)`.


### printlnStdout
```C++
// 1
auto printlnStdout(std::string_view message) noexcept -> void;

// 2
template<class... Args>
inline auto printlnStdout(std::format_string<Args...> fmt, Args&&... args) noexcept -> void;

// 3
inline auto printlnStdout() noexcept -> void;

// 4
inline auto printlnStdout(size_t num_newlines) noexcept -> void;
```
Print a message to standard out and append a newline. 

- overload 2: equivalent to `printlnStdout(std::format(fmt, args)`
- overload 3: just prints a single `\n` character
- overload 4: prints a number of `\n` characters. Optimizes 0-7.





### printStderr
```C++
// 1
auto printStderr(std::string_view message) noexcept -> void;

// 2
template<class... Args>
inline auto printStderr(std::format_string<Args...> fmt, Args&&... args) noexcept -> void;
```
Prints a message to standard err. Overload `2` is equivalent to calling `printStderr(std::format(fmt, args...)`.


### printlnStderr
```C++
// 1
auto printlnStderr(std::string_view message) noexcept -> void;

// 2
template<class... Args>
inline auto printlnStderr(std::format_string<Args...> fmt, Args&&... args) noexcept -> void;

// 3
inline auto printlnStderr() noexcept -> void;

// 4
inline auto printlnStderr(size_t num_newlines) noexcept -> void;
```
Print a message to standard err and append a newline. 

- overload 2: equivalent to `printlnStdout(std::format(fmt, args)`
- overload 3: just prints a single `\n` character
- overload 4: prints a number of `\n` characters. Optimizes 0-7.






### print colors
```C++
auto printWhite(std::string_view message) noexcept -> void;

template<class... Args>
inline auto printWhite(std::format_string<Args...> fmt, Args&&... args) noexcept -> void;


auto printGray(std::string_view message) noexcept -> void;

template<class... Args>
inline auto printGray(std::format_string<Args...> fmt, Args&&... args) noexcept -> void;


auto printBlack(std::string_view message) noexcept -> void;

template<class... Args>
inline auto printBlack(std::format_string<Args...> fmt, Args&&... args) noexcept -> void;


auto printRed(std::string_view message) noexcept -> void;

template<class... Args>
inline auto printRed(std::format_string<Args...> fmt, Args&&... args) noexcept -> void;


auto printYellow(std::string_view message) noexcept -> void;

template<class... Args>
inline auto printYellow(std::format_string<Args...> fmt, Args&&... args) noexcept -> void;


auto printGreen(std::string_view message) noexcept -> void;

template<class... Args>
inline auto printGreen(std::format_string<Args...> fmt, Args&&... args) noexcept -> void;


auto printCyan(std::string_view message) noexcept -> void;

template<class... Args>
inline auto printCyan(std::format_string<Args...> fmt, Args&&... args) noexcept -> void;


auto printBlue(std::string_view message) noexcept -> void;

template<class... Args>
inline auto printBlue(std::format_string<Args...> fmt, Args&&... args) noexcept -> void;


auto printMagenta(std::string_view message) noexcept -> void;

template<class... Args>
inline auto printMagenta(std::format_string<Args...> fmt, Args&&... args) noexcept -> void;
```
Equivalent to calling `print`, but with a given color. Automatically calls `evo::styleConsole::reset()` at the end.




### println colors
```C++
auto printlnWhite(std::string_view message) noexcept -> void;

template<class... Args>
inline auto printlnWhite(std::format_string<Args...> fmt, Args&&... args) noexcept -> void;


auto printlnGray(std::string_view message) noexcept -> void;

template<class... Args>
inline auto printlnGray(std::format_string<Args...> fmt, Args&&... args) noexcept -> void;


auto printlnBlack(std::string_view message) noexcept -> void;

template<class... Args>
inline auto printlnBlack(std::format_string<Args...> fmt, Args&&... args) noexcept -> void;


auto printlnRed(std::string_view message) noexcept -> void;

template<class... Args>
inline auto printlnRed(std::format_string<Args...> fmt, Args&&... args) noexcept -> void;


auto printlnYellow(std::string_view message) noexcept -> void;

template<class... Args>
inline auto printlnYellow(std::format_string<Args...> fmt, Args&&... args) noexcept -> void;


auto printlnGreen(std::string_view message) noexcept -> void;

template<class... Args>
inline auto printlnGreen(std::format_string<Args...> fmt, Args&&... args) noexcept -> void;


auto printlnCyan(std::string_view message) noexcept -> void;

template<class... Args>
inline auto printlnCyan(std::format_string<Args...> fmt, Args&&... args) noexcept -> void;


auto printlnBlue(std::string_view message) noexcept -> void;

template<class... Args>
inline auto printlnBlue(std::format_string<Args...> fmt, Args&&... args) noexcept -> void;


auto printlnMagenta(std::string_view message) noexcept -> void;

template<class... Args>
inline auto printlnMagenta(std::format_string<Args...> fmt, Args&&... args) noexcept -> void;
```
Equivalent to calling `println`, but with a given color. Automatically calls `evo::styleConsole::reset()` at the end.


### Assert
```C++
inline auto Assert(bool conditional, CStrProxy message) noexcept -> void;

template<class... Args>
inline auto Assert(bool conditional, std::format_string<Args...> fmt, Args&&... args) noexcept -> void;
```
If `conditional` is false, print out the message in the "Fatal" style, and calls a breakpoint.


### debugAssert
```C++
inline auto debugAssert([[maybe_unused]] bool conditional, [[maybe_unused]] CStrProxy message) noexcept -> void;

template<class... Args>
inline auto debugAssert([[maybe_unused]] bool conditional, [[maybe_unused]] std::format_string<Args...> fmt, [[maybe_unused]] Args&&... args) noexcept -> void;
```
Calls `Assert(conditional, message)` in debug mode, otherwise is a no-op.



### fatalBreak
```C++
EVO_NORETURN inline auto fatalBreak(CStrProxy msg) noexcept -> void;

template<class... Args>
EVO_NORETURN inline auto fatalBreak(std::format_string<Args...> fmt, Args&&... args) noexcept -> void;
```
Prints the message to the console in the fatal style. Calls a breakpoint and marks unreachable in debug mode, otherwise calls `std::exit(1)`.

### debugFatalBreak
```C++
EVO_NORETURN inline auto debugFatalBreak(CStrProxy msg) noexcept -> void;

template<class... Args>
EVO_NORETURN inline auto debugFatalBreak(std::format_string<Args...> fmt, Args&&... args) noexcept -> void;
```
In debug mode, will print a message to the console in the fatal style, and calls a breakpoint. Both debug mode and release mode call unreachable.



### unimplemented
```C++
EVO_NORETURN inline auto unimplemented(const std::source_location location = std::source_location::current()) noexcept -> void;
EVO_NORETURN inline auto unimplemented(std::string_view message, const std::source_location location = std::source_location::current()) noexcept -> void;
```
Formats an unimplemented message and passes it to `debugAssert()`



## styleConsole namespace

### reset
```C++
inline auto reset() noexcept -> void;
```
Resets the console styling to default.


### log styling
```C++
inline auto fatal() noexcept -> void;
inline auto error() noexcept -> void;
inline auto warning() noexcept -> void;
inline auto info() noexcept -> void;
inline auto success() noexcept -> void;
inline auto debug() noexcept -> void;
inline auto trace() noexcept -> void;
```
Style the text / background based on logging styles.



### styleConsole::text namespace
```C++
inline auto white()   noexcept -> void;
inline auto gray()    noexcept -> void;
inline auto black()   noexcept -> void;

inline auto red()     noexcept -> void;
inline auto yellow()  noexcept -> void;
inline auto green()   noexcept -> void;
inline auto cyan()    noexcept -> void;
inline auto blue()    noexcept -> void;
inline auto magenta() noexcept -> void;
```
Change the color of the text in the console.


### styleConsole::background namespace
```C++
inline auto white()   noexcept -> void;
inline auto gray()    noexcept -> void;
inline auto black()   noexcept -> void;

inline auto red()     noexcept -> void;
inline auto yellow()  noexcept -> void;
inline auto green()   noexcept -> void;
inline auto cyan()    noexcept -> void;
inline auto blue()    noexcept -> void;
inline auto magenta() noexcept -> void;
```
Change the color of the text background in the console.


## log namespace

### Type
```C++
enum class Type{
	Fatal,
	Error,
	Warning,
	Success,
	Info,
	Debug,
	Trace,
};
```
Enum class for types of log messages.

### Message
```C++
struct Message{
	Type type;
	std::string_view str;
};
```
Data for a log message.


### hasCallback
```C++
EVO_NODISCARD auto hasCallback() noexcept -> bool;
```
Gets if a log callback is set.


### setCallback
```C++
auto setCallback(const std::function<const Message&>& log_callback) noexcept -> void;
```
Set the log callback.

### setDefaultCallback
```C++
auto setDefaultCallback() noexcept -> void;
```
Set the callback to the default.

### setDefaultThreadSafeCallback
```C++
auto setDefaultThreadSaferCallback() noexcept -> void;
```
Set the callback to the default (thread safer version). It is guaranteed to be safe if the only console manipulation done is through logging, but any outside manipulation may have negative effects.


### callCallback
```C++
auto callCallback(const Message& msg) noexcept -> void;
```
Make a call to the log callback.


### logging
```C++
inline auto fatal(std::string_view message) noexcept -> void;

template<class... Args>
inline auto fatal(std::format_string<Args...> fmt, Args&&... args) noexcept -> void;


inline auto error(std::string_view message) noexcept -> void;

template<class... Args>
inline auto error(std::format_string<Args...> fmt, Args&&... args) noexcept -> void;


inline auto warning(std::string_view message) noexcept -> void;

template<class... Args>
inline auto warning(std::format_string<Args...> fmt, Args&&... args) noexcept -> void;


inline auto success(std::string_view message) noexcept -> void;

template<class... Args>
inline auto success(std::format_string<Args...> fmt, Args&&... args) noexcept -> void;


inline auto info(std::string_view message) noexcept -> void;

template<class... Args>
inline auto info(std::format_string<Args...> fmt, Args&&... args) noexcept -> void;


inline auto debug(std::string_view message) noexcept -> void;

template<class... Args>
inline auto debug(std::format_string<Args...> fmt, Args&&... args) noexcept -> void;


inline auto trace(std::string_view message) noexcept -> void;

template<class... Args>
inline auto trace(std::format_string<Args...> fmt, Args&&... args) noexcept -> void;
```
Emit a log message to the log callback. In release mode, `debug` and `trace` do nothing. You can define `EVO_NO_LOG_FILTER` to keep these working in release mode. In addition, in debug mode you can define `EVO_NO_LOG_TRACE` to make trace logs do nothing.
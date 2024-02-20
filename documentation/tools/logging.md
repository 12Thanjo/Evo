# Logging
### tools/Logging.h


###### TODO: organize this better


## Functions

### log
```C++
auto log(CStrProxy message) noexcept -> void;
```
Log to the console.





### styleConsoleFatal
```C++
auto styleConsoleFatal() noexcept -> void;
```
The the style of logging to the console to be "Fatal" (White with Red background).


### styleConsoleError
```C++
auto styleConsoleError() noexcept -> void;
```
The the style of logging to the console to be "Error" (Red).


### styleConsoleWarning
```C++
auto styleConsoleWarning() noexcept -> void;
```
The the style of logging to the console to be "Warning" (Yellow).


### styleConsoleInfo
```C++
auto styleConsoleInfo() noexcept -> void;
```
The the style of logging to the console to be "Info" (Cyan).

### styleConsoleSuccess
```C++
auto styleConsoleSuccess() noexcept -> void;
```
The the style of logging to the console to be "Success" (Purple).

### styleConsoleDebug
```C++
auto styleConsoleDebug() noexcept -> void;
```
The the style of logging to the console to be "Debug" (Purple).


### styleConsoleTrace
```C++
auto styleConsoleTrace() noexcept -> void;
```
The the style of logging to the console to be "Trace" (gray).


### styleConsoleReset
```C++
auto styleConsoleReset() noexcept -> void;
```
The the style of logging to the console to be "Reset" (default).





### logFatal
```C++
inline auto logFatal(CStrProxy message) noexcept -> void;
```
Log to the console with the "Fatal" style, and automatically adds a newline.


### logError
```C++
inline auto logError(CStrProxy message) noexcept -> void;
```
Log to the console with the "Error" style, and automatically adds a newline.


### logWarning
```C++
inline auto logWarning(CStrProxy message) noexcept -> void;
```
Log to the console with the "Warning" style, and automatically adds a newline.


### logInfo
```C++
inline auto logInfo(CStrProxy message) noexcept -> void;
```
Log to the console with the "Info" style, and automatically adds a newline.


### logSuccess
```C++
inline auto logSuccess(CStrProxy message) noexcept -> void;
```
Log to the console with the "Success" style, and automatically adds a newline.


### logDebug
```C++
inline auto logDebug(CStrProxy message) noexcept -> void;
```
Log to the console with the "Debug" style, and automatically adds a newline. In release mode, these functions are no-op.


### logTrace
```C++
inline auto logTrace(CStrProxy message) noexcept -> void;
```
Log to the console with the "Trace" style, and automatically adds a newline. In release mode, these functions are no-op.






### Assert
```C++
inline auto Assert(bool conditional, CStrProxy message) noexcept -> void;
```
If `conditional` is false, print out the message in the "Fatal" style, and calls a breakpoint.


### debugAssert
```C++
inline auto debugAssert([[maybe_unused]] bool conditional, [[maybe_unused]] CStrProxy message) noexcept -> void;
```
Calls `Assert()` in debug mode, otherwise is a no-op.






## Macros

### EVO_FATAL_BREAK(msg)
Log fatal message, set a breakpoint, and mark unreachable
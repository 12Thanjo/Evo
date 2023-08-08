# Evo
My own custom standard library.

This is very much a work in progress.



[List of compiler flags / defines](#compiler-flags)

## Utils
- [assert.h](#assert)
- [numeric_types.h](#numeric_types)
- [platform_detection.h](#platform_detection)
- [select_size_type.h](#select_size_type)
- [strings.h](#strings)

## Containers
- [ArrayProxy](#array_proxy)
- [Flags](#flags)
- [StaticString](#static_string)
- [StaticVector](#static_vector)


## Tools
- [FS (File System)](#fs)
- [Logging](#logging)
- [Time](#time)



<a name="assert"></a>
### assert.h
Creates the following macros:

| Macro                               | Description                                                                   |
|-------------------------------------|-------------------------------------------------------------------------------|
| *EVO_ASSERT* (`conditional`)        | Runs a breakpoint if condition is not met                                     |
| *EVO_DEBUG_ASSERT* (`conditional`)  | Runs a breakpoint if condition is not met (only in [debug mode](#debug-mode)) |
| *EVO_STATIC_ASSERT* (`conditional`) | At compile time, errors if condition is not met                               |
| *EVO_BREAK* ()                      | Creates a debug breakpoint                                                    |


<a name="numeric_types"></a>
### numeric_types.h
Defines sized numeric types

| Type   | Description             | Alias for           |
|:------:|-------------------------|---------------------|
| `i8`   | 8-bit integer           | signed char         |
| `i16`  | 16-bit integer          | signed short        |
| `i16`  | 32-bit integer          | signed int          |
| `i16`  | 64-bit integer          | signed long long    |
| `ui8`  | 8-bit unsigned integer  | unsigned char       |
| `ui16` | 16-bit unsigned integer | unsigned short      |
| `ui16` | 32-bit unsigned integer | unsigned int        |
| `ui16` | 64-bit unsigned integer | unsigned long long  |
| `f32`  | 32-bit floating point   | float               |
| `f64`  | 64-bit floating point   | double              |
| `byte` | one single byte         | unsigned char / ui8 |


Uses the [`EVO_GLOBAL_NUMERIC_TYPES`](#global-numeric-types) flag.

<a name="platform_detection"></a>
### platform_detection.h
Detects the current platform and sets defines accordingly

#### Compiler
| Define               | Compiler |
|----------------------|----------|
| `EVO_COMPILER_MSVC`  | MSVC     |
| `EVO_COMPILER_CLANG` | Clang    |
| `EVO_COMPILER_GCC`   | GCC      |

#### OS/Platform
| Define                       | Platform      | Note                                                                        |
|------------------------------|---------------|-----------------------------------------------------------------------------|
| `EVO_PLATFORM_WINDOWS`       | Windows       |                                                                             |
| `EVO_PLATFORM_LINUX`         | Linux         |                                                                             |
| `EVO_PLATFORM_ANDROID`       | Android       | Will be set along with `EVO_PLATFORM_LINUX`								 |
| `EVO_PLATFORM_UNIX`          | Unix          | Will **not** be set along with `EVO_PLATFORM_LINUX` or `EVO_PLATFROM_APPLE` |
| `EVO_PLATFROM_APPLE`         | Apple         |               																 |
| `EVO_PLATFORM_IOS`           | IOS           | Will be set along with `EVO_PLATFORM_APPLE`								 |
| `EVO_PLATFORM_IOS_SIMULATOR` | IOS Simulator | Will be set along with `EVO_PLATFORM_APPLE` and `EVO_PLATFORM_IOS`          |
| `EVO_PLATFORM_MAC`           | MAC           | Will be set along with `EVO_PLATFORM_APPLE`                                 |



<a name="select_size_type"></a>
### select_size_type.h
###### TODO
Template meta-programming "magic" to select smallest unsigned integer type to hold a specific capacity or number of bits


<a name="strings"></a>
### strings.h
###### TODO
Various helper functions for c strings





<a name="array_proxy"></a>
### ArrayProxy
###### TODO
Designed to be a const reference to any array like type of data, and inteded for use as function parameters. It also supports the use of temporaries (such as st::initializer_list).


<a name="flags"></a>
### Flags
###### TODO
Bit flags container and various supporting functions


<a name="static_string"></a>
### StaticString
###### TODO
Non-allocating version of std::string (the data is stored in-place). 
It can support c-strings with no extra capacity needed. For example:
```c++
auto small_string = evo::StaticString<5>("Hello"); // uses a ui8 to represent current size
auto large_string = evo::StaticString<256>("World"); // uses a ui16 to represent current size

evo::print( std::format("'{}' (size {})", small_string.c_str(), sizeof(small_string)) ); // prints: "'Hello' (size 6)"
evo::print( std::format("'{}' (size {})", large_string.c_str(), sizeof(large_string)) ); // prints: "'World' (size 258)"
```


<a name="static_vector"></a>
### StaticVector
###### TODO
Non-allocating version of std::vector (the data is stored in-place)




<a name="fs"></a>
### File System (fs)
###### TODO
Interacting with the file system (for example, read/write files)


<a name="logging"></a>
### Logging
###### TODO
Enhanced logging


<a name="time"></a>
### Logging
###### TODO
Getting system time and type-safe unit number representations





<a name="compiler-flags"></a>
### Compiler Flags / defines
(By `true` or `false` I mean defined or undefined respectively)

|                                     Flag                       | Default | Description                                                                                                     |
|----------------------------------------------------------------|:-------:|-----------------------------------------------------------------------------------------------------------------|
| <a name="global-numeric-types"></a> `EVO_GLOBAL_NUMERIC_TYPES` | `false` | `true` means that numeric types are put into the global namespace, whereas `false` puts them in `Evo` namespace |
| <a name="debug-mode"></a>           `EVO_CONFIG_DEBUG`         | `false` | Sets whether to run in debug mode `true` or release mode `false`                                                |


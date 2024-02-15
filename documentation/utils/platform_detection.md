# Platform Detection
#### utils/platform_detection.h

Automatic definition of macros to help detect the current platform


## Compiler
Will error if it can't decect the compiler.
| Define               | Compiler |
|----------------------|----------|
| `EVO_COMPILER_MSVC`  | MSVC     |
| `EVO_COMPILER_CLANG` | Clang    |
| `EVO_COMPILER_GCC`   | GCC      |

## OS/Platform
Will error if it can't decect the OS/Platform.
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



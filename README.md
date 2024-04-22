# Evo
My own custom standard library. It's worked on as I want/need things, so it's by no means perfect, complete, or fully tested; I don't really expect others to be using it.

Requires at least C++20.

## API Docs:
[List of compiler flags / defines](#compiler-flags)

## Utils
- [assert.h](documentation/utils/asserts.md)
- [misc.h](documentation/utils/misc.md)
- [numeric_types.h](documentation/utils/numeric_types.md)
- [platform_detection.h](documentation/utils/platform_detection.md)
- [select_size_type.h](documentation/utils/select_size_type.md)
- [strings.h](documentation/utils/strings.md)

## Containers
- [ArrayProxy](documentation/containers/ArrayProxy.md)
- [Bimap](documentation/containers/Bimap.md)
- [CStrProxy](documentation/containers/CStrProxy.md)
- [Expected](documentation/containers/Expected.md)
- [Flags](documentation/containers/flags.md)
- [iterators](documentation/containers/iterators.md)
- [Result](documentation/containers/Result.md)
- [StaticString](documentation/containers/StaticString.md)
- [StaticVector](documentation/containers/StaticVector.md)

## Tools
- [FS (File System)](documentation/tools/fs.md)
- [Logging](documentation/tools/logging.md)
- [Random](documentation/tools/random.md)
- [Time](documentation/tools/time.md)



<a name="compiler-flags"></a>
### Compiler Flags / defines
(By `true` or `false` I mean defined or undefined respectively)

| Flag                       | Default | Description                                                                                                     |
|----------------------------|:-------:|-----------------------------------------------------------------------------------------------------------------|
| `EVO_GLOBAL_NUMERIC_TYPES` | `false` | `true` means that numeric types are put into the global namespace, whereas `false` puts them in `Evo` namespace |
| `EVO_CONFIG_DEBUG`         | `false` | Sets whether to run in debug mode `true` or release mode `false`                                                |


These are defined becasue they mess up Sublime's syntax highlighting otherwise
| Define          | Value           |
|-----------------|-----------------|
| `EVO_NODISCARD` | `[[nodiscard]]` |
| `EVO_NORETURN`  | `[[noreturn]]`  |



### Important note if using older versions:
`v1.4.0` contains breaking changes 


### Running the tests:
The test suite is not fully implemented, but if you would like to run it it is in the testing directory.
I using premake5 as my build system, but I had it generate make files in case you don't have and/or don't want to use premake5.
The test build system makefiles are also only setup for windows.

##### TODO: how to use testing suite
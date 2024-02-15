# Evo
My own custom standard library.

This is very much a work in progress.


### Running the tests:
The test suite is not fully implemented, but if you would like to run it it is in the testing directory.
I using premake5 as my build system, but I had it generate make files in case you don't have and/or don't want to use premake5.

##### TODO: how to use testing suite


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
- [ArrayProxy](documentation/containers/array_proxy.md)
- [Bimap](documentation/containers/Bimap.md)
- [CStrProxy](documentation/containers/CStrProxy.md)
- [Expected](documentation/containers/Expected.md)
- [Flags](documentation/containers/flags.md)
- [iterators](documentation/containers/iterators.md)
- [StaticString](documentation/containers/static_string.md)
- [StaticVector](documentation/containers/static_vector.md)

## Tools
- [FS (File System)](documentation/fs.md)
- [Logging](documentation/logging.md)
- [Time](documentation/time.md)




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

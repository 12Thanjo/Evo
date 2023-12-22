# Evo Change Log

### v1.0.21
- added `boolStr(bool) -> const char*` to utils/strings.h

### v1.0.20
- updated numeric types
	- added `f128`
	- added some of the upcomming float types (`float32_t`, `float64_t`, `float128_t`)
	- `EVO_GLOBAL_NUMERIC_TYPES` no longer removes the nuemric types from the `evo` namespace
	- Fixed the error messages in the static asserts to make sure the number types are the correct size

### v1.0.19
- Added 'isOctalNumber(char)'

### v1.0.18
- Added 'isHexNumber(char)'

### v1.0.17
- fixed name of `isAlphaNumeric()`

### v1.0.16
- fixed `fs::File::read()` (and similar functions) returning std::nullopt when a file was empty

### v1.0.15
- fixed `debugAssert(bool, CStrProxy)`

### v1.0.14
- Added `printCharName(char)`

### v1.0.13
- Added LICENSE

### v1.0.12
- Fixed finding location of defines.h in some compilers
- Added include for cmath

### v1.0.11
- Fixed printing to console of longer strings on Windows (only printed out max of 1024 characters)

### v1.0.10
- fixed the strings from read files being larger than the actual data

### v1.0.9
- fixed bug where reading large files failed

### v1.0.8
- Made `evo::unreachable()` constexpr

### v1.0.7
- Added `evo::unreachable()`

### v1.0.6
- fixed character intrinsics `evo::isWhitespace(char)` returning void instead of bool

### v1.0.5
- added character intrinsics

### v1.0.4
- added `[[maybe_unused]]` to `evo::debugAssert(bool, evo::CStrProxy)`

### v1.0.3
- fixed `evo::debugAssert(bool)`
- renamed `evo::assert` to `evo::Assert` to avoid clashing with the c `assert` macro
- fixed specializations of `std::advance`, `std::next`, and `std::prev` to work on MSVC

### v1.0.2
- Added missing headers
- Fixed ptr dereferencing in `StaticVector::resize(size_t)`

### v1.0.1
- Changed i32 / ui32 from `int` to `long` (for better compatability)

## v1.0.0
- Added CStrProxy
- Added more asserts, debug breaking, etc.
- Added new iterators classes (for contiguous/array-like data structures)
- Rewrote StaticVector to use C array instead of std::array


## Older
Older updates were not tracked by this file. Commit messages will describe the update
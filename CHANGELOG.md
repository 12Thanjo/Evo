# Evo Changelog

### v1.8.2
- Added unknown options for detection of compiler, platform, and architecture
- Fixed `SmallVector` properly resizing
- Removed invalid asserts from `SmallVector`

### v1.8.1
- Added detection of the ARM64 architecture

### v1.8.0
- Added architecture detection to plaform_detection.h

### v1.7.0
- Made the constructors/destructors of iterators `constexpr`
- Made `Bimap::get_left()` and `Bimap::get_right()` properly end with an unreachable
- Fixed `StaticVector` move constructors
- Added `SmallVector` container

### v1.6.0
- Added new container `Defer`

### v1.5.4
- Added formatting versions of `Assert()`, `debugAssert()`, `fatalBreak()`, and `debugFatalBreak()`

### v1.5.3
- Added proper forwarding of arguments in formatting printing / logging
- Added link to CHANGELOG in README

### v1.5.2
- Fixed `Assert()`  and `debugAssert()` not adding a newline to the message

### v1.5.1
- Fixed style codes showing up in the Windows debug console
- Added `printStdout()`, `printlnStdout()`, `printStderr()`, and `printlnStderr()`

### v1.5.0
- Major update to logging
- Removed the extraneous parameter in `StaticString::pop_back()`
- Added `CStrProxy::operator std::string_view`
- Added `CStrProxy::c_str()`
- Added `StaticString::operator std::string_view`

### v1.4.3
- Added `random01()`
- Added `randomBool()`

### v1.4.2
- Made `StaticVector` with non-default-constructable types
- Removed `StaticVector::operator std::span`

### v1.4.1
- Fixed ArrayProxy iterator dereferencing not being the correct const-ness

### v1.4.0
- Changed methods in `fs::File` and `fs::BinaryFile` that returned `std::optional` to now return `evo::Result`
- Changed `evo::stringsEqual()` to now return `evo::Result<bool>`
- Added to and reorganized README

### v1.3.1
- Fixed documentation links

### v1.3.0
- Added the `Result` container

### v1.2.5
- Fixed `fs::File::open()` and `fs::BinaryFile::open()` to not assert when just writing (not reading) to file that doesn't exist

### v1.2.4
- Fixed compile errors in `StaticString::append`
- Fixed various warnings throughout `StaticString`

### v1.2.3
- Fixed index types of `StaticVector::operator[]` to be intended
	- was causing improper overloading in MSVC

### v1.2.2
- Fixed `Flags` not compiling in certain conditions
- Added `styleConsoleSuccess()` and `logSuccess`
- Added random to tools

### v1.2.1
- Fixed Changelog
- Fixed broken links in documentation
- `printCharName(char)` now returns `{{??}}` if it recieves a negative char code
- Fixed missing `;` in asserts.h
- Fixed static_assert message in numeric_types.h (f128)
- Fixed including stdfloat before C++23
- Temporarily removed `f128` as MSVC does not support it yet
- Added `CapacityType_t` and `BitsSize_t`
- Fixed `Flags` not compiling on MSVC

### v1.2.0
- Fixed warnings for `printCharName(char)`
	- now returns `[[Extended-ASCII]]` if it recieves a negative char code
- Improved breakpoints in compilers other than MSVC
- Added `gdb` and `test` to build system
	- `gdb` compiles and opens gdb
	- `test` compiles and runs
- Added conversion operator from `Iterator<T>` to `ConstIterator<T>`
	- Also from `ReverseIterator<T>` to `ConstReverseIterator<T>`
- Added `Bimap` (bi-directional map)
- Updated README and greatly improved documentation
- Changed numeric types
	- Fixed numeric integer types to work on unix-type platforms
	- Fixed explicitly sized floating point types to check for C++23 or greater before putting into global namespace
- Changed `ArrayProxy`
	- Removed non-const iterators
	- Fixed the constructor that takes a `StaticVector` to take it by const reference
- Changed `StaticVector`
	- Fixed warnings for `StaticVector`
	- Fixed `StaticVector::pop_back()` to function like C++ standard
	- Fixed compile error in `StaticVector::emplace_back(Args&&...)`
	- Fixed compile error in `StaticVector::clear()`
	- Fixed compile error in `StaticVector::erase(const_iterator)`
	- Fixed the constructor that takes a `std::initializer_list`
	- Fixed `operator=` to no longer be `EVO_NODISCARD`
	- Fixed `back()` returning the element after it should
- Changed `Flags`
	- Changed default underlying type to `BitsSize<to_underlying(Enum::_max) - 1>::type`
	- Made `Flags` Constructors `EVO_NODISCARD`
	- Added `enum_t` member type
- Fixed `operator++(int)` of all iterators
- Changed `StaticString`
	- constructors are now `EVO_NODISCARD`
	- `operator=` now return `*this`
	- Fixed `back()` assuming the string is always at max capacity
- Changed FS 
	- Changed all use of `ui64` to `size_t`
	- Made `File::File()` `EVO_NODISCARD`
	- Added `File::getHandle()`

### v1.1.0
- Added Expected and Unexpected (versions of C++23's `expected` and `unexpected`)

### v1.0.22
- Added a version of C++23's `std::to_underlying`

### v1.0.21
- Added `boolStr(bool) -> const char*` to utils/strings.h

### v1.0.20
- updated numeric types
	- Added `f128`
	- Added a version of C++23's float types (`float32_t`, `float64_t`, `float128_t`)
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
Older updates were not tracked by this file. Commit messages will describe the respective update
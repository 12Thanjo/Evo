# Evo Changelog

### v1.28.0
- Added `ArrayProxy::operator==`

### v1.27.1
- Fixed assert firing incorrectly in `UnmovableVector` when the allocation size was >= 2^8

### v1.27.0
- Added specialization of `Expected<void, E>`

### v1.26.0
- Added conversion operators to `std::span` of `SmallVector`, `StaticVector`, and `UnmovableVector`

### v1.25.0
- Made the default held type of `Result` to be `void`
- Added `Result<void>::fromBool(bool is_success)`
- Fixed mistake in documentation for `Result`

### v1.24.3
- Fixed `SmallVector()::erase()` not always erasing the correct element

### v1.24.2
- Added the ability for `SmallVector` to be compiled with the element type being incomplete

### v1.24.1
- Fixed `SmallVector` reallocation not properly moving values to new buffer

### v1.24.0
- Overhaul of `SmallVector` implementation to improve the memory usage and performance
- Fixed debug assert in `StaticVector::resize()`

### v1.23.1
- Fixed various issues with constructors of `Expected`

### v1.23.0
- Added hashing of `SmallVector`
- Added hashing of `StaticVector`
- Added hashing of `UnmovableVector`

### v1.22.0
- Added `copy()`

### v1.21.0
- Added `copy()`

### v1.20.0
- Added `Unmovable::resize()`

### v1.19.4
- Fixed fatal error in `SmallVector::erase()` when is big and erasing the last element

### v1.19.3
- Fixed `Expected::operator->()`

### v1.19.2
- Fixed `StaticVector::erase()` and `SmallVector::erase()` calling a destructor incorrectly
- Removed nodiscard attribute from `Expected::~Expected`

### v1.19.1
- Added destructor for `Expected`

### v1.19.0
- Added `bitCast()` and `unsafeBitCast()`
- Made `hashCombine()` nodiscard

### v1.18.3
- Made all iterators conform to the `std::bidirectional_iterator` concept

### v1.18.2
- Added `inBounds()` to all iterators
- Added iterator debug in-bounds checking for `StaticVector` and `SmallVector`
- Modified documentation of `StaticVector::clear()` to add the sentance "Unlike `std::vector::clear()`, this also de-allocates".

### v1.18.1
- Fixed some warnings on `MSVC` for `StaticVector::resize()`

### v1.18.0
- Added `UnmovableVector`
- Added `lldb` target to build system
- Fixed `StaticVector::max_size()` not always giving the correct value

### v1.17.1
- Fixed `SmallVector::erase()`
- Fixed `StaticVector::erase()`

### v1.17.0
- Added support for `Result<void>`
- Fixed `Result::error()`

### v1.16.2
- Fixed r-value reference versions of `Result::value()`

### v1.16.1
- Made the default constructor of `SmallVector` constexpr

### v1.16.0
- Added convenience functions to the `fs` namespace
	- `readFile`
	- `readBinaryFile`
	- `writeFile`
	- `writeBinaryFile`

### v1.15.1
- Fixed `ArrayProxy::front()` and `ArrayProxy::back()` to return references, not pointers
- Fixed there being two separate definitions of the dyn_lib macros

### v1.15.0
- Added utils/dyn_lib.h

### v1.14.20
- Fixed `Variant` not always constructing properly

### v1.14.19
- Added r-value-reference versions of `Result::value()`

### v1.14.18
- Added `operator==` and `operator!=` to `Flags`, `SmallVector`, and `StaticVector`

### v1.14.17
- Fixed incorrect behaviour with `StaticVector` constructors with trivially movable types
	- Incorrect arithemtic was causing overwrites

### v1.14.16
- Fixed fatal error when calling `StaticVector::operator=` with non-trivially-copyable types

### v1.14.15
- Added comparison operators to `time::Nanoseconds`, `time::Milliseconds`, and `time::Seconds`

### v1.14.14
- Added small optimization to `SmallVector` when going from small buffer to big

### v1.14.13
- Fixed crashes for `StaticVector` and `SmallVector` when copying with non-trivially copyable elements

### v1.14.12
- Fixed compile errors on Clang and GCC
- Fixed incorrect behaviour with `StaticVector` constructors with trivially movable types
- Fixed incorrect behaviour with `SmallVector` constructors with types that are trivially constructable and moveable

### v1.14.11
- Fixed compile errors caused by updates to MSVC (string formatting of time objects)

### v1.14.10
- Fixed compile errors caused by updates to MSVC

### v1.14.9
- Added some optimizations to `StaticVector` and `SmallVector` based on type traits
	- optimize moves and copies to `std::memcpy()` if possible

### v1.14.8
- Added copy and move constructors for `Result`

### v1.14.7
- Improved the performance of `isAlphaNumeric()` and `isLetter()`

### v1.14.6
- Fixed `std::initializer_list` constructors of `StaticVector` incorrectly asserting when the size of the `std::initializer_list` is exactly the capacity of the `StaticVector`

### v1.14.5
- Fixed warnings when creating `StaticVector` with the `std::initializer_list` constructor

### v1.14.4
- Added `SmallVector` default SMALL_CAPACITY
- Removed warning for `SmallVector` of below optimal SMALL_CAPACITY

### v1.14.3
- Fixed the non-const version of `Result::value()` to actually return a non-const-reference

### v1.14.2
- Added `log::setDefaultThreadSaferCallback()`

### v1.14.1
- Removed warnings from `debug()` and `trace()` when they are no-ops

### v1.14.0
- Added Linux support for testing build system
- Fixed compiling of `print()` on non-Windows platforms

### v1.13.3
- Fixed improperly setting of some `Windows.h` macros

### v1.13.2
- Fixed `SmallVector` incorrectly warning about size

### v1.13.1
- Added implementation of standard hash for `Variant`

### v1.13.0
- Added `hashCombine`

### v1.12.0
- Fixed `std::prev` for evo iterators
- Changed ArrayProxy to use evo iterators

### v1.11.0
- Added constructors for `StaticVector` and `SmallVector` from iterators
- Added `SmallVector::reserve()`

### v1.10.0
- Added `EVO_CONCAT` macro

### v1.9.6
- Added `Variant::visit()`

### v1.9.5
- Fixed `SmallVector` incorrectly warning about size
- Fixed `SmallVector` inserting / emplacing when switching from internal buffer to heap

### v1.9.4
- Fixed `SmallVector::insert`

### v1.9.3
- Fixed reverse iteration for `StaticVector` and `SmallVector`

### v1.9.2
- Changed the `SmallVector` too small error to be a warning

### v1.9.1
- Fixed some warnings for `StaticVector`

### v1.9.0
- Added `Variant`

### v1.8.2
- Added unknown options for detection of compiler, platform, and architecture
- Fixed `SmallVector` properly resizing
- Removed invalid asserts from `SmallVector`

### v1.8.1
- Added detection of the ARM64 architecture

### v1.8.0
- Added architecture detection to platform_detection.h

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
- `printCharName(char)` now returns `{{??}}` if it receives a negative char code
- Fixed missing `;` in asserts.h
- Fixed static_assert message in numeric_types.h (f128)
- Fixed including `stdfloat` before C++23
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
	- `EVO_GLOBAL_NUMERIC_TYPES` no longer removes the numeric types from the `evo` namespace
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
- Added include for `cmath`

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
- Changed i32 / ui32 from `int` to `long` (for better compatibility)

## v1.0.0
- Added CStrProxy
- Added more asserts, debug breaking, etc.
- Added new iterators classes (for contiguous/array-like data structures)
- Rewrote StaticVector to use C array instead of std::array


## Older
Older updates were not tracked by this file. Commit messages will describe the respective update
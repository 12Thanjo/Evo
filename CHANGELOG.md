# Evo Change Log

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
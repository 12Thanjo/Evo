# Misc
#### utils/misc.h

Miscellaneous functions

### Vector Deallocation
```C++
template<typename T>
inline auto vector_dealloc(std::vector<T>& vec) noexcept -> void;
```
Clears and shrinks the vector


### unreachable:
```C++
EVO_NORETURN constexpr auto unreachable() noexcept -> void;
```
Similar to C++23's `std::unreachable`, it tells the compiler that a certain section / branch of code is unreachable.



### to underlying:
```C++
template<class Enum>
EVO_NODISCARD constexpr auto to_underlying(Enum e) noexcept -> std::underlying_type_t<Enum>;
```
Converts an enum value to its underyling integer type. This is an implementation of C++23's `std::to_underlying`


### hashCombine:
```C++
constexpr auto hashCombine(size_t lhs, size_t rhs) noexcept -> size_t;
constexpr auto hashCombine(std::initializer_list<size_t> list) noexcept -> size_t;
```
Combine a number of hashes
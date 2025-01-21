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



### to_underlying:
```C++
template<class Enum>
EVO_NODISCARD constexpr auto to_underlying(Enum e) noexcept -> std::underlying_type_t<Enum>;
```
Converts an enum value to its underyling integer type. This is an implementation of C++23's `std::to_underlying`.


### copy:
```C++
template<class T>
EVO_NODISCARD constexpr auto copy(const T& value) noexcept -> T;
```
Copyies the value given.


### hashCombine:
```C++
EVO_NODISCARD constexpr auto hashCombine(size_t lhs, size_t rhs) noexcept -> size_t;
EVO_NODISCARD constexpr auto hashCombine(std::initializer_list<size_t> list) noexcept -> size_t;
```
Combine a number of hashes



### bitCast:
```C++
template<class TO, class FROM>
EVO_NODISCARD constexpr auto bitCast(const FROM& from) -> const TO&;

template<class TO, class FROM>
EVO_NODISCARD constexpr auto bitCast(FROM& from) -> TO&;
```
Alternative to `std::bit_cast`. Requires that `FROM` and `TO` to have the same size and `FROM` to be trivially destructible.


### unsafeBitCast:
```C++
template<class TO, class FROM>
EVO_NODISCARD constexpr auto unsafeBitCast(const FROM& from) -> const TO&;

template<class TO, class FROM>
EVO_NODISCARD constexpr auto unsafeBitCast(FROM& from) -> TO&;
```
Alternative to `std::bit_cast`. Requires that `FROM` and `TO` to have the same size.
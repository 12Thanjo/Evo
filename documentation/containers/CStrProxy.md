# CStrProxy
#### containers/CStrProxy.h

```C++
template<typename T>
class CStrProxy;
```

An interface for a read-only null-terminated character array. This is intended for use as a function parameter.






## Member Functions

### Constructors
```C++
[[nodiscard]] constexpr CStrProxy(char character) noexcept; // just a single character
[[nodiscard]] constexpr CStrProxy(const char* str) noexcept; // null-terminated character array
[[nodiscard]] constexpr CStrProxy(const std::string& str) noexcept;

template<size_t CAPACITY>
[[nodiscard]] constexpr CStrProxy(const StaticString<CAPACITY>& str) noexcept;
```

### Type conversion
```C++
[[nodiscard]] constexpr operator std::string_view() const noexcept;
```


### Data
```C++
[[nodiscard]] constexpr auto data() const noexcept -> const char*;
```
Get a pointer to the beginning to the string.


### c_str
```C++
[[nodiscard]] constexpr auto c_str() const noexcept -> const char*;
```
Get c-string from the data (equivalent to calling `data()`).


### Helper Classes
```C++
template<>
struct std::hash<evo::CStrProxy>;

template<>
struct std::formatter<evo::CStrProxy>;
```


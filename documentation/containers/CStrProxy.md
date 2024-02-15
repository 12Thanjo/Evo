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
EVO_NODISCARD constexpr CStrProxy(char character) noexcept; // just a single character
EVO_NODISCARD constexpr CStrProxy(const char* str) noexcept; // null-terminated character array
EVO_NODISCARD constexpr CStrProxy(const std::string& str) noexcept;

template<size_t CAPACITY>
EVO_NODISCARD constexpr CStrProxy(const StaticString<CAPACITY>& str) noexcept;
```

### Data
```C++
EVO_NODISCARD constexpr auto data() const noexcept -> const char*;
```
Get a pointer to the beginning to the string.


### Helper Classes
```C++
template<>
struct std::hash<evo::CStrProxy>;

template<>
struct std::formatter<evo::CStrProxy>;
```


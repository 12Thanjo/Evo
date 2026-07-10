# containers/Flags.h


## Classes

### [Flags](Flags_type.md)


## Functions

### bitFlag
```C++
template<typename T>
[[nodiscard]] constexpr auto bitFlag(T flag) noexcept -> T;
```
Takes the flag position `flag` and returns a value with that bit set to 1 (with the rest being 0)


### createFlagMask
```C++
template<typename T, typename UnderlyingT>
[[nodiscard]] constexpr auto flagMask(std::initializer_list<T> list) noexcept -> UnderlyingT;
```
Takes every number in `list` and makes a flag mask with those bits set



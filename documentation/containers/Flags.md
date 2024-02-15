# containers/Flags.h


## Classes

### [Flags](Flags_type.md)


## Functions

### bitFlag
```C++
template<typename T>
EVO_NODISCARD constexpr auto bitFlag(T flag) noexcept -> T;
```
Takes the flag position `flag` and returns a value with that bit set to 1 (with the rest being 0)


### createFlagMask
```C++
template<typename T, typename UnderlyingT>
EVO_NODISCARD constexpr auto flagMask(std::initializer_list<T> list) noexcept -> UnderlyingT;
```
Takes every number in `list` and makes a flag mask with those bits set



# Variant
#### containers/Variant.h

```C++
template<class... Ts>
class Variant : public std::variant<Ts...>;
```

Container to add a nicer interface over std::variant.




## Template Parameters

| Template | Description                            |
|:--------:|----------------------------------------|
| Ts...    | Possible types for the variant to hold |



## Member Functions

### is
```C++
template<class T>
EVO_NODISCARD constexpr auto is() const noexcept -> bool;
```
Check if the variant is holding a given type.


### as
```C++
template<class T>
EVO_NODISCARD constexpr auto as() noexcept -> T&;

template<class T>
EVO_NODISCARD constexpr auto as() const noexcept -> const T&;
```
Get the currently held value.



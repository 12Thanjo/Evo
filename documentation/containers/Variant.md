# Variant
#### containers/Variant.h

```C++
template<class... Ts>
class Variant : public std::variant<Ts...>;
```

Container to add a nicer interface over `std::variant`. It inherits from `std::variant`.




## Template Parameters

| Template | Description                            |
|:--------:|----------------------------------------|
| Ts...    | Possible types for the variant to hold |



## Member Functions

### getNative
```C++
[[nodiscard]] constexpr auto getNative() const&  noexcept -> const std::variant<Ts...>&;
[[nodiscard]] constexpr auto getNative()      &  noexcept ->       std::variant<Ts...>&;
[[nodiscard]] constexpr auto getNative()      && noexcept ->       std::variant<Ts...>&&;
```
Get the native C++ standard library version of the variant.


### is
```C++
template<class T>
[[nodiscard]] constexpr auto is() const noexcept -> bool;
```
Check if the variant is holding a given type.


### as
```C++
template<class T>
[[nodiscard]] constexpr auto as() const& noexcept -> const T&;

template<class T>
[[nodiscard]] constexpr auto as() & noexcept -> T&;

template<class T>
[[nodiscard]] constexpr auto as() && noexcept -> T&&;
```
Get the currently held value.



### visit
```C++
[[nodiscard]] constexpr auto visit(auto callable) noexcept;
[[nodiscard]] constexpr auto visit(auto callable) const noexcept;
```
Make a call to `std::visit` on the native variant




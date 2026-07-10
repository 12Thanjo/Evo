# Unexpected
#### containers/Expected.h

```C++
template<class E>
class Unexpected;
```

Used for to set the error value in the constructor of an [`Expected`](Expected_type.md).

This is a simplified version of C++23's `std::unexpected`.



## Template Parameters

| Template | Description         |
|:--------:|---------------------|
|    E	   | Type of error value |



## Member Functions

### Constructors
```C++
[[nodiscard]] constexpr Unexpected(const Unexpected&);
[[nodiscard]] constexpr Unexpected(Unexpected&&);

[[nodiscard]] constexpr explicit Unexpected(const E& val);
[[nodiscard]] constexpr explicit Unexpected(E&& val);
```


### error
```C++
[[nodiscard]] constexpr auto error()       noexcept ->       E&;
[[nodiscard]] constexpr auto error() const noexcept -> const E&;
```
Get the error value



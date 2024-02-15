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
EVO_NODISCARD constexpr Unexpected(const Unexpected&);
EVO_NODISCARD constexpr Unexpected(Unexpected&&);

EVO_NODISCARD constexpr explicit Unexpected(const E& val);
EVO_NODISCARD constexpr explicit Unexpected(E&& val);
```


### error
```C++
EVO_NODISCARD constexpr auto error()       noexcept ->       E&;
EVO_NODISCARD constexpr auto error() const noexcept -> const E&;
```
Get the error value



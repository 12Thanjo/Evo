# Expected
#### containers/Expected.h

```C++
template<class T, class E>
class Expected;
```

A tool to hold two types of values: expected and error. This is designed for returning from functions (return value / error value). This type does not dynamically allocate unless the default constructor is called and the expected type's default constructor dynamically allocates. There is also a specialization for `T = void`.

This is a simplified version of C++23's `std::expected`.



## Template Parameters

| Template | Description            |
|:--------:|------------------------|
|    T	   | Type of expected value |
|    E	   | Type of error value    |


## Member Types

| Member Type              | Definition      |
|--------------------------|-----------------|
| value_type 			   | `T`			 |
| error_type 			   | `E` 			 |
| unexpected_type 		   | `Unexpected<E>` |			


## Member Functions

### Constructors
```C++
[[nodiscard]] constexpr Expected() noexcept;

[[nodiscard]] constexpr Expected(const Expected& rhs) noexcept;
[[nodiscard]] constexpr Expected(Expected&& rhs) noexcept;

// Expected
[[nodiscard]] constexpr Expected(const T& val) noexcept;
[[nodiscard]] constexpr Expected(T&& val) noexcept;

// Unexpected (error)
[[nodiscard]] constexpr Expected(const Unexpected<E>& val) noexcept;
[[nodiscard]] constexpr Expected(Unexpected<E>&& val) noexcept;
```

### operator=
```C++
constexpr auto operator=(const Expected& rhs) noexcept -> Expected;
constexpr auto operator=(Expected&& rhs) noexcept -> Expected;
```


### Observers

#### Dereference
```C++
[[nodiscard]] constexpr auto operator->()       noexcept ->       T*;
[[nodiscard]] constexpr auto operator->() const noexcept -> const T*;

[[nodiscard]] constexpr auto operator*()       noexcept ->       T&;
[[nodiscard]] constexpr auto operator*() const noexcept -> const T&;
```

#### has_value
```C++
[[nodiscard]] constexpr auto has_value() const noexcept -> bool;
```
Check if it holds a value. Returns true if it has the expected value, returns false if it has the error value.


#### value
```C++
[[nodiscard]] constexpr auto value()       noexcept ->       T&;
[[nodiscard]] constexpr auto value() const noexcept -> const T&;
```
Get the expected value


#### error
```C++
[[nodiscard]] constexpr auto error()       noexcept ->       E&;
[[nodiscard]] constexpr auto error() const noexcept -> const E&;
```
Get the error value



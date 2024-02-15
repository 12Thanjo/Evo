# Expected
#### containers/Expected.h

```C++
template<class T, class E>
class Expected;
```

A tool to hold two types of values: expected and error. This is designed for returning from functions (return value / error value). This type does not dynamically allocate unless the default constructor is called and the expected type's default constructor dynamically allocates.

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
EVO_NODISCARD constexpr Expected() noexcept;

EVO_NODISCARD constexpr Expected(const Expected& rhs) noexcept;
EVO_NODISCARD constexpr Expected(Expected&& rhs) noexcept;

// Expected
EVO_NODISCARD constexpr Expected(const T& val) noexcept;
EVO_NODISCARD constexpr Expected(T&& val) noexcept;

// Unexpected (error)
EVO_NODISCARD constexpr Expected(const Unexpected<E>& val) noexcept;
EVO_NODISCARD constexpr Expected(Unexpected<E>&& val) noexcept;
```

### operator=
```C++
constexpr auto operator=(const Expected& rhs) noexcept -> Expected;
constexpr auto operator=(Expected&& rhs) noexcept -> Expected;
```


### Observers

#### Dereference
```C++
EVO_NODISCARD constexpr auto operator->()       noexcept ->       T*;
EVO_NODISCARD constexpr auto operator->() const noexcept -> const T*;

EVO_NODISCARD constexpr auto operator*()       noexcept ->       T&;
EVO_NODISCARD constexpr auto operator*() const noexcept -> const T&;
```

#### has_value
```C++
EVO_NODISCARD constexpr auto has_value() const noexcept -> bool;
```
Check if it holds a value. Returns true if it has the expected value, returns false if it has the error value.


#### value
```C++
EVO_NODISCARD constexpr auto value()       noexcept ->       T&;
EVO_NODISCARD constexpr auto value() const noexcept -> const T&;
```
Get the expected value


#### error
```C++
EVO_NODISCARD constexpr auto error()       noexcept ->       E&;
EVO_NODISCARD constexpr auto error() const noexcept -> const E&;
```
Get the error value



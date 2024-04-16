# Result
#### containers/Result.h

```C++
template<class T>
class Result;
```

A type designed for returning values from functions with a clearer API than just using `std::optional`. For errors, instead of returning `std::nullopt`, you return `evo::ResultError` instead.

```C++
auto some_func() noexcept -> evo::Result<int> {
	const bool errored = some_func_that_may_error();

	if(errored){
		return 12;
	}else{
		return evo::ResultError;
	}
};
```



## Template Parameters

| Template | Description                    |
|:--------:|--------------------------------|
| CAPACITY | Maximum capacity of the string |



## Member Functions

### Constructors / creators
```C++
// Success
EVO_NODISCARD constexpr Result(const T& value) noexcept;
EVO_NODISCARD constexpr Result(T&& value) noexcept;
EVO_NODISCARD constexpr Result(ResultError) noexcept;

// Error
EVO_NODISCARD static constexpr auto error() noexcept -> Result;
```

## Checking Result

### isSuccess
```C++
EVO_NODISCARD inline constexpr auto isSuccess() const noexcept -> bool;
```
Get if there no error occured in the function


### isError
```C++
EVO_NODISCARD inline constexpr auto isError() const noexcept -> bool;
```
Get if there was an error that occured in the function


## value
```C++
EVO_NODISCARD inline constexpr auto value() const noexcept -> const T&;
EVO_NODISCARD inline constexpr auto value() noexcept -> T&;
```
Get the return value (only present if `isSuccess() == true`)


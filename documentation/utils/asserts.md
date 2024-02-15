# Asserts
### utils/asserts.h

Asserts and breakpoints.



## Macros:

| Macro                               | Description                                                                   |
|-------------------------------------|-------------------------------------------------------------------------------|
| *EVO_ASSERT* (`conditional`)        | Runs a breakpoint if condition is not met                                     |
| *EVO_DEBUG_ASSERT* (`conditional`)  | Runs a breakpoint if condition is not met (only in [debug mode](#debug-mode)) |
| *EVO_STATIC_ASSERT* (`conditional`) | At compile time, errors if condition is not met                               |
| *EVO_BREAK* ()                      | Creates a debug breakpoint                                                    |




## Functions:

### Breakpoint:
```C++
inline auto breakpoint() noexcept -> void;
```
In debug mode (`EVO_CONFIG_DEBUG`), calls a breapoint (`EVO_BREAK()`). Otherwise it will call `std::exit(EXIT_FAILURE)`.


### Assert:
```C++
inline auto Assert(bool conditional) noexcept -> void;
```
If conditional is `false`, call `evo::breakpoint()`.



### debugAssert:
```C++
inline auto debugAssert([[maybe_unused]] bool conditional) noexcept -> void;
```
In debug mode (`EVO_CONFIG_DEBUG`), if conditional is `false`, call `evo::breakpoint()`.

# Flags
#### containers/Flags.h

```C++
template<typename Enum, typename UnderlyingT = BitsSize<to_underlying(Enum::_max) - 1>::type>
class Flags;
```

A convienence tool for managing flag masks. Takes in an enum to manage the flag indices.

Here's an example of a supported enum:
```C++
enum class Direction{
	Up,
	Down,
	Left,
	Right,

	_max,
};
```
Note how the last value (and greatest) is `_max`.




## Template Parameters

| Template    | Description                    |
|:-----------:|--------------------------------|
|   Enum      | The enum for the bit indices   |
| UnderlyingT | Type of the underlying integer |


## Member Types

| Member Type  | Definition                                    |
|--------------|-----------------------------------------------|
| enum_t	   | The enum type (alias for `Enum`)              |
| underlying_t | The underlying type (alias for `UnderlyingT`) |


## Member Functions

### Constructors
```C++
EVO_NODISCARD constexpr Flags() noexcept; // defaults to all flags 0

EVO_NODISCARD constexpr Flags(Enum flag) noexcept; // sets a single flag

EVO_NODISCARD constexpr Flags(std::initializer_list<Enum> flags) noexcept; // sets each flag from list
```


### Modifiers

#### set
```C++
constexpr auto set(Enum flag_value) noexcept -> void;
constexpr auto set(std::initializer_list<Enum> flag_values) noexcept -> void;
```
Set given flag values (make the value `1`).


#### unset
```C++
constexpr auto unset(Enum flag_value) noexcept -> void;
constexpr auto unset(std::initializer_list<Enum> flag_values) noexcept -> void;
```
Unset given flag values (make the value `0`).


#### clear
```C++
constexpr auto clear() noexcept -> void;
```
Makes all flag values to `0`.


#### toggle
```C++
constexpr auto toggle(Enum flag_value) noexcept -> void;
constexpr auto toggle(std::initializer_list<Enum> flag_values) noexcept -> void;
```
Toggle given flag values.



### Lookup

#### has
```C++
EVO_NODISCARD constexpr auto has(Enum flag_value) noexcept -> bool;
EVO_NODISCARD constexpr auto has(std::initializer_list<Enum> flag_values) noexcept -> bool;
```
Checks if given flag values are set.


#### hasNone
```C++
EVO_NODISCARD constexpr auto hasNone() const noexcept -> bool;
```
Checks if all flag values are unset.



### Underlying

#### value
```C++
EVO_NODISCARD constexpr auto value() const noexcept -> UnderlyingT;
```
Returns the underlying integer value.
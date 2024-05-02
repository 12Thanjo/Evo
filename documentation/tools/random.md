# Random
#### tools/random.h


## Functions

### random
```C++
EVO_NODISCARD auto random() noexcept -> ui64;
EVO_NODISCARD auto random(ui64 max) noexcept -> ui64;
EVO_NODISCARD auto random(ui64 min, ui64 max) noexcept -> ui64;
```
Provides a random number using a 64-bit Mersenne Twister (`std::mt19937_64`). Note: while this is much better than just using `::rand()`, it is not cryptographically secure.


### random01
```C++
EVO_NODISCARD auto random01() noexcept -> f64;
```
Gets a random number between 0-1. Uses `evo::random()` under the hood, so it is not cryptographically secure.


### randomBool
```C++
EVO_NODISCARD auto randomBool() noexcept -> bool;
```
Gets a random bool value. Uses `evo::random()` under the hood, so it is not cryptographically secure.
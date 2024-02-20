# Random
#### tools/random.h


## Functions

### Random
```C++
EVO_NODISCARD auto random() noexcept -> ui64;
EVO_NODISCARD auto random(ui64 max) noexcept -> ui64;
EVO_NODISCARD auto random(ui64 min, ui64 max) noexcept -> ui64;
```
Provides a random number using a 64-bit Mersenne Twister (`std::mt19937_64`). Note: while this is much better than just using `::rand()`, it is not cryptographically secure.

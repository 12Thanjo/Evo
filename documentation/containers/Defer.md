# Defer
#### containers/Defer.h

```C++
class Defer;
```

Run a function at the end of the scope.


## Member Functions

### Constructors
```C++
EVO_NODISCARD Defer(std::function<void()>&& defer_callback) noexcept;
EVO_NODISCARD Defer(const std::function<void()>& defer_callback) noexcept;

Defer(const Defer&) = delete;
Defer(Defer&&) = delete;
```


## Macros

### EVO_DEFER
```C++
#define EVO_DEFER(callback) ::evo::Defer _evo_defer_num ## __COUNTER__ = ::evo::Defer(callback)
```
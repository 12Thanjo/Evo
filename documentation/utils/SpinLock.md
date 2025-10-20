# SpinLock
#### utils/SpinLock.h

Implementation of a spin lock. This is a drop-in replacement for `std::mutex` and `std::shared_mutex` as it tested faster than both.


### lock
```C++
auto lock() noexcept -> void;
auto lock_shared() noexcept -> void;
```
Lock the spin lock


### try_lock
```C++
EVO_NODISCARD auto try_lock() noexcept -> bool;
```
Attempt to lock the spin lock - returns false if it failed


### unlock
```C++
auto unlock() noexcept -> void;
auto unlock_shared() noexcept -> void;
```
Unlock the spin lock
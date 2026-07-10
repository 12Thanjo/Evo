# IterRange
#### containers/IterRange.h

```C++
template<class ITER>
class IterRange;
```

A range of iterators that don't have to point to contiguous data.



## Template Parameters

| Template | Description                  |
|:--------:|------------------------------|
|   ITER   | The type of iterator to hold |


## Member Types

| Member Type | Definition |
|-------------|------------|
| iterator    | `ITER`     |


## Member Functions

### Constructors
```C++
[[nodiscard]] constexpr IterRange(const ITER& begin_iter, const ITER& end_iter) noexcept;
[[nodiscard]] constexpr IterRange(ITER&& begin_iter, const ITER& end_iter) noexcept;
[[nodiscard]] constexpr IterRange(const ITER& begin_iter, ITER&& end_iter) noexcept;
[[nodiscard]] constexpr IterRange(ITER&& begin_iter, ITER&& end_iter) noexcept;
```

### Iterators

#### begin / cbegin
```C++
[[nodiscard]] constexpr auto begin() const noexcept -> iterator;
```
Returns an iterator to the beginning


#### end / cend
```C++
[[nodiscard]] constexpr auto end() const noexcept -> iterator;
```
Returns an iterator to the end



### Observers

#### size
```C++
[[nodiscard]] constexpr auto size() const noexcept -> size_t;
```
Get the number of elements in the range


#### empty
```C++
[[nodiscard]] constexpr auto empty() const noexcept -> bool;
```
Get if the range is empty

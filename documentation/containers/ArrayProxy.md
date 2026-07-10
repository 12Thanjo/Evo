# ArrayProxy
#### containers/ArrayProxy.h

```C++
template<typename T>
class ArrayProxy;
```

A read-only interface to an array-like set of data. This is designed for use in function parameters as it an hold temporaries.


#### Iterators:
All the iterators have identical interfaces to the respective iterators in [default evo iterators](iterators.md). The only difference is these have extra bounds checking in debug mode (`EVO_CONFIG_DEBUG`).



## Template Parameters

| Template | Description                           |
|:--------:|---------------------------------------|
|    T	   | The type of the elements of the array |


## Member Types

| Member Type              | Definition                          |
|--------------------------|-------------------------------------|
| value_type               | `T`                                 |
| size_type                | `size_t`                            |
| difference_type          | `std::ptrdiff_t`                    |
| reference                | `T&`                                |
| const_reference          | `const T&`                          |
| pointer                  | `T*`                                |
| const_pointer            | `const T*`                          |
| const_iterator           | `ArrayProxyConstIterator<T>`        |
| const_reverse_iterator   | `ArrayProxyConstReverseIterator<T>` |


## Member Functions

### Constructors
```C++
[[nodiscard]] constexpr ArrayProxy()                 noexcept; // no elements
[[nodiscard]] constexpr ArrayProxy( std::nullptr_t ) noexcept; // no elements
[[nodiscard]] constexpr ArrayProxy(const T& value)   noexcept; // one elements


[[nodiscard]] constexpr ArrayProxy(const T* array_ptr, size_t array_count)   noexcept;
[[nodiscard]] constexpr ArrayProxy(const std::initializer_list<T> init_list) noexcept;
[[nodiscard]] constexpr ArrayProxy(const std::vector<T>& vector)             noexcept;


template<size_t COUNT>
[[nodiscard]] constexpr ArrayProxy(const std::array<T, COUNT>& array) noexcept;

template<size_t COUNT>
[[nodiscard]] constexpr ArrayProxy(const std::span<T, COUNT>& span) noexcept;

template<size_t COUNT>
[[nodiscard]] constexpr ArrayProxy(const evo::StaticVector<T, COUNT>& static_vector) noexcept;
```

### Iterators

#### begin / cbegin
```C++
[[nodiscard]] constexpr auto  begin() const noexcept -> const_iterator;
[[nodiscard]] constexpr auto cbegin() const noexcept -> const_iterator;
```
Returns an iterator to the beginning


#### end / cend
```C++
[[nodiscard]] constexpr auto  end() const noexcept -> const_iterator;
[[nodiscard]] constexpr auto cend() const noexcept -> const_iterator;
```
Returns an iterator to the end


#### rbegin / crbegin
```C++
[[nodiscard]] constexpr auto  rbegin() const noexcept -> const_iterator;
[[nodiscard]] constexpr auto crbegin() const noexcept -> const_iterator;
```
Returns a reverse iterator to the beginning


#### rend / crend
```C++
[[nodiscard]] constexpr auto  rend() const noexcept -> const_iterator;
[[nodiscard]] constexpr auto crend() const noexcept -> const_iterator;
```
Returns a reverse iterator to the end



### Element Access

#### at 
```C++
[[nodiscard]] constexpr auto at(size_t index) const noexcept -> const T&;
```
Returns a const reference to the element at the given index


#### front
```C++
[[nodiscard]] constexpr auto front() const noexcept -> const T&;
```
Returns the first element


#### back
```C++
[[nodiscard]] constexpr auto back() const noexcept -> const T&;
```
Returns a the last element


#### operator[] 
```C++
[[nodiscard]] constexpr auto operator[](size_t index) const noexcept -> const T&;
```
Returns a const reference to the element at the given index


#### data
```C++
[[nodiscard]] constexpr auto data() const noexcept -> const T*;
```
Returns a pointer to the underlying data of the array




### Observers

#### size
```C++
[[nodiscard]] constexpr auto size() const noexcept -> size_t;
```
Get the number of elements in the array


#### size_bytes
```C++
[[nodiscard]] constexpr auto size_bytes() const noexcept -> size_t;
```
Get the size in bytes of the array


#### empty
```C++
[[nodiscard]] constexpr auto empty() const noexcept -> bool;
```
Get if the array is empty


### Subviews

#### first
```C++
[[nodiscard]] constexpr auto first(size_t num) const noexcept -> ArrayProxy<T>;
```
Get a sub-ArrayProxy containing the first `num` elements


#### last
```C++
[[nodiscard]] constexpr auto last(size_t num) const noexcept -> ArrayProxy<T>;
```
Get a sub-ArrayProxy containing the last `num` elements


#### subarr
```C++
[[nodiscard]] constexpr auto subarr(size_t start, size_t num_elems) const noexcept -> ArrayProxy<T>;
```
Get a sub-ArrayProxy containing the elements from `start` index for `num_elems` elements


### Operators
```C++
[[nodiscard]] constexpr auto operator==(const ArrayProxy<T>& rhs) const -> bool;
```



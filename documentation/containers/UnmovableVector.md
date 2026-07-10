# UnmovableVector
#### containers/UnmovableVector.h

```C++
template<typename T, bool ALLOW_SMALL_BUFFER_OPT = true>
class UnmovableVector;
```

A version of vector that allocates once and cannot reallocate without being cleared. This (along with no copy or move constructors) allows elements that cannot be copied or moved to be put into the container as well. It also has support for small-buffer-optimization which allows for allocating the elements in-place instead of allocating memory.


## Template Parameters

| Template               | Description                          |
|:----------------------:|--------------------------------------|
|           T            | Type of the elements of the vector   |
| ALLOW_SMALL_BUFFER_OPT | Allow small buffer optimization      |


## Member Types

| Member Type            | Definition                     |
|------------------------|--------------------------------|
| value_type             | `T`                            |
| size_type              | `size_t`                       |
| difference_type        | `std::ptrdiff_t`               |
| reference              | `T&`                           |
| const_reference        | `const T&`                     |
| pointer                | `T*`                           |
| const_pointer          | `const T*`                     |
| iterator               | `Iterator<T>`                  |
| const_iterator         | `ConstIterator<T>`             |
| reverse_iterator       | `ReverseIterator<T>`           |
| const_reverse_iterator | `ConstReverseIterator<T>`      |

## Member Functions

### Constructors
```C++
[[nodiscard]] constexpr UnmovableVector() noexcept;
[[nodiscard]] constexpr UnmovableVector(size_t reserve_ammount) noexcept;
```


### Element Access


#### at
```C++
[[nodiscard]] constexpr auto at(size_t index) noexcept -> T&;
[[nodiscard]] constexpr auto at(size_t index) const noexcept -> const T&;
```
Access the element at the given `index`


#### operator[]
```C++
[[nodiscard]] constexpr auto operator[](size_t index) noexcept -> T&;
[[nodiscard]] constexpr auto operator[](size_t index) const noexcept -> const T&;
```
Access the element at the given `index`


#### front
```C++
[[nodiscard]] constexpr auto front() noexcept -> char&;
[[nodiscard]] constexpr auto front() const noexcept -> const char&;
```
Access the first element (eqivalent to running `at(0)`). Behavior is undefined if `empty() == false` 


#### back
```C++
[[nodiscard]] constexpr auto back() noexcept -> char&;
[[nodiscard]] constexpr auto back() const noexcept -> const char&;
```
Access the first element (eqivalent to running `at(size() - 1)`). Behavior is undefined if `empty() == false` 


#### data
```C++
[[nodiscard]] constexpr auto data() noexcept -> char*;
[[nodiscard]] constexpr auto data() const noexcept -> const char*;
```
Returns a pointer to the underlying data of the vector.



### Iterators

#### begin
```C++
[[nodiscard]] constexpr auto  begin()       noexcept ->       iterator;
[[nodiscard]] constexpr auto  begin() const noexcept -> const_iterator;
[[nodiscard]] constexpr auto cbegin() const noexcept -> const_iterator;
```
Returns an iterator to the beginning of the vector.


#### end
```C++
[[nodiscard]] constexpr auto  end()       noexcept ->       iterator;
[[nodiscard]] constexpr auto  end() const noexcept -> const_iterator;
[[nodiscard]] constexpr auto cend() const noexcept -> const_iterator;
```
Returns an iterator to the end of the vector.


#### rbegin
```C++
[[nodiscard]] constexpr auto  rbegin()       noexcept ->       iterator;
[[nodiscard]] constexpr auto  rbegin() const noexcept -> const_iterator;
[[nodiscard]] constexpr auto crbegin() const noexcept -> const_iterator;
```
Returns an reverse iterator to the beginning of the vector.


#### rend
```C++
[[nodiscard]] constexpr auto  rend()       noexcept ->       iterator;
[[nodiscard]] constexpr auto  rend() const noexcept -> const_iterator;
[[nodiscard]] constexpr auto crend() const noexcept -> const_iterator;
```
Returns an reverse iterator to the end of the vector.



### Capacity

#### empty
```C++
[[nodiscard]] constexpr auto empty() const noexcept -> bool;
```
Returns if the vector is empty.


#### size
```C++
[[nodiscard]] constexpr auto size() const noexcept -> size_t;
```
Returns the size of the currently held vector.


#### max_size
```C++
[[nodiscard]] constexpr auto max_size() const noexcept -> size_t;
```
Returns the maximum size of the vector.


#### capacity
```C++
[[nodiscard]] constexpr auto capacity() const noexcept -> size_t;
```
Returns the total capacity of the vector.



### Modifiers

#### reserve
```C++
constexpr auto reserve(size_t reserve_ammount) noexcept -> void;
```
Reserve enough storage for `reserve_ammount` elements.


#### resize
```C++
constexpr auto resize(size_t reserve_ammount) noexcept -> void;
```
Allocates enough storage for `reserve_ammount` elements, and default constructs all of them.


#### clear
```C++
constexpr auto clear() noexcept -> void;
```
Clears all data in the vector (calls the destructor of each existing element).


#### insert
```C++
constexpr auto insert(const_iterator pos, const T& value) noexcept -> iterator;
constexpr auto insert(const_iterator pos, T&& value) noexcept -> iterator;
```
Insert an element at a given position `pos`. Returns an iterator to the newly inserted element.


#### emplace
```C++
template<class... Args>
constexpr auto emplace(const_iterator pos, Args&&... args) noexcept -> iterator;
```
Creates a new element at the given position `pos`, and constructs it in-place.


#### erase
```C++
constexpr auto erase(const_iterator pos) noexcept -> iterator;
```
Erases the element at given position `pos`. Returns an iterator to the element following the one removed. If `pos` refers to the last element, returns `end()` instead.


#### push_back
```C++
constexpr auto push_back(const T& value) noexcept -> void;
constexpr auto push_back(T&& value) noexcept -> void;
```
Add an element to the end of the vector


#### emplace_back
```C++
template<class... Args>
constexpr auto emplace_back(Args&&... args) noexcept -> T&;
```
Add an element to the end of the vector and generate the element in place.



#### pop_back
```C++
constexpr auto pop_back(const T& value) noexcept -> void;
```
Remove the element from the back of the list


#### resize
```C++
constexpr auto resize(size_t new_size) noexcept -> void;

template<std::enable_if<std::is_same_v<size_type, size_t>> = false>
constexpr auto resize(size_type new_size) noexcept -> void; // only if size_type is not size_t
```
Resize the vector to given size `new_size`


### Operators

#### operator==
```C++
[[nodiscard]] constexpr auto operator==(const UnmovableVector& rhs) const noexcept -> bool;
```

#### operator std::span<T>
```C++
[[nodiscard]] constexpr operator std::span<T>() noexcept;
```
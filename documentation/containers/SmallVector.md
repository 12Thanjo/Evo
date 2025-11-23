# SmallVector
#### containers/SmallVector.h

```C++
template<typename T, size_t SMALL_CAPACITY>
class SmallVector;
```

A vector that has small size optimization. SMALL_CAPACITY can be defaulted, and it will automatically pick the optimal size.


## Template Parameters

| Template       | Description                                                                                 |
|:--------------:|---------------------------------------------------------------------------------------------|
| T              | Type of the elements of the vector                                                          |
| SMALL_CAPACITY | Maximum capacity of the small vector optimization (0 to turn off small vector optimization) |


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
EVO_NODISCARD constexpr SmallVector() noexcept;
EVO_NODISCARD SmallVector(const SmallVector<T, SMALL_CAPACITY>& rhs) noexcept;
EVO_NODISCARD SmallVector(SmallVector<T, SMALL_CAPACITY>&& rhs) noexcept;

EVO_NODISCARD explicit constexpr SmallVector(size_type count, const T& value = T()) noexcept;

EVO_NODISCARD SmallVector(std::initializer_list<T> init_list) noexcept;

template<class InputIt>
EVO_NODISCARD constexpr StaticVector(InputIt first, InputIt last) noexcept;
```


### operator=
```C++
constexpr auto operator=(const SmallVector<T, SMALL_CAPACITY>& rhs) noexcept -> SmallVector<T, SMALL_CAPACITY>&;
constexpr auto operator=(SmallVector<T, SMALL_CAPACITY>&& rhs) noexcept -> SmallVector<T, SMALL_CAPACITY>&;
constexpr auto operator=(std::initializer_list<T> init_list) noexcept -> SmallVector<T, SMALL_CAPACITY>&;
```



### Element Access


#### at
```C++
EVO_NODISCARD constexpr auto at(size_t index) noexcept -> T&;
EVO_NODISCARD constexpr auto at(size_t index) const noexcept -> const T&;


template<std::enable_if<std::is_same_v<size_type, size_t>> = false>
EVO_NODISCARD constexpr auto at(size_type index) noexcept -> T&; // for if size_type is equivalent to size_t

template<std::enable_if<std::is_same_v<size_type, size_t>> = false>
EVO_NODISCARD constexpr auto at(size_type index) const noexcept -> const T&; // for if size_type is equivalent to size_t
```
Access the element at the given `index`


#### operator[]
```C++
EVO_NODISCARD constexpr auto operator[](size_t index) noexcept -> T&;
EVO_NODISCARD constexpr auto operator[](size_t index) const noexcept -> const T&;


template<std::enable_if<std::is_same_v<size_type, size_t>> = false>
EVO_NODISCARD constexpr auto operator[](size_type index) noexcept -> T&; // for if size_type is equivalent to size_t

template<std::enable_if<std::is_same_v<size_type, size_t>> = false>
EVO_NODISCARD constexpr auto operator[](size_type index) const noexcept -> const T&; // for if size_type is equivalent to size_t
```
Access the element at the given `index`


#### front
```C++
EVO_NODISCARD constexpr auto front() noexcept -> char&;
EVO_NODISCARD constexpr auto front() const noexcept -> const char&;
```
Access the first element (eqivalent to running `at(0)`). Behavior is undefined if `empty() == false` 


#### back
```C++
EVO_NODISCARD constexpr auto back() noexcept -> char&;
EVO_NODISCARD constexpr auto back() const noexcept -> const char&;
```
Access the first element (eqivalent to running `at(size() - 1)`). Behavior is undefined if `empty() == false` 


#### data
```C++
EVO_NODISCARD constexpr auto data() noexcept -> char*;
EVO_NODISCARD constexpr auto data() const noexcept -> const char*;
```
Returns a pointer to the underlying data of the vector.



### Iterators

#### begin
```C++
EVO_NODISCARD constexpr auto  begin()       noexcept ->       iterator;
EVO_NODISCARD constexpr auto  begin() const noexcept -> const_iterator;
EVO_NODISCARD constexpr auto cbegin() const noexcept -> const_iterator;
```
Returns an iterator to the beginning of the vector.


#### end
```C++
EVO_NODISCARD constexpr auto  end()       noexcept ->       iterator;
EVO_NODISCARD constexpr auto  end() const noexcept -> const_iterator;
EVO_NODISCARD constexpr auto cend() const noexcept -> const_iterator;
```
Returns an iterator to the end of the vector.


#### rbegin
```C++
EVO_NODISCARD constexpr auto  rbegin()       noexcept ->       iterator;
EVO_NODISCARD constexpr auto  rbegin() const noexcept -> const_iterator;
EVO_NODISCARD constexpr auto crbegin() const noexcept -> const_iterator;
```
Returns an reverse iterator to the beginning of the vector.


#### rend
```C++
EVO_NODISCARD constexpr auto  rend()       noexcept ->       iterator;
EVO_NODISCARD constexpr auto  rend() const noexcept -> const_iterator;
EVO_NODISCARD constexpr auto crend() const noexcept -> const_iterator;
```
Returns an reverse iterator to the end of the vector.



### Capacity

#### empty
```C++
EVO_NODISCARD constexpr auto empty() const noexcept -> bool;
```
Returns if the vector is empty.


#### size
```C++
EVO_NODISCARD constexpr auto size() const noexcept -> size_t;
```
Returns the size of the currently held vector.


#### max_size
```C++
EVO_NODISCARD constexpr static auto max_size() const noexcept -> size_t;
```
Returns the maximum size of the vector.


#### capacity
```C++
EVO_NODISCARD constexpr auto capacity() const noexcept -> size_t;
```
Returns the total capacity of the vector.


#### small_capacity
```C++
EVO_NODISCARD constexpr static auto small_capacity() const noexcept -> size_t;
```
Returns the total small capacity of the vector.



### Modifiers

#### clear
```C++
constexpr auto clear() noexcept -> void;
```
Clears all data in the vector (calls the destructor of each existing element).


#### reserve
```C++
constexpr auto reserve(size_t new_cap) noexcept -> void;
```
Make sure at least the given ammount is allocated. If `new_cap` is smaller than the current ammount allocated, do nothing.


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


#### append_range
```C++
template<class R>
constexpr auto append_range(R&& range) noexcept -> void;
```
Addend the range to the end of the vector.


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
EVO_NODISCARD constexpr auto operator==(const SmallVector& rhs) const noexcept -> bool;
```

#### operator std::span<T>
```C++
EVO_NODISCARD constexpr operator std::span<T>() noexcept;
```


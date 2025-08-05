# StepVector
#### containers/StepVector.h

```C++
template<typename T, size_t STARTING_POW_OF_2 = get_optimal_start_pow_of_2_for_step_vector<T>()>
class StepVector;
```

A vector that has stepping buffers. Unlike `std::vector`, when StepVector needs more space it allocates a new buffer of double the size of the last buffer, but keeps the old buffer. This means that methods like `StepVector::emplace_back()` do not invalidate iterators and does not require copying any of the buffer data.

By default, `STARTING_POW_OF_2` is 4 elements or a single cache-line (whichever makes more sense for the type).


## Template Parameters

| Template          | Description                                                                                             |
|:-----------------:|---------------------------------------------------------------------------------------------------------|
| T                 | Type of the elements of the vector                                                                      |
| STARTING_POW_OF_2 | Power of 2 size of the initial buffer (so a value of 3 means the starting buffer is size of 8 elements) |


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
| iterator               | `StepVector::Iter`             |
| const_iterator         | `StepVector::ConstIter`        |


## Member Functions

### Constructors
```C++
EVO_NODISCARD constexpr StepVector() noexcept;
EVO_NODISCARD constexpr StepVector(const StepVector&) noexcept;
EVO_NODISCARD constexpr StepVector(StepVector&&) noexcept;
```

### operator=
```C++
auto operator=(const StepVector<T, SMALL_CAPACITY>& rhs) noexcept -> StepVector<T, SMALL_CAPACITY>&;
auto operator=(StepVector<T, SMALL_CAPACITY>&& rhs) noexcept -> StepVector<T, SMALL_CAPACITY>&;
```


### Element Access


#### at
```C++
EVO_NODISCARD auto at(size_t index) noexcept -> T&;
EVO_NODISCARD auto at(size_t index) const noexcept -> const T&;
```
Access the element at the given `index`


#### operator[]
```C++
EVO_NODISCARD auto operator[](size_t index) noexcept -> T&;
EVO_NODISCARD auto operator[](size_t index) const noexcept -> const T&;
```
Access the element at the given `index`


#### front
```C++
EVO_NODISCARD auto front() noexcept -> char&;
EVO_NODISCARD auto front() const noexcept -> const char&;
```
Access the first element (eqivalent to running `at(0)`). Behavior is undefined if `empty() == false` 


#### back
```C++
EVO_NODISCARD auto back() noexcept -> char&;
EVO_NODISCARD auto back() const noexcept -> const char&;
```
Access the first element (eqivalent to running `at(size() - 1)`). Behavior is undefined if `empty() == false` 




### Iterators

#### begin
```C++
EVO_NODISCARD auto  begin()       noexcept ->       iterator;
EVO_NODISCARD auto  begin() const noexcept -> const_iterator;
EVO_NODISCARD auto cbegin() const noexcept -> const_iterator;
```
Returns an iterator to the beginning of the vector.


#### end
```C++
EVO_NODISCARD auto  end()       noexcept ->       iterator;
EVO_NODISCARD auto  end() const noexcept -> const_iterator;
EVO_NODISCARD auto cend() const noexcept -> const_iterator;
```
Returns an iterator to the end of the vector.





### Capacity

#### empty
```C++
EVO_NODISCARD auto empty() const noexcept -> bool;
```
Returns if the vector is empty.


#### size
```C++
EVO_NODISCARD auto size() const noexcept -> size_t;
```
Returns the size of the currently held vector.


#### resize
```C++
auto resize(size_t new_size) noexcept -> void;
```
Resize the vector to given size `new_size`.




### Modifiers

#### clear
```C++
auto clear() noexcept -> void;
```
Clears all data in the vector (calls the destructor of each existing element).


#### push_back
```C++
auto push_back(const T& value) noexcept -> void;
auto push_back(T&& value) noexcept -> void;
```
Add an element to the end of the vector.


#### emplace_back
```C++
template<class... Args>
auto emplace_back(Args&&... args) noexcept -> T&;
```
Add an element to the end of the vector and generate the element in place.


#### pop_back
```C++
auto pop_back(const T& value) noexcept -> void;
```
Remove the element from the back of the list


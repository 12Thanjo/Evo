# StaticString
#### containers/StaticString.h

```C++
template<size_t CAPACITY>
class StaticString;
```

Non-allocating version of std::string (the data is stored in-place). The `size_type` is automatically chosen to be smallest supported integral type (using `CapacityType`).

It can support c-strings with no extra capacity needed. For example:

```C++
auto small_string = evo::StaticString<5>("Hello"); // uses a ui8 to represent current size
auto large_string = evo::StaticString<256>("World"); // uses a ui16 to represent current size

evo::print( std::format("'{}' (size {})", small_string.c_str(), sizeof(small_string)) ); // prints: "'Hello' (size 6)"
evo::print( std::format("'{}' (size {})", large_string.c_str(), sizeof(large_string)) ); // prints: "'World' (size 258)"
```



## Template Parameters

| Template | Description                    |
|:--------:|--------------------------------|
| CAPACITY | Maximum capacity of the string |


## Member Types

| Member Type            | Definition                                           |
|------------------------|------------------------------------------------------|
| value_type             | `char`                                               |
| size_type              | `CapacityType<CAPACITY>::type`                       |
| difference_type        | `std::ptrdiff_t`                                     |
| reference              | `char&`                                              |
| const_reference        | `const char&`                                        |
| pointer                | `char*`                                              |
| const_pointer          | `const char*`                                        |
| iterator               | `std::array<char, CAPACITY>::iterator`               |
| const_iterator         | `std::array<char, CAPACITY>::const_iterator`         |
| reverse_iterator       | `std::array<char, CAPACITY>::reverse_iterator`       |
| const_reverse_iterator | `std::array<char, CAPACITY>::const_reverse_iterator` |


## Member Functions

### Constructors
```C++
EVO_NODISCARD constexpr StaticString() noexcept;

EVO_NODISCARD constexpr StaticString(const char* chars) noexcept;

EVO_NODISCARD constexpr StaticString(const std::string& str) noexcept;
EVO_NODISCARD constexpr StaticString(std::string&& str) noexcept;

template<size_t StrSize>
EVO_NODISCARD constexpr StaticString(const StaticString<StrSize>& str) noexcept;
```


### operator=
```C++
constexpr auto operator =(const char* chars) noexcept -> StaticString<CAPACITY>&;
constexpr auto operator =(const std::string& str) noexcept -> StaticString<CAPACITY>&;
constexpr auto operator =(std::string&& str) noexcept -> StaticString<CAPACITY>&;

template<size_t StrSize>
constexpr auto operator =(const StaticString<StrSize>& str) noexcept -> StaticString<CAPACITY>&;
```


### Element Access


#### at
```C++
EVO_NODISCARD constexpr auto at(size_type index) noexcept -> char&;
EVO_NODISCARD constexpr auto at(size_type index) const noexcept -> const char&;
```
Access a character at the given `index`


#### operator[]
```C++
EVO_NODISCARD constexpr auto operator[](size_type index) noexcept -> char&;
EVO_NODISCARD constexpr auto operator[](size_type index) const noexcept -> const char&;
```
Access a character at the given `index`


#### front
```C++
EVO_NODISCARD constexpr auto front() noexcept -> char&;
EVO_NODISCARD constexpr auto front() const noexcept -> const char&;
```
Access the first character of the string (eqivalent to running `at(0)`). Behavior is undefined if `empty() == false` 


#### back
```C++
EVO_NODISCARD constexpr auto back() noexcept -> char&;
EVO_NODISCARD constexpr auto back() const noexcept -> const char&;
```
Access the first character of the string (eqivalent to running `at(size() - 1)`). Behavior is undefined if `empty() == false` 


#### data
```C++
EVO_NODISCARD constexpr auto data() noexcept -> char*;
EVO_NODISCARD constexpr auto data() const noexcept -> const char*;
```
Returns a pointer to the underlying data of the string.


#### c_str
```C++
EVO_NODISCARD constexpr auto c_str() const noexcept -> const char*;
```
Returns a c-string. Is almost equivalent to calling `data()` but makes sure the string is null-terminated.



### Iterators

#### begin
```C++
EVO_NODISCARD constexpr auto  begin()       noexcept ->       iterator;
EVO_NODISCARD constexpr auto  begin() const noexcept -> const_iterator;
EVO_NODISCARD constexpr auto cbegin() const noexcept -> const_iterator;
```
Returns an iterator to the beginning of the string.


#### end
```C++
EVO_NODISCARD constexpr auto  end()       noexcept ->       iterator;
EVO_NODISCARD constexpr auto  end() const noexcept -> const_iterator;
EVO_NODISCARD constexpr auto cend() const noexcept -> const_iterator;
```
Returns an iterator to the end of the string.


#### rbegin
```C++
EVO_NODISCARD constexpr auto  rbegin()       noexcept ->       iterator;
EVO_NODISCARD constexpr auto  rbegin() const noexcept -> const_iterator;
EVO_NODISCARD constexpr auto crbegin() const noexcept -> const_iterator;
```
Returns an reverse iterator to the beginning of the string.


#### rend
```C++
EVO_NODISCARD constexpr auto  rend()       noexcept ->       iterator;
EVO_NODISCARD constexpr auto  rend() const noexcept -> const_iterator;
EVO_NODISCARD constexpr auto crend() const noexcept -> const_iterator;
```
Returns an reverse iterator to the end of the string.



### Capacity

#### empty
```C++
EVO_NODISCARD constexpr auto empty() const noexcept -> bool;
```
Returns if the string is empty.


#### size
```C++
EVO_NODISCARD constexpr auto size() const noexcept -> size_t;
```
Returns the size of the currently held string.


#### max_size
```C++
EVO_NODISCARD constexpr auto max_size() const noexcept -> size_t;
```
Returns the maximum size of the string.


#### capacity
```C++
EVO_NODISCARD constexpr auto capacity() const noexcept -> size_t;
```
Returns the total capacity of the string.



### Modifiers

#### clear
```C++
constexpr auto clear() noexcept -> void;
```
Clears the currently held string.


#### push_back
```C++
constexpr auto push_back(char value) noexcept -> void
```
Adds a character to the end of the string


#### pop_back
```C++
constexpr auto pop_back(char value) noexcept -> void
```
Removes a character to the end of the string


#### append
```C++
constexpr auto append(const char* chars) const -> void;
constexpr auto append(const std::string& str) const -> void;

template<size_t StrSize>
constexpr auto append(const StaticString<StrSize>& str) const -> void;
```
Adds to the end of the string. Equivalent to `operator+=`.



#### operator+=
```C++
constexpr auto operator +=(const char* chars) const -> void;
constexpr auto operator +=(const std::string& str) const -> void;

template<size_t StrSize>
constexpr auto operator +=(const StaticString<StrSize>& str) const -> void;
```
Adds to the end of the string. Equivalent to `append()`.


#### resize
```C++
constexpr auto resize(size_type new_size) noexcept -> void;

template<typename std::enable_if<std::is_same_v<size_t, size_type>> = false>
constexpr auto resize(size_t new_size) noexcept -> void; // for if size_type is equivalent to size_t
```
Resize the string to a given size.



#### resize_to_c_str
```C++
constexpr auto resize_to_c_str() noexcept -> void
```
Resizes the string by looking for the null-terminator. This is useful for when you pass `data()` into a C-function, and you can call `resize_to_c_str()` right after it.



### Helper Classes
```C++
template<size_t CAPACITY>
struct std::hash<evo::StaticString<CAPACITY>>;

template<size_t CAPACITY>
struct std::formatter<evo::StaticString<CAPACITY>>;
```

# Bimap
#### containers/Bimap.h

```C++
template<
	class LeftT, class RightT,
	class LHash = std::hash<LeftT>, class RHash = std::hash<RightT>,
	class LEqual = std::equal_to<LeftT>, class REqual = std::equal_to<RightT>,
	class DataAllocator = std::allocator<std::pair<LeftT, RightT>>, class BucketAllocator = std::allocator<StaticVector<size_t, _BimapMaxBucketSize>>
>
class Bimap;
```

A bi-direction hash map.


## Iterator Invalidation:
| Operations               | Invalidated               |
|--------------------------|---------------------------|
| All read only operations | Never                     |
| clear, rehashe, reserve  | Always                    |
| insert, emplace          | Only if causes rehash     |
| erase_left, erase_right  | Only if element is erased |



## Template Parameters

| Template        | Description                                        |
|:---------------:|----------------------------------------------------|
| LeftT           | Type of the left element				           |
| RightT          | Type of the right element 				           |
| LHash           | Type of the hasher for the left element            |
| RHash           | Type of the hasher for the right element           |
| LEqual          | Type of the equality checker for the left element  |
| REqual          | Type of the equality checker for the right element |
| DataAllocator   | Type of the data allocator                         |
| BucketAllocator | Type of the bucket allocator                       |


## Member Types

| Member Type              | Definition                                                  |
|--------------------------|-------------------------------------------------------------|
| left_type                | `LeftT`                                                     |
| right_type               | `RightT`                                                    |
| value_type               | `std::pair<LeftT, RightT>`                                  |
| size_type                | `std::size_t`                                               |
| difference_type          | `std::ptrdiff_t`                                            |
| left_hasher              | `LHash`                                                     |
| right_hasher             | `RHash`                                                     |
| left_key_equal           | `LEqual`                                                    |
| right_key_equal          | `REqual`                                                    |
| data_allocator_type      | `DataAllocator`                                             |
| bucket_allocator_type    | `BucketAllocator`                                           |
| reference                | `value_type&`                                               |
| const_reference          | `const value_type&`                                         |
| pointer                  | `value_type*`                                               |
| const_pointer            | `const value_type*`                                         |
| iterator                 | `Iterator<value_type>`                                      |
| const_iterator           | `ConstIterator<value_type>`                                 |
| local_iterator           | `StaticVector<size_t, _BimapMaxBucketSize>::iterator`       |
| const_local_iterator     | `StaticVector<size_t, _BimapMaxBucketSize>::const_iterator` |


## Member Functions

### Constructors
```C++
EVO_NODISCARD constexpr Bimap(
	size_t bucket_count = 16,
	const LHash& left_hasher = LHash(), const RHash& right_hasher = RHash(),
	const LEqual& left_equal_to = LEqual(), const REqual& right_equal_to = REqual(),
	const DataAllocator& data_alloc = DataAllocator(),
	const BucketAllocator& left_bucket_alloc = BucketAllocator(), const BucketAllocator& right_bucket_alloc = BucketAllocator()
) noexcept;
```

### Iterators

#### begin / cbegin
```C++
EVO_NODISCARD constexpr auto  begin()       noexcept ->       iterator;
EVO_NODISCARD constexpr auto  begin() const noexcept -> const_iterator;
EVO_NODISCARD constexpr auto cbegin() const noexcept -> const_iterator;
```
Returns an iterator to the beginning


#### end / cend
```C++
EVO_NODISCARD constexpr auto  end()       noexcept ->       iterator;
EVO_NODISCARD constexpr auto  end() const noexcept -> const_iterator;
EVO_NODISCARD constexpr auto cend() const noexcept -> const_iterator;
```
Returns an iterator to the end


#### rbegin / crbegin
```C++
EVO_NODISCARD constexpr auto  rbegin()       noexcept ->       iterator;
EVO_NODISCARD constexpr auto  rbegin() const noexcept -> const_iterator;
EVO_NODISCARD constexpr auto crbegin() const noexcept -> const_iterator;
```
Returns a reverse iterator to the beginning


#### rend / crend
```C++
EVO_NODISCARD constexpr auto  rend()       noexcept ->       iterator;
EVO_NODISCARD constexpr auto  rend() const noexcept -> const_iterator;
EVO_NODISCARD constexpr auto crend() const noexcept -> const_iterator;
```
Returns a reverse iterator to the end




### Capacity


#### empty
```C++
EVO_NODISCARD constexpr auto empty() const noexcept -> bool;
```
Get if the bimap is empty


#### size
```C++
EVO_NODISCARD constexpr auto size() const noexcept -> size_t;
```
Get the number of elements in the bimap


#### max_size
```C++
EVO_NODISCARD constexpr auto max_size() const noexcept -> size_t;
```
Get the maximum size of the bimap. The value returned is equivalent to `std::vector<value_type, DataAllocator>::max_size`


#### capacity
```C++
EVO_NODISCARD constexpr auto capacity() const noexcept -> size_t;
```
Get the current capacity of the bimap




### Modifiers

#### clear
```C++
constexpr auto clear() noexcept -> void;
```
Deletes all of the elements in the bimap, and resets the size to 0


#### insert
```C++
constexpr auto insert(const value_type& value) noexcept -> iterator;
constexpr auto insert(value_type&& value) noexcept -> iterator;
```
Insert a value pair into the bimap. Returns an iterator to the newly inserted pair


#### emplace
```C++
template<class... Args>
constexpr auto emplace(Args&&... args) noexcept -> iterator;
```
Create a new value pair in the bimap and creates it with the given arguments. Returns an iterator to the newly inserted pair


#### erase
```C++
constexpr auto erase_left(const LeftT& left) noexcept -> size_t;
constexpr auto erase_right(const RightT& right) noexcept -> size_t;
```
Erase a value pair from the bimap. Uses the given value to lookup the value pair.





### Lookup


#### at 
```C++
EVO_NODISCARD constexpr auto at_left(const LeftT& left)       noexcept ->       value_type&;
EVO_NODISCARD constexpr auto at_left(const LeftT& left) const noexcept -> const value_type&;

EVO_NODISCARD constexpr auto at_right(const RightT& right)       noexcept ->       value_type&;
EVO_NODISCARD constexpr auto at_right(const RightT& right) const noexcept -> const value_type&;
```
Get the value pair with the given value as the lookup


#### get
```C++
EVO_NODISCARD constexpr auto get_left(const RightT& right)       noexcept ->       LeftT&;
EVO_NODISCARD constexpr auto get_left(const RightT& right) const noexcept -> const LeftT&;

EVO_NODISCARD constexpr auto get_right(const LeftT& left)       noexcept ->       RightT&;
EVO_NODISCARD constexpr auto get_right(const LeftT& left) const noexcept -> const RightT&;
```
Given a lookup value, returns a reference to the oposite value in the respective value pair


#### find
```C++
EVO_NODISCARD constexpr auto find_left(const LeftT& left)       noexcept ->       iterator;
EVO_NODISCARD constexpr auto find_left(const LeftT& left) const noexcept -> const_iterator;

EVO_NODISCARD constexpr auto find_right(const RightT& right)       noexcept ->       iterator;
EVO_NODISCARD constexpr auto find_right(const RightT& right) const noexcept -> const_iterator;
```
Given a value, returns an iterator to the respective value pair. If the value pair does not exist, returns an iterator to the end (equivalent to a call to `end()`).


#### contains
```C++
EVO_NODISCARD constexpr auto contains_left(const LeftT& left) const noexcept -> bool;
EVO_NODISCARD constexpr auto contains_right(const RightT& right) const noexcept -> bool;
```
Returns if an value pair with the given value exists in the bimap.



### Bucket Interface

#### begin
```C++
EVO_NODISCARD constexpr auto  left_begin(size_t n)       noexcept ->       local_iterator;
EVO_NODISCARD constexpr auto  left_begin(size_t n) const noexcept -> const_local_iterator;
EVO_NODISCARD constexpr auto left_cbegin(size_t n) const noexcept -> const_local_iterator;

EVO_NODISCARD constexpr auto  right_begin(size_t n)       noexcept ->       local_iterator;
EVO_NODISCARD constexpr auto  right_begin(size_t n) const noexcept -> const_local_iterator;
EVO_NODISCARD constexpr auto right_cbegin(size_t n) const noexcept -> const_local_iterator;
```
Get an local iterator to the beginning of the bucket at index `n`


#### end
```C++
EVO_NODISCARD constexpr auto  left_end(size_t n)       noexcept ->       local_iterator;
EVO_NODISCARD constexpr auto  left_end(size_t n) const noexcept -> const_local_iterator;
EVO_NODISCARD constexpr auto left_cend(size_t n) const noexcept -> const_local_iterator;

EVO_NODISCARD constexpr auto  right_end(size_t n)       noexcept ->       local_iterator;
EVO_NODISCARD constexpr auto  right_end(size_t n) const noexcept -> const_local_iterator;
EVO_NODISCARD constexpr auto right_cend(size_t n) const noexcept -> const_local_iterator;
```
Get an local iterator to the end of the bucket at index `n`. The functions beginning with "left_" will get the buckets for the left values, and visa versa.


#### bucket_count
```C++
EVO_NODISCARD constexpr auto bucket_count() const noexcept -> size_t;
```
Get the current number of buckets


### max_bucket_count
```C++
EVO_NODISCARD constexpr auto max_bucket_count() const noexcept -> size_t;
```
Get the maximum number of buckets. Equivalent to calling `std::vector<std::vector<StaticVector<size_t, evo::_BimapMaxBucketSize>, BucketAllocator>::max_size()`


### bucket_size
```C++
EVO_NODISCARD constexpr auto left_bucket_size(size_t n) const noexcept -> size_t;
EVO_NODISCARD constexpr auto right_bucket_size(size_t n) const noexcept -> size_t;
```
Get the size of a bucket at index `n`.


### bucket
```C++
EVO_NODISCARD constexpr auto left_bucket(const LeftT& left) const noexcept -> size_t;
EVO_NODISCARD constexpr auto right_bucket(const RightT& right) const noexcept -> size_t;
```
Get the bucket index for a specific value.



### Hash Policy

#### max_bucket_size
```C++
EVO_NODISCARD constexpr static auto max_bucket_size() noexcept -> size_t;
```
Get the maximum size of a bucket.


#### rehash
```C++
constexpr auto rehash(size_t count) noexcept -> void;
```
Rehash for `count` of buckets.


#### reserve
```C++
constexpr auto reserve(size_t count) noexcept -> void;
```
Rehash for `count` number of elements. Equivalent to calling `Bimap::rehash(count / Bimap::max_bucket_size())`.


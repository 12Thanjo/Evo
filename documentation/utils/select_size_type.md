# Select Size Type
#### utils/select_size_type.h

Template "magic" to optimally determine which integral size type is best


## CapacityType
```C++
template<size_t CAPACITY>
struct CapacityType;
```
Get the smallest integral type required to store given capacity.


## CapacityType_t
```C++
template<size_t CAPACITY>
using CapacityType_t = CapacityType<CAPACITY>::type;
```
Get the smallest integral type required to store given capacity.



## BitsSize
```C++
template<size_t BITS>
struct BitsSize;
```
Get the smallest integral type required to store number of bits.

## BitsSize
```C++
template<size_t BITS>
using BitsSize_t = BitsSize<BITS>::type;
```
Get the smallest integral type required to store number of bits.



## Example Usage:
```C++
// this will be equivalent to ui8 because it can hold a count to 17
using Ex1 = evo::CapacityType_t<17>;

// this will be equivalent to ui16 because it can hold a count to 400
using Ex2 = evo::CapacityType<400>::type;


// this will be equivalent to ui32 because it is the smallest integral type that has a minimum of 19 bits
using Ex3 = evo::BitsSize_t<19>;

// this will be equivalent to ui64 because it is the smallest integral type that has a minimum of 38 bits
using Ex4 = evo::BitsSize<38>::type;

```

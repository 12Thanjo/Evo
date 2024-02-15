# Select Size Type
#### utils/select_size_type.h

Template "magic" to optimally determine which integral size type is best


## CapacityType
```C++
template<size_t CAPACITY>
struct CapacityType;
```
Get the smallest integral type required to store given capacity.


## BitsSize
```C++
template<size_t BITS>
struct BitsSize;
```
Get the smallest integral type required to store number of bits.



## Example Usage:
```C++
// this will be equivalent to ui8 because it can hold a count to 17
using Ex1 = evo::CapacityType<17>::type;

// this will be equivalent to ui16 because it can hold a count to 400
using Ex2 = evo::CapacityType<400>::type;


// this will be equivalent to ui64 because it is the smallest type that has a minimum of 38 bits
using Ex3 = evo::BitsSize<38>::type;

```

# Numeric Types
#### utils/numeric_types.h

Numeric types for convienence

## Integral types
Defining the macro `EVO_GLOBAL_NUMERIC_TYPES` will also put all of these in the global namespace

| Type   | Description             | Alias for           |
|:------:|-------------------------|---------------------|
| `i8`   | 8-bit integer           | int8_t              |
| `i16`  | 16-bit integer          | int16_t             |
| `i16`  | 32-bit integer          | int32_t             |
| `i16`  | 64-bit integer          | int64_t             |
| `ui8`  | 8-bit unsigned integer  | uint8_t             |
| `ui16` | 16-bit unsigned integer | uint16_t            |
| `ui16` | 32-bit unsigned integer | uint32_t            |
| `ui16` | 64-bit unsigned integer | uint64_t            |
| `byte` | single byte             | ui8	             |
| `uint` | unsigned integer		   | unsigned int	     |


## Floating point types
Defining the macro `EVO_GLOBAL_NUMERIC_TYPES` will also put all of these in the global namespace

| Type   | Description   | Alias for           |
|:------:|---------------|---------------------|
| `f32`  | 32-bit float  | float               |
| `f64`  | 64-bit float  | double              |
| `f128` | 128-bit float | long double         |



### Implementation of C++23's float types
These are implementations of some of C++23's explicitly sized floating point types. All of these are automatically placed in global namespace unless its C++23 or greater in which case it will include `stdfloat` instead

| Type         | Description   | Alias for           |
|:------------:|---------------|---------------------|
| `float32_t`  | 32-bit float  | float               |
| `float64_t`  | 64-bit float  | double              |
| `float128_t` | 128-bit float | long double         |






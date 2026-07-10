# Strings
#### utils/strings.h

String utility functions

## stringSize
```C++
[[nodiscard]] constexpr auto stringSize(const char* str, size_t max_length = 100) noexcept -> size_t;
```
Returns the length of a null-terminated char array (`str`) up to a maximum length (`max_length`)


## stringsEqual
```C++
[[nodiscard]] constexpr auto stringsEqual(const char* str1, const char* str2, size_t max_length = 100) noexcept -> evo::Result<bool>;
```
Compares two null-terminated char arrays (`str1` and `str2`) up to a maximum length (`max_length`). The function returns an error if both strings are larger than the maximum length


## isLowerLetter
```C++
[[nodiscard]] constexpr auto isLowerLetter(char character) noexcept -> bool;
```
Checks if a character is a lower-case letter


## isUpperLetter
```C++
[[nodiscard]] constexpr auto isUpperLetter(char character) noexcept -> bool;
```
Checks if a character is a upper-case 


## isLetter
```C++
[[nodiscard]] constexpr auto isLetter(char character) noexcept -> bool;
```
Checks if a character is a letter


## isNumber
```C++
[[nodiscard]] constexpr auto isNumber(char character) noexcept -> bool;
```
Checks if a character is a number


## isHexNumber
```C++
[[nodiscard]] constexpr auto isHexNumber(char character) noexcept -> bool;
```
Checks if a character is a hex number (equivalent to regex: `[0-9a-fA-F]`)


## isOctalNumber
```C++
[[nodiscard]] constexpr auto isOctalNumber(char character) noexcept -> bool;
```
Checks if a character is a octal number (equivalent to regex: `[0-7]`)


## isAlphaNumeric
```C++
[[nodiscard]] constexpr auto isAlphaNumeric(char character) noexcept -> bool;
```
Checks if a character is a letter or a number


## isWhitespace
```C++
[[nodiscard]] constexpr auto isWhitespace(char character) noexcept -> bool;
```
Checks if a character is a letter or a number


## printCharName
```C++
[[nodiscard]] constexpr auto printCharName(char character) noexcept -> const char*;
```
Returns a null-terminated char-array for the name of the character. If the character does not have a specific name, it will return "`[[EXTENDED ASCII]]`" instead.


## boolStr
```C++
[[nodiscard]] constexpr auto boolStr(bool boolean) noexcept -> const char*;
```
Converts the boolean to either the string "true" or "false"
# File
#### tools/fs.h


```C++
class File;
```

A type to help manage reading from and writing to text files.



## Member functions

### Constructors
```C++
[[nodiscard]] File() noexcept;
```



### Handle

#### open
```C++
[[nodiscard]] auto open(const std::string& path, Flags<FileMode> mode) noexcept -> bool;
```
Opens a file.

#### close
```C++
auto close() noexcept -> void;
```
Closes the file.



#### getHandle
```C++
[[nodiscard]] constexpr auto getHandle() const noexcept -> ::FILE*;
```
Gets the underlying file handle.

#### isValid
```C++
[[nodiscard]] constexpr auto isValid() const noexcept -> bool;
```
Gets if the file is handle is valid (essentially if the file is open).



### Reading

#### read
```C++
[[nodiscard]] auto read() const noexcept -> std::optional<std::string>; // 1
[[nodiscard]] auto read(size_t data_size) const noexcept -> std::optional<std::string>; // 2
```
Reads the file. Returns `std::nullopt` if an error occured.
- Function 1 will read the entire file
- Function 2 will read up `data_size`


#### readLine
```C++
[[nodiscard]] auto readLine() const noexcept -> std::optional<std::string>;
```
Reads a line from the file (calls `::fgets()`). Can call this function multiple times to get next lines. Returns `std::nullopt` if an error occured.



### Writing

#### write
```C++
[[nodiscard]] auto write(const std::string& data) noexcept -> bool;
```
Writes data to the file. Returns if the write was successful.

#### writeLine
```C++
[[nodiscard]] auto writeLine(const std::string& text) noexcept -> bool;
```
Appends a line to the file. Returns if the write was successful.


### Observers

#### size
```C++
[[nodiscard]] auto size() const noexcept -> size_t;
```
Gets the size of the file



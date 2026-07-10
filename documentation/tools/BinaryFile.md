# BinaryFile
#### tools/fs.h


```C++
class BinaryFile;
```

A type to help manage reading from and writing to binary files.



## Member functions

### Constructors
```C++
[[nodiscard]] BinaryFile() noexcept;
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
[[nodiscard]] auto read() const noexcept -> std::optional<std::vector<byte>>; // 1
[[nodiscard]] auto read(size_t data_size) const noexcept -> std::optional<std::vector<byte>>; // 2
```
Reads the file. Returns `std::nullopt` if an error occured.
- Function 1 will read the entire file
- Function 2 will read up `data_size`




### Writing

#### write
```C++
[[nodiscard]] auto write(const std::vector<byte>& data) noexcept -> bool;
```
Writes data to the file. Returns if the write was successful.


### Observers

#### size
```C++
[[nodiscard]] auto size() const noexcept -> size_t;
```
Gets the size of the file



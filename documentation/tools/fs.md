# FS (File System)
#### tools/fs.h


## Classes

### [File](File.md)
### [BinaryFile](BinaryFile.md)


## Functions

### exists
```C++
[[nodiscard]] auto exists(const std::string& path) noexcept -> bool;
```
Returns if a file exists given the `path`


### readFile
```C++
[[nodiscard]] auto readFile(const std::string& path) noexcept -> Result<std::string>;
```
Quick interface to read a file.

### readBinaryFile
```C++
[[nodiscard]] auto readBinaryFile(const std::string& path) noexcept -> Result<std::vector<byte>>;
```
Quick interface to read a binary file.

### writeFile
```C++
[[nodiscard]] auto writeFile(const std::string& path, const std::string& data) noexcept -> bool;
```
Quick interface to write a file. Returns `false` if it failed.

### writeBinaryFile
```C++
[[nodiscard]] auto writeBinaryFile(const std::string& path, const std::vector<byte>& data) noexcept -> bool;
```
Quick interface to write a binary file. Returns `false` if it failed.



## Enums

### FileMode
```C++
enum class FileMode : ui8 {
	Read,
	Write,

	_max,
};
```


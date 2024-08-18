# FS (File System)
#### tools/fs.h


## Classes

### [File](File.md)
### [BinaryFile](BinaryFile.md)


## Functions

### exists
```C++
EVO_NODISCARD auto exists(const std::string& path) noexcept -> bool;
```
Returns if a file exists given the `path`


### readFile
```C++
EVO_NODISCARD auto readFile(const std::string& path) noexcept -> Result<std::string>;
```
Quick interface to read a file.

### readBinaryFile
```C++
EVO_NODISCARD auto readBinaryFile(const std::string& path) noexcept -> Result<std::vector<byte>>;
```
Quick interface to read a binary file.

### writeFile
```C++
EVO_NODISCARD auto writeFile(const std::string& path, const std::string& data) noexcept -> bool;
```
Quick interface to write a file. Returns `false` if it failed.

### writeBinaryFile
```C++
EVO_NODISCARD auto writeBinaryFile(const std::string& path, const std::vector<byte>& data) noexcept -> bool;
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


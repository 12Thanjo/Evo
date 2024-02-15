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


## Enums

### FileMode
```C++
enum class FileMode : ui8 {
	Read,
	Write,

	_max,
};
```


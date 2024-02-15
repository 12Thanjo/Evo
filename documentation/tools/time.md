# Time
#### tools/time.h


## Classes

### Nanoseconds
###### TODO

### Milliseconds
###### TODO

### Seconds
###### TODO


## Functions

### now
```C++
EVO_NODISCARD auto now() noexcept -> Nanoseconds;
```
Get the current clock time.



### getCurrentTime
```C++
EVO_NODISCARD auto getCurrentTime() noexcept -> CurrentTime;
```
Returns the current time. The current time is a struct:

```C++
struct CurrentTime{
	ui16 year;
	ui8 month;
	ui8 day;

	ui8 hours;
	ui8 minutes;
	ui8 seconds;
};
```
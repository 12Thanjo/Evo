# Dyn Lib
#### utils/dyn_lib.h

Macros defining dynamic library interface.

Usage:
```C++
extern "C" {
	EVO_DYN_LIB auto some_func() -> void {
		// do stuff...
	}

	EVO_DYN_LIB_HIDDEN auto hidden_func() -> void {
		// do stuff...
	}
}

// if you want to turn off these macros, you can define EVO_IGNORE_DYN_LIB
```


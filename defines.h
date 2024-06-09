#pragma once


// these (without the macro) messes with sublime syntax highlighting
#define EVO_NODISCARD [[nodiscard]]

#define EVO_NORETURN [[noreturn]]


#define EVO_CONCAT_INNER(a, b) a ## b
#define EVO_CONCAT(a, b) EVO_CONCAT_INNER(a, b)
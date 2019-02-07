

#ifndef BOOLEAN_H_
#define BOOLEAN_H_

/* Skip if <stdbool.h> was already included. */
#ifndef __bool_true_false_are_defined

/* Skip if this is being compiled in C++ */
#ifndef __cplusplus

/* Undefine any previously defined preprocessor macros. */
#undef bool
#undef true
#undef false

typedef int bool;
enum { false = 0, true = 1 };
#endif
#endif

#endif


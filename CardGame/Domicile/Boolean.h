/*
** Copyright (C) October 2018 by Colby O'Donnell <colbster@uw.edu>
** University of Washington PCE (Professional Continuing Education)
** Assignment 8, Boolean.h
**
** Limited license is granted for use by the following institution:
**   University of Washington PCE (Professional Continuing Education)
**   Course: Foundations of C - Autumn 2018
**   The institution may share this work only with registered students of the course.
**   Registered students of the course may retain a copy of this work for their own personal educational use.
**
** Development
**   Author:    Colby O'Donnell <colbster@uw.edu>
**   Developed: January 05, 2012
**   Updated:   October 13, 2018
**
** For bool, true, and false, you may use either this header, or #include <stdbool.h>, which is
** available in most standard C libraries, even though it is not strictly ANSI-C.
*/

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


#pragma once

/* Define to 1 if you have the <inttypes.h> header file. */
#define HAVE_INTTYPES_H 0

/* Define to 1 if you have the <stdint.h> header file. */
#define HAVE_STDINT_H 1

/* Define to 1 if you have the <stdio.h> header file. */
#define HAVE_STDIO_H 0

/* Define to 1 if you have the <strings.h> header file. */
#define HAVE_STRINGS_H 0

/* Define to 1 if you have the <string.h> header file. */
#define HAVE_STRING_H 1

/* Define to 1 if you have the ANSI C header files. */
#define STDC_HEADERS 1

// disallow bcopy in string.h
#define _POSIX_C_SOURCE 200809L

// use precalculated log table
#define USE_FAST_LOG 0

// use precalculated log table as const -> in the ESP32 this will end up in flash memory
#define USE_FAST_LOG_CONST 0

// deocode on the fly
#define DECODE_ON_THE_FLY 0

// optimization which only works with -fno-strict-alias
#define USE_HIRO_IEEE754_HACK 0

// Avoid big memory allocations
#define USE_MEMORY_HACK 1

// Print memory allocation
#define USE_DEBUG_ALLOC 1

// Not all microcontroller support vararg methods: alternative impelentation using the preprocessor
#define USE_LOGGING_HACK 1

// Print debug messages
#define USE_DEBUG 1


#define WITH_DMALLOC 0
#define DEPRECATED_OR_OBSOLETE_CODE_REMOVED 1
#define HAVE_NASM 0
#define HAVE_MPGLIB 0
#define HAVE_XMMINTRIN_H 0


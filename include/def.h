#ifndef DEF_INCLUDED
#define DEF_INCLUDED (1)

#include <stdbool.h>
#include <stdint.h>
#include <ctype.h>

#include "arch/cfg.h"
#include "platform/cfg.h"

#define ignore      (void)
#define unused(...) ((void)(__VA_ARGS__))

/* unsigned integer */
typedef uint8_t u8;
#define u8_limit (UINT8_MAX)

typedef uint16_t u16;
#define u16_limit (UINT16_MAX)

typedef uint32_t u32;
#define u32_limit (UINT32_MAX)

typedef uint64_t u64;
#define u64_limit (UINT64_MAX)

typedef uintptr_t usize;
#define usize_limit (UINTPTR_MAX)

/* signed integer */
typedef int8_t i8;
#define i8_limit_min (INT8_MIN)
#define i8_limit_max (INT8_MAX)

typedef int16_t i16;
#define i16_limit_min (INT16_MIN)
#define i16_limit_max (INT16_MAX)

typedef int32_t i32;
#define i32_limit_min (INT32_MIN)
#define i32_limit_max (INT32_MAX)

typedef int64_t i64;
#define i64_limit_min (INT64_MIN)
#define i64_limit_max (INT64_MAX)

typedef intptr_t isize;
#define isize_limit_min (INTPTR_MIN)
#define isize_limit_max (INTPTR_MAX)

#endif /* DEF_INCLUDED */

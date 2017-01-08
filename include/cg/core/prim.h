#ifndef CG_CORE_PRIM_H
#define CG_CORE_PRIM_H

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <inttypes.h>

typedef bool     CGbool;
typedef int8_t   CGi8;
typedef uint8_t  CGu8;
typedef int16_t  CGi16;
typedef uint16_t CGu16;
typedef int32_t  CGi32;
typedef uint32_t CGu32;
typedef int64_t  CGi64;
typedef uint64_t CGu64;
typedef intptr_t CGisize;
typedef size_t   CGusize;
typedef intptr_t CGindex;
typedef float    CGfloat;
typedef double   CGdouble;

#define CG_TRUE  true
#define CG_FALSE false

#define CG_INVALID_INDEX SIZE_MAX

#endif // CG_CORE_PRIM_H

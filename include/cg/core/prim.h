#ifndef CGCORE_PRIM_H
#define CGCORE_PRIM_H

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
typedef size_t   CGsize;
typedef intptr_t CGintptr;

#define CGINVALID_INDEX SIZE_MAX

#endif // CGCORE_PRIM_H

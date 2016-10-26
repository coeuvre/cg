#ifndef CG_CORE_TYPES_H
#define CG_CORE_TYPES_H

#include <stdbool.h>
#include <stdint.h>

typedef uint8_t u8;
typedef int8_t i8;
typedef uint16_t u16;
typedef int16_t i16;
typedef uint32_t u32;
typedef int32_t i32;
typedef uint64_t u64;
typedef int64_t i64;
typedef intptr_t isize;
typedef uintptr_t usize;

typedef float f32;
typedef double f64;

#define F32_MIN FLT_MIN
#define F32_MAX FLT_MAX

#define KB(x) ((x) * 1024LL)
#define MB(x) (KB(x) * 1024LL)
#define GB(x) (MB(x) * 1024LL)
#define TB(x) (GB(x) * 1024LL)

#endif

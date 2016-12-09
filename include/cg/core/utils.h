#ifndef CG_CORE_UTILS_H
#define CG_CORE_UTILS_H

#include <cg/core/env.h>
#include <cg/core/prim.h>

#include <assert.h>

#if defined(CG_COMPILER_MSVC)
    #define CG_EXPORT __declspec(dllexport)
#elif defined(CG_COMPILER_GCC)
    #define CG_EXPORT __attribute__((dllexport))
#else
    #error Unsupported compiler
#endif

#define cg_array_count(a) (sizeof(a) / sizeof((a)[0]))

#define CG_ASSERT(expr) assert(expr)

#define CG_UNREACHABLE() CG_ASSERT(!"unreachable")

uint64_t cg_get_current_counter(void);

uint64_t cg_counter_to_nanosec(uint64_t counter);

#define cg_nanosec_to_sec(nanosec) ((double)((nanosec) / 1000000000.0))

#define cg_nanosec_to_millisec(nanosec) ((nanosec) / 1000000)

#define cg_sec_to_nanosec(sec) ((uint64_t)((sec) * 1000000000))

#define cg_sec_to_millisec(sec) ((uint64_t)((sec) * 1000))

#endif /* CG_CORE_UTILS_H */

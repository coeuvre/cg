#ifndef CG_CORE_UTILS_H
#define CG_CORE_UTILS_H

#include <cg/core/env.h>

#include <assert.h>

#if defined(CG_COMPILER_MSVC)
    #define CG_EXPORT __declspec(dllexport)
#elif defined(CG_COMPILER_GCC)
    #define CG_EXPORT __attribute__((dllexport))
#else
    #error Unsupported compiler
#endif

#define cg_array_count(a) (sizeof(a) / sizeof((a)[0]))

#define cg_assert(expr) assert(expr)

#endif /* CG_CORE_UTILS_H */

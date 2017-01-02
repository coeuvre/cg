#ifndef CGCORE_UTILS_H
#define CGCORE_UTILS_H

#include <cg/core/env.h>
#include <cg/core/prim.h>

#include <assert.h>

#if defined(CGCOMPILER_MSVC)
    #define CGEXPORT __declspec(dllexport)
#elif defined(CGCOMPILER_GCC)
    #define CGEXPORT __attribute__((dllexport))
#else
    #error Unsupported compiler
#endif

#define CGCOUNT(a) (sizeof(a) / sizeof((a)[0]))

#define CGASSERT(expr) assert(expr)

#define CGUNREACHABLE() CGASSERT(!"unreachable")

#endif // CGCORE_UTILS_H

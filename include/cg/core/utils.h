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

#define cgArrayCount(a) (sizeof(a) / sizeof((a)[0]))

#define cgAssert(expr) assert(expr)

#define cgUnreachable() cgAssert(!"unreachable")

CGu64 cgGetTick(void);

CGu64 cgTickToNanosecond(CGu64 ticks);

#define cgNanosecondToSecond(ns) ((double)((ns) / 1000000000.0))

#define cgNanosecondToMillisecond(ns) ((ns) / 1000000)

#define cgSecondToNanosecond(sec) ((uint64_t)((sec) * 1000000000))

#define cgSecondToMillisecond(sec) ((uint64_t)((sec) * 1000))


#endif // CG_CORE_UTILS_H

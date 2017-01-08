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

#define cgGetCArrayCount(a) (sizeof(a) / sizeof((a)[0]))

#define cgAssert(expr) assert(expr)

#define cgUnreachable() cgAssert(!"unreachable")

CGu64 cgGetTicks(void);

CGu64 cgTicksToNanoseconds(CGu64 ticks);

#define cgNanosecondsToSeconds(ns) ((double)((ns) / 1000000000.0))

#define cgNanosecondsToMilliseconds(ns) ((ns) / 1000000)

#define cgSecondsToNanoseconds(sec) ((uint64_t)((sec) * 1000000000))

#define cgSecondsToMilliseconds(sec) ((uint64_t)((sec) * 1000))


#endif // CG_CORE_UTILS_H

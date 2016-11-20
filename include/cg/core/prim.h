#ifndef CG_CORE_PRIM_H
#define CG_CORE_PRIM_H

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

#if defined(CG_COMPILER_MSVC)
    #define CG_EXPORT __declspec(dllexport)
#elif defined(CG_COMPILER_GCC)
    #define CG_EXPORT __attribute__((dllexport))
#else
    #define CG_EXPORT
#endif

#define cg_array_count(a) (sizeof(a) / sizeof((a)[0]))

#endif /* CG_CORE_PRIM_H */

#ifndef CG_CORE_UTILS_H
#define CG_CORE_UTILS_H

#include <assert.h>
#define cg_assert(expr) assert(expr)

#define cg_array_count(a) (sizeof(a) / sizeof(a[0]))

#define cg_size_kb(x) ((x) * 1024LL)
#define cg_size_mb(x) (cg_size_kb(x) * 1024LL)
#define cg_size_gb(x) (cg_size_mb(x) * 1024LL)
#define cg_size_tb(x) (cg_size_gb(x) * 1024LL)

#endif // CG_CORE_UTILS_H

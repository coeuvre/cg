#ifndef CG_CORE_MEMORY_H
#define CG_CORE_MEMORY_H

#include <cg/core/prim.h>

#define CG_KB(x) ((x) * 1024LL)
#define CG_MB(x) (CG_KB(x) * 1024LL)
#define CG_GB(x) (CG_MB(x) * 1024LL)
#define CG_TB(x) (CG_GB(x) * 1024LL)

#define cgAlloc(size) cgAllocWithContext(size, __FILE__, __LINE__)
#define cgCalloc(size) cgCallocWithContext(size, __FILE__, __LINE__)
#define cgFree(p, size) cgFreeWithContext(p, size, __FILE__, __LINE__)

void *cgAllocWithContext(CGusize size, CGi8 *file, CGu32 line);

void *cgCallocWithContext(CGusize count, CGusize size, CGi8 *file, CGu32 line);

void cgFreeWithContext(void *p, CGusize size, CGi8 *file, CGu32 line);

#endif // CG_CORE_MEMORY_H

#ifndef CGCORE_MEMORY_H
#define CGCORE_MEMORY_H

#include <cg/core/prim.h>

#define CGKB(x) ((x) * 1024LL)
#define CGMB(x) (CGKB(x) * 1024LL)
#define CGGB(x) (CGMB(x) * 1024LL)
#define CGTB(x) (CGGB(x) * 1024LL)

#define CGALLOC(size) cgAllocWithContext(size, __FILE__, __LINE__)
#define CGCALLOC(size) cgCallocWithContext(size, __FILE__, __LINE__)
#define CGFREE(p, size) cgFreeWithContext(p, size, __FILE__, __LINE__)

CGvoid *cgAllocWithContext(CGuint size, CGi8 *file, CGu32 line);

CGvoid *cgCallocWithContext(CGuint count, CGuint size, CGi8 *file, CGu32 line);

CGvoid cgFreeWithContext(CGvoid *p, CGuint size, CGi8 *file, CGu32 line);

#endif // CGCORE_MEMORY_H

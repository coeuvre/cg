#ifndef CG_PLATFORM_CORE_MEMORY_H
#define CG_PLATFORM_CORE_MEMORY_H

#include <cg/core/prim.h>

void *cgPlatformAlloc(CGusize size);
void *cgPlatformCalloc(CGusize count, CGusize size);
void cgPlatformFree(void *p);

#endif // CG_PLATFORM_CORE_MEMORY_H

#ifndef CG_PLATFORM_CORE_MEMORY_H
#define CG_PLATFORM_CORE_MEMORY_H

#include <cg/core/prim.h>

void *cgPlatformAlloc(CGuint size);
void *cgPlatformCalloc(CGuint count, CGuint size);
void cgPlatformFree(void *p);

#endif // CG_PLATFORM_CORE_MEMORY_H

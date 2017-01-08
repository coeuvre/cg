#ifndef CG_PLATFORM_CORE_MEMORY_H
#define CG_PLATFORM_CORE_MEMORY_H

#include <cg/core/prim.h>

void *cgPlatformAlloc(size_t size);
void *cgPlatformCalloc(size_t count, size_t size);
void cgPlatformFree(void *p);

#endif /* CG_PLATFORM_CORE_MEMORY_H */

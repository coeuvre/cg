#ifndef CG_PLATFORM_CORE_MEMORY_H
#define CG_PLATFORM_CORE_MEMORY_H

#include <cg/core/prim.h>

void *cg_platform_alloc(size_t size);
void *cg_platform_calloc(size_t count, size_t size);
void cg_platform_free(void *p);

#endif /* CG_PLATFORM_CORE_MEMORY_H */

#ifndef CG_CORE_MEMORY_H
#define CG_CORE_MEMORY_H

#include <cg/core/prim.h>

#define cg_size_kb(x) ((x) * 1024LL)
#define cg_size_mb(x) (cg_size_kb(x) * 1024LL)
#define cg_size_gb(x) (cg_size_mb(x) * 1024LL)
#define cg_size_tb(x) (cg_size_gb(x) * 1024LL)

#define cg_alloc(size) cg_alloc_with_context(size, __FILE__, __LINE__)
#define cg_calloc(size) cg_calloc_with_context(size, __FILE__, __LINE__)
#define cg_free(p, size) cg_free_with_context(p, size, __FILE__, __LINE__)

void *cg_alloc_with_context(size_t size, char *file, int line);

void *cg_calloc_with_context(size_t count, size_t size, char *file, int line);

void cg_free_with_context(void *p, size_t size, char *file, int line);

#endif /* CG_CORE_MEMORY_H */

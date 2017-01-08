#include <cg/core.h>

#include <stdlib.h>

typedef struct MemoryInfo MemoryInfo;
struct MemoryInfo {
    CGi8 *file;
    CGu32 line;
    CGusize size;
    MemoryInfo *next;
    MemoryInfo *prev;
};

/*
 * NOTE: This static variable means we are NOT thread safe.
 */
static MemoryInfo *HEAD;

static void *pushMemoryInfo(void *memory, CGusize size,
                              CGi8 *file, CGu32 line)
{
    MemoryInfo *mi = memory;

    cgAssert(mi != 0);

    mi->file = file;
    mi->line = line;
    mi->size = size;
    mi->next = HEAD;
    mi->prev = 0;

    if (mi->next) {
        mi->next->prev = mi;
    }

    HEAD = mi;

    return mi + 1;
}

void *cgAllocWithContext(CGusize size, CGi8 *file, CGu32 line)
{
    void *memory = malloc(size + sizeof(MemoryInfo));

    return pushMemoryInfo(memory, size, file, line);
}

void *cgCallocWithContext(CGusize count, CGusize size, CGi8 *file, CGu32 line)
{
    CGusize total = count * size + sizeof(MemoryInfo);
    CGusize per = total / count;
    if (per * count < total) {
        per = per + 1;
    }
    cgAssert(per * count >= total);
    void *memory = calloc(count, per);

    return pushMemoryInfo(memory, size, file, line);
}

void cgFreeWithContext(void *p, CGusize size, CGi8 *file, CGu32 line)
{
    MemoryInfo *mi = (MemoryInfo *)p - 1;

    cgAssert(mi != 0);

    if (mi->size != size) {
        cgLogWithContext(file, line, CG_LOG_LEVEL_WARN,
                         "Memory corrupted: free memory with size %zu, "       \
                         "but it was allocated with size %zu.",
                         size, mi->size);
    }

    if (mi->next) {
        mi->next->prev = mi->prev;
    }

    if (mi->prev) {
        mi->prev->next = mi->next;
    }

    free(mi);
}

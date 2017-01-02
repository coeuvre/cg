#include <stdlib.h>

#include <cg/core.h>

typedef struct MemoryInfo MemoryInfo;
struct MemoryInfo {
    CGi8 *file;
    CGu32 line;
    CGuint size;
    MemoryInfo *next;
    MemoryInfo *prev;
};

/*
 * NOTE: This static variable means we are NOT thread safe.
 */
static MemoryInfo *HEAD;

static CGvoid *pushMemoryInfo(CGvoid *memory, CGuint size,
                              CGi8 *file, CGu32 line)
{
    MemoryInfo *mi = memory;

    CGASSERT(mi != 0);

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

CGvoid *cgAllocWithContext(CGuint size, CGi8 *file, CGu32 line)
{
    CGvoid *memory = malloc(size + sizeof(MemoryInfo));

    return pushMemoryInfo(memory, size, file, line);
}

CGvoid *cgCallocWithContext(CGuint count, CGuint size, CGi8 *file, CGu32 line)
{
    CGuint total = count * size + sizeof(MemoryInfo);
    CGuint per = total / count;
    if (per * count < total) {
        per = per + 1;
    }
    CGASSERT(per * count >= total);
    CGvoid *memory = calloc(count, per);

    return pushMemoryInfo(memory, size, file, line);
}

CGvoid cgFreeWithContext(CGvoid *p, CGuint size, CGi8 *file, CGu32 line)
{
    MemoryInfo *mi = (MemoryInfo *)p - 1;

    CGASSERT(mi != 0);

    if (mi->size != size) {
        cgLogWithContext(file, line, CGLOG_LEVEL_WARN,
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

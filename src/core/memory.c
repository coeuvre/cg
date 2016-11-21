#include <stdlib.h>

#include <cg/core/log.h>
#include <cg/core/memory.h>
#include <cg/core/util.h>

struct memory_info;

struct memory_info {
    char *file;
    int line;
    size_t size;
    struct memory_info *next;
    struct memory_info *prev;
};

/*
 * This static variable means we are NOT thread safe.
 */
static struct memory_info *HEAD;

static void *push_memory_info(void *memory, size_t size, char *file, int line)
{
    struct memory_info *mi = memory;

    cg_assert(mi != 0);

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

void *cg_alloc_with_context(size_t size, char *file, int line)
{
    void *memory = malloc(size + sizeof(struct memory_info));

    return push_memory_info(memory, size, file, line);
}

void *cg_calloc_with_context(size_t count, size_t size, char *file, int line)
{
    size_t total = count * size + sizeof(struct memory_info);
    size_t per = total / count;
    if (per * count < total) {
        per = per + 1;
    }
    cg_assert(per * count >= total);
    void *memory = calloc(count, per);

    return push_memory_info(memory, size, file, line);
}

void cg_free_with_context(void *p, size_t size, char *file, int line)
{
    struct memory_info *mi = (struct memory_info *)p - 1;

    cg_assert(mi != 0);

    if (mi->size != size) {
        cg_log_with_context(file, line, CG_LOG_LEVEL_WARNING,
                            "Memory corrupted: free memory with size %zu, " \
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
#include <cg/core/assert.h>
#include <cg/core/string.h>
#include <cg/core/prim.h>

int main(void)
{
    char str[] = "hello, cg";
    char *p = cg_str_rfind(str, cg_array_count(str) - 1, ',');
    cg_assert(p);

    return 0;
}

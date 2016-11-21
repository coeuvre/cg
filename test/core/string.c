#include <cg/core/string.h>
#include <cg/core/prim.h>
#include <cg/core/util.h>

static void test_cstr_is_equal()
{
    cg_assert(cg_cstr_is_equal("This is a test string in cg.",
                               "This is a test string in cg."));

    cg_assert(!cg_cstr_is_equal("This is a test string in cg,",
                                "This is a test string in cg."));

    cg_assert(!cg_cstr_is_equal("This is a test string",
                                "This is a test string in cg."));

    cg_assert(!cg_cstr_is_equal("In cg, this is a test string",
                                "This is a test string in cg."));
}

static void test_cstr_rfind()
{
    char *str = "This is a test string in cg.";
    size_t count = cg_cstr_count(str);
    cg_assert(count == 28);

    size_t p;

    p = cg_cstr_rfind(str, 'z');
    cg_assert(p == CG_INVALID_INDEX);

    p = cg_cstr_rfind(str, '.');
    cg_assert(p == count - 1);

    p = cg_cstr_rfind(str, 'T');
    cg_assert(p == 0);

    p = cg_cstr_rfind(str, 'a');
    cg_assert(p == 8);

    p = cg_cstr_rfind(str, 'i');
    cg_assert(p == 22);
}

static void test_cstr_copy()
{
    char *str = "This is a test string in cg.";

    {
        char buf[512];
        size_t copied = cg_cstr_copy(buf, 512, str);
        cg_assert(copied == cg_cstr_count(str));
        cg_assert(cg_cstr_is_equal(buf, str));
    }

    {
        char buf[10];
        size_t copied = cg_cstr_copy(buf, 10, str);
        cg_assert(copied == 9);
        cg_assert(cg_cstr_count(buf) == 9);
        cg_assert(!cg_cstr_is_equal(buf, str));
    }
}

int main(void)
{
    test_cstr_is_equal();
    test_cstr_rfind();
    test_cstr_copy();

    return 0;
}

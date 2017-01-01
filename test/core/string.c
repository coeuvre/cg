#include <cg/core.h>

static void test_cstr_is_equal(void)
{
    CG_ASSERT(cg_cstr_is_equal("This is a test string in cg.",
                               "This is a test string in cg."));

    CG_ASSERT(!cg_cstr_is_equal("This is a test string in cg,",
                                "This is a test string in cg."));

    CG_ASSERT(!cg_cstr_is_equal("This is a test string",
                                "This is a test string in cg."));

    CG_ASSERT(!cg_cstr_is_equal("In cg, this is a test string",
                                "This is a test string in cg."));
}

static void test_cstr_rfind(void)
{
    char *str = "This is a test string in cg.";
    size_t count = cg_cstr_count(str);
    CG_ASSERT(count == 28);

    size_t p;

    p = cg_cstr_rfind(str, 'z');
    CG_ASSERT(p == CGINVALID_INDEX);

    p = cg_cstr_rfind(str, '.');
    CG_ASSERT(p == count - 1);

    p = cg_cstr_rfind(str, 'T');
    CG_ASSERT(p == 0);

    p = cg_cstr_rfind(str, 'a');
    CG_ASSERT(p == 8);

    p = cg_cstr_rfind(str, 'i');
    CG_ASSERT(p == 22);
}

static void test_cstr_copy(void)
{
    char *str = "This is a test string in cg.";

    {
        char buf[512];
        size_t copied = cg_cstr_copy(buf, 512, str);
        CG_ASSERT(copied == cg_cstr_count(str));
        CG_ASSERT(cg_cstr_is_equal(buf, str));
    }

    {
        char buf[10];
        size_t copied = cg_cstr_copy(buf, 10, str);
        CG_ASSERT(copied == 9);
        CG_ASSERT(cg_cstr_count(buf) == 9);
        CG_ASSERT(!cg_cstr_is_equal(buf, str));
    }
}

int main(void)
{
    test_cstr_is_equal();
    test_cstr_rfind();
    test_cstr_copy();

    return 0;
}

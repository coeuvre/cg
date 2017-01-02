#include <cg/core.h>

static void test_cstr_is_equal(void)
{
    CGASSERT(cg_cstr_is_equal("This is a test string in cg.",
                               "This is a test string in cg."));

    CGASSERT(!cg_cstr_is_equal("This is a test string in cg,",
                                "This is a test string in cg."));

    CGASSERT(!cg_cstr_is_equal("This is a test string",
                                "This is a test string in cg."));

    CGASSERT(!cg_cstr_is_equal("In cg, this is a test string",
                                "This is a test string in cg."));
}

static void test_cstr_rfind(void)
{
    char *str = "This is a test string in cg.";
    size_t count = cg_cstr_count(str);
    CGASSERT(count == 28);

    size_t p;

    p = cg_cstr_rfind(str, 'z');
    CGASSERT(p == CGINVALID_INDEX);

    p = cg_cstr_rfind(str, '.');
    CGASSERT(p == count - 1);

    p = cg_cstr_rfind(str, 'T');
    CGASSERT(p == 0);

    p = cg_cstr_rfind(str, 'a');
    CGASSERT(p == 8);

    p = cg_cstr_rfind(str, 'i');
    CGASSERT(p == 22);
}

static void test_cstr_copy(void)
{
    char *str = "This is a test string in cg.";

    {
        char buf[512];
        size_t copied = cg_cstr_copy(buf, 512, str);
        CGASSERT(copied == cg_cstr_count(str));
        CGASSERT(cg_cstr_is_equal(buf, str));
    }

    {
        char buf[10];
        size_t copied = cg_cstr_copy(buf, 10, str);
        CGASSERT(copied == 9);
        CGASSERT(cg_cstr_count(buf) == 9);
        CGASSERT(!cg_cstr_is_equal(buf, str));
    }
}

int main(void)
{
    test_cstr_is_equal();
    test_cstr_rfind();
    test_cstr_copy();

    return 0;
}

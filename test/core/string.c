#include <cg/core.h>

static void test_cstr_is_equal(void)
{
    cgAssert(cgIsCStrEqual("This is a test string in cg.",
                               "This is a test string in cg."));

    cgAssert(!cgIsCStrEqual("This is a test string in cg,",
                                "This is a test string in cg."));

    cgAssert(!cgIsCStrEqual("This is a test string",
                                "This is a test string in cg."));

    cgAssert(!cgIsCStrEqual("In cg, this is a test string",
                                "This is a test string in cg."));
}

static void test_cstr_rfind(void)
{
    char *str = "This is a test string in cg.";
    size_t count = cgGetCStrCount(str);
    cgAssert(count == 28);

    size_t p;

    p = cgFindCStrReversed(str, 'z');
    cgAssert(p == CG_INVALID_INDEX);

    p = cgFindCStrReversed(str, '.');
    cgAssert(p == count - 1);

    p = cgFindCStrReversed(str, 'T');
    cgAssert(p == 0);

    p = cgFindCStrReversed(str, 'a');
    cgAssert(p == 8);

    p = cgFindCStrReversed(str, 'i');
    cgAssert(p == 22);
}

static void test_cstr_copy(void)
{
    char *str = "This is a test string in cg.";

    {
        char buf[512];
        size_t copied = cgCopyCStr(buf, 512, str);
        cgAssert(copied == cgGetCStrCount(str));
        cgAssert(cgIsCStrEqual(buf, str));
    }

    {
        char buf[10];
        size_t copied = cgCopyCStr(buf, 10, str);
        cgAssert(copied == 9);
        cgAssert(cgGetCStrCount(buf) == 9);
        cgAssert(!cgIsCStrEqual(buf, str));
    }
}

int main(void)
{
    test_cstr_is_equal();
    test_cstr_rfind();
    test_cstr_copy();

    return 0;
}

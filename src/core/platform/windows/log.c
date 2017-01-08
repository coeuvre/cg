#include "core/platform/log.h"

#include <stdio.h>

#include <Windows.h>

static bool IS_INITIALIZED = false;
#define OUTPUT_BUF_SIZE 4096
static char OUTPUT_BUF[OUTPUT_BUF_SIZE];

void cgPlatformLog(CGi8 *message)
{
    OutputDebugStringA(message);
    OutputDebugStringA("\n");

    if (!IS_INITIALIZED) {
        setvbuf(stdout, OUTPUT_BUF, _IOFBF, OUTPUT_BUF_SIZE);
        IS_INITIALIZED = true;
    }

    printf("%s\n", message);
}

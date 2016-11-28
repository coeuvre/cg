#include <cg/platform/core/log.h>

#include <stdio.h>

#include <Windows.h>

void cg_platform_log(char *message)
{
    OutputDebugStringA(message);
    OutputDebugStringA("\n");
    printf("%s\n", message);
}

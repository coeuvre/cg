#include <cg/platform/core/log.h>

#include <stdio.h>

#include <Windows.h>

void cg_platform_log(char *message)
{
    OutputDebugString(message);
    printf(message);
}

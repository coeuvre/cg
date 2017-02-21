#include "core/platform/Log.h"

#include <stdio.h>

void cgPlatformLog(char *message)
{
    printf("%s\n", message);
}

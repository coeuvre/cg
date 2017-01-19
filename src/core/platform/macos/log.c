#include "core/platform/log.h"

#include <stdio.h>

void cgPlatformLog(char *message)
{
    printf("%s\n", message);
}

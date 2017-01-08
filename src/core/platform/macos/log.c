#include "core/platform/log.h"

#include <stdio.h>

void cgPlatformLog(CGi8 *message)
{
    printf("%s\n", message);
}

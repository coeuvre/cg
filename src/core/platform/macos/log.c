#include "core/platform/log.h"

#include <stdio.h>

void cg_platform_log(char *message)
{
    printf("%s\n", message);
}

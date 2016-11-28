#include <cg/core/log.h>

#include <stdio.h>

#include <cg/platform/core/log.h>

void cg_vlog_with_context(char *file, int line, enum cg_log_level level,
                          char *format, va_list args)
{
#define MAX_CHAR_COUNT 512
    char buf[MAX_CHAR_COUNT];
    vsnprintf(buf, MAX_CHAR_COUNT, format, args);
    cg_platform_log(buf);
}

void cg_log_with_context(char *file, int line, enum cg_log_level level,
                         char *format, ...)
{
    (void)level;
    va_list args;
    va_start(args, format);
    cg_vlog_with_context(file, line, level, format, args);
    va_end(args);
}

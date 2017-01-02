#include <cg/core/log.h>
#include <cg/core/utils.h>

#include <stdio.h>

#include "core/platform/log.h"

/*
 * Log level
 *
 * NOTE: This global variable means LOG related functions are NOT thread safe.
 *
 * TODO: Make this thread safe.
 */
static CGLogLevel LEVEL = CGLOG_LEVEL_ERROR;

static char *logLevelToString(CGLogLevel level)
{
    static char *t[] = {
        "MERGE",
        "ALERT",
        "CRIT",
        "ERROR",
        "WARN",
        "NOTICE",
        "INFO",
        "DEBUG",
    };

    if (level >= 0 && level < CGCOUNT(t)) {
        return t[level];
    } else {
        return "DEFAULT";
    }
}

void cgSetLogLevel(CGLogLevel level)
{
    LEVEL = level;
}

CGLogLevel cgGetLogLevel(void)
{
    return LEVEL;
}

void cgLogWithContext(char *file, int line, CGLogLevel level,
                      char *format, ...)
{
    (void)level;
    va_list args;
    va_start(args, format);
    if (level <= LEVEL) {
#define MAX_CHAR_COUNT 512
        char buf[MAX_CHAR_COUNT];

        char *level_str = logLevelToString(level);
        size_t written = snprintf(buf, MAX_CHAR_COUNT,
                                "%s(%d): [%s] ", file, line, level_str);

        if (written > 0 && written < MAX_CHAR_COUNT) {
            vsnprintf(buf + written, MAX_CHAR_COUNT - written, format, args);
        }

        cg_platform_log(buf);
    }
    va_end(args);
}

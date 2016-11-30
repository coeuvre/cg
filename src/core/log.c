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
static enum cg_log_level LEVEL = CG_LOG_LEVEL_ERROR;

static char *log_level_to_str(enum cg_log_level level)
{
    switch (level) {
    case CG_LOG_LEVEL_DEFAULT:
        return "DEFAULT";
    case CG_LOG_LEVEL_EMERG:
        return "MERGE";
    case CG_LOG_LEVEL_ALERT:
        return "ALERT";
    case CG_LOG_LEVEL_CRIT:
        return "CRIT";
    case CG_LOG_LEVEL_ERROR:
        return "ERROR";
    case CG_LOG_LEVEL_WARN:
        return "WARN";
    case CG_LOG_LEVEL_NOTICE:
        return "NOTICE";
    case CG_LOG_LEVEL_INFO:
        return "INFO";
    case CG_LOG_LEVEL_DEBUG:
        return "DEBUG";
    }

    cg_unreachable();

    return "";
}

void cg_set_log_level(enum cg_log_level level)
{
    LEVEL = level;
}

enum cg_log_level cg_get_log_level(void)
{
    return LEVEL;
}

void cg_vlog_with_context(char *file, int line, enum cg_log_level level,
                          char *format, va_list args)
{
    if (level <= LEVEL) {
#define MAX_CHAR_COUNT 512
        char buf[MAX_CHAR_COUNT];

        char *level_str = log_level_to_str(level);
        size_t written = snprintf(buf, MAX_CHAR_COUNT,
                                "%s(%d): [%s] ", file, line, level_str);

        if (written > 0 && written < MAX_CHAR_COUNT) {
            vsnprintf(buf + written, MAX_CHAR_COUNT - written, format, args);
        }

        cg_platform_log(buf);
    }
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

#ifndef CG_CORE_LOG_H
#define CG_CORE_LOG_H

#include <stdarg.h>

#include <cg/core/prim.h>

typedef enum CGLogLevel {
    CG_LOG_LEVEL_DEFAULT = -1,  // default (or last) loglevel
    CG_LOG_LEVEL_EMERG   = 0,   // system is unusable
    CG_LOG_LEVEL_ALERT   = 1,   // action must be taken immediately
    CG_LOG_LEVEL_CRIT    = 2,   // critical conditions
    CG_LOG_LEVEL_ERROR   = 3,   // error conditions
    CG_LOG_LEVEL_WARN    = 4,   // warning conditions
    CG_LOG_LEVEL_NOTICE  = 5,   // normal but significant condition
    CG_LOG_LEVEL_INFO    = 6,   // informational
    CG_LOG_LEVEL_DEBUG   = 7,   // debug-level messages
} CGLogLevel;

/*
 * Set log level.
 */
void cgSetLogLevel(CGLogLevel level);

/*
 * Get current log level.
 */
CGLogLevel cgGetLogLevel(void);

void cgLogWithContext(char *file, CGu32 line, CGLogLevel level,
                      char *format, ...);

#define cgLog(level, format, ...)                                              \
    cgLogWithContext(__FILE__, __LINE__, CG_LOG_LEVEL_##level, format,         \
                     ##__VA_ARGS__)

#endif // CG_CORE_LOG_H

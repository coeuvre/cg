#ifndef CG_CORE_LOG_H
#define CG_CORE_LOG_H

#include <stdarg.h>

enum CgLogLevel {
    CG_LOG_LEVEL_DEFAULT = -1,  /* default (or last) loglevel */
    CG_LOG_LEVEL_EMERG   = 0,   /* system is unusable */
    CG_LOG_LEVEL_ALERT   = 1,   /* action must be taken immediately */
    CG_LOG_LEVEL_CRIT    = 2,   /* critical conditions */
    CG_LOG_LEVEL_ERROR   = 3,   /* error conditions */
    CG_LOG_LEVEL_WARN    = 4,   /* warning conditions */
    CG_LOG_LEVEL_NOTICE  = 5,   /* normal but significant condition */
    CG_LOG_LEVEL_INFO    = 6,   /* informational */
    CG_LOG_LEVEL_DEBUG   = 7,   /* debug-level messages */
};

/*
 * Set log level.
 */
void cgSetLogLevel(enum CgLogLevel level);

/*
 * Get current log level.
 */
enum CgLogLevel cgGetLogLevel(void);

void cgLogWithContext(char *file, int line, enum CgLogLevel level,
                      char *format, ...);

#define CG_LOG(level, format, ...)                                             \
    cgLogWithContext(__FILE__, __LINE__, CG_LOG_LEVEL_##level, format,         \
                     ##__VA_ARGS__)

#endif // CG_CORE_LOG_H

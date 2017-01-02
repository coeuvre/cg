#ifndef CGCORE_LOG_H
#define CGCORE_LOG_H

#include <stdarg.h>

typedef enum CGLogLevel {
    CGLOG_LEVEL_DEFAULT = -1,  /* default (or last) loglevel */
    CGLOG_LEVEL_EMERG   = 0,   /* system is unusable */
    CGLOG_LEVEL_ALERT   = 1,   /* action must be taken immediately */
    CGLOG_LEVEL_CRIT    = 2,   /* critical conditions */
    CGLOG_LEVEL_ERROR   = 3,   /* error conditions */
    CGLOG_LEVEL_WARN    = 4,   /* warning conditions */
    CGLOG_LEVEL_NOTICE  = 5,   /* normal but significant condition */
    CGLOG_LEVEL_INFO    = 6,   /* informational */
    CGLOG_LEVEL_DEBUG   = 7,   /* debug-level messages */
} CGLogLevel;

/*
 * Set log level.
 */
void cgSetLogLevel(CGLogLevel level);

/*
 * Get current log level.
 */
CGLogLevel cgGetLogLevel(void);

void cgLogWithContext(char *file, int line, CGLogLevel level,
                      char *format, ...);

#define CGLOG(level, format, ...)                                              \
    cgLogWithContext(__FILE__, __LINE__, CGLOG_LEVEL_##level, format,          \
                     ##__VA_ARGS__)

#endif // CGCORE_LOG_H

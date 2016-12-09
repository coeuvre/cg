#ifndef CG_CORE_LOG_H
#define CG_CORE_LOG_H

#include <stdarg.h>

enum cg_log_level {
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
void cg_set_log_level(enum cg_log_level level);

/*
 * Get current log level.
 */
enum cg_log_level cg_get_log_level(void);

void cg_vlog_with_context(char *file, int line, enum cg_log_level level,
                          char *format, va_list args);

void cg_log_with_context(char *file, int line, enum cg_log_level level,
                         char *format, ...);

#define cg_log(level, format, ...)                                             \
    cg_log_with_context(__FILE__, __LINE__, level, format, ##__VA_ARGS__)

#define CG_ERROR(format, ...) cg_log(CG_LOG_LEVEL_ERROR, format, ##__VA_ARGS__)

#define CG_WARNING(format, ...)                                                \
    cg_log(CG_LOG_LEVEL_WARNING, format, ##__VA_ARGS__)

#define CG_INFO(format, ...) cg_log(CG_LOG_LEVEL_INFO, format, ##__VA_ARGS__)

#define CG_DEBUG(format, ...) cg_log(CG_LOG_LEVEL_DEBUG, format, ##__VA_ARGS__)

#endif /* CG_CORE_LOG_H */

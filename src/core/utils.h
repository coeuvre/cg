#ifndef CG_CORE_UTILS_H
#define CG_CORE_UTILS_H

#include <assert.h>
#include <stdarg.h>

#define ASSERT(expr) assert(expr)

#define ARRAY_COUNT(a) (sizeof(a) / sizeof(a[0]))

typedef enum LogLevel {
    LogLevel_Error,
    LogLevel_Warn,
    LogLevel_Info,
    LogLevel_Debug,
    LogLevel_Trace,
} LogLevel;

#define LOG_ERROR(format, ...) cg_log(LogLevel_Error, format, __VA_ARGS__)
#define LOG_WARN(format, ...) cg_log(LogLevel_Warn, format, __VA_ARGS__)
#define LOG_INFO(format, ...) cg_log(LogLevel_Info, format, __VA_ARGS__)
#define LOG_DEBUG(format, ...) cg_log(LogLevel_Debug, format, __VA_ARGS__)
#define LOG_TRACE(format, ...) cg_log(LogLevel_Trace, format, __VA_ARGS__)

#define CG_LOG(name) void name(LogLevel level, char *format, ...)
typedef CG_LOG(Log);

#define CG_VLOG(name) void name(LogLevel level, char *format, va_list args)
typedef CG_VLOG(VLog);

extern CG_LOG(cg_log);

#endif

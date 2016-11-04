#ifndef CG_CORE_LOG_H
#define CG_CORE_LOG_H

#include <stdarg.h>

typedef enum LogLevel {
    LogLevel_Error,
    LogLevel_Warn,
    LogLevel_Info,
    LogLevel_Debug,
    LogLevel_Trace,
} LogLevel;

#define error(format, ...) log(LogLevel_Error, format, __VA_ARGS__)
#define warn(format, ...) log(LogLevel_Warn, format, __VA_ARGS__)
#define info(format, ...) log(LogLevel_Info, format, __VA_ARGS__)
#define debug(format, ...) log(LogLevel_Debug, format, __VA_ARGS__)
#define trace(format, ...) log(LogLevel_Trace, format, __VA_ARGS__)

#define LOG(name) void name(LogLevel level, char *format, ...)
typedef LOG(Log);

#define VLOG(name) void name(LogLevel level, char *format, va_list args)
typedef VLOG(VLog);

extern LOG(log);

#endif // CG_CORE_LOG_H

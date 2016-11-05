#ifndef CG_CORE_LOG_H
#define CG_CORE_LOG_H

#include <stdarg.h>

typedef enum cgLogLevel {
    cgLogLevel_Error,
    cgLogLevel_Warn,
    cgLogLevel_Info,
    cgLogLevel_Debug,
    cgLogLevel_Trace,
} cgLogLevel;

#define cg_error(format, ...) cg_log(cgLogLevel_Error, format, __VA_ARGS__)
#define cg_warn(format, ...) cg_log(cgLogLevel_Warn, format, __VA_ARGS__)
#define cg_info(format, ...) cg_log(cgLogLevel_Info, format, __VA_ARGS__)
#define cg_debug(format, ...) cg_log(cgLogLevel_Debug, format, __VA_ARGS__)
#define cg_trace(format, ...) cg_log(cgLogLevel_Trace, format, __VA_ARGS__)

#define CG_LOG(name) void name(cgLogLevel level, char *format, ...)
typedef CG_LOG(cgLog);

#define CG_VLOG(name) void name(cgLogLevel level, char *format, va_list args)
typedef CG_VLOG(cgVLog);

extern CG_LOG(cg_log);

#endif // CG_CORE_LOG_H

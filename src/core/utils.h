#ifndef CG_CORE_UTILS_H
#define CG_CORE_UTILS_H

#include <assert.h>

#define ASSERT(expr) assert(expr)

typedef enum LogLevel {
    LogLevel_Error,
    LogLevel_Warn,
    LogLevel_Info,
    LogLevel_Debug,
    LogLevel_Trace,
} LogLevel;

#endif

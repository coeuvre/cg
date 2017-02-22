#ifndef CG_CORE_LOG_H
#define CG_CORE_LOG_H

#include <stdarg.h>

#include <cg/core/Prim.h>

typedef enum CGLogLevel {
    kCGLogLevelDefault = -1,  // default (or last) loglevel
    kCGLogLevelEmerg   = 0,   // system is unusable
    kCGLogLevelAlert   = 1,   // action must be taken immediately
    kCGLogLevelCrit    = 2,   // critical conditions
    kCGLogLevelError   = 3,   // error conditions
    kCGLogLevelWarn    = 4,   // warning conditions
    kCGLogLevelNotice  = 5,   // normal but significant condition
    kCGLogLevelInfo    = 6,   // informational
    kCGLogLevelDebug   = 7,   // debug-level messages
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
    cgLogWithContext(__FILE__, __LINE__, kCGLogLevel##level, format,         \
                     ##__VA_ARGS__)

#endif // CG_CORE_LOG_H

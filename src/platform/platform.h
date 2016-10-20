#ifndef CG_PLATFORM_H
#define CG_PLATFORM_H

// Platform does:
//   * OpenGL Context Creation
//   * Hot reload game code
//
// Platform provides:
//   * Logging
//   * File I/O
//   * Memory Management

#include "core/utils.h"

typedef struct PlatformApi {
    LogFn *log;
} PlatformApi;

#endif

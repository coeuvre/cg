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
    VLog *vlog;
} PlatformApi;

#define CG_LOADED(name) void name(PlatformApi *platform)
typedef CG_LOADED(cgLoaded);

#define CG_UPDATE(name) void name(f32 dt)
typedef CG_UPDATE(cgUpdate);

#endif

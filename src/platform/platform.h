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

#include "core/core.h"

#define CG_ALLOC(name) void *name(usize size)
typedef CG_ALLOC(cgAlloc);

#define CG_FREE(name) void name(void *p, usize size)
typedef CG_FREE(cgFree);

typedef struct PlatformMemoryApi {
    cgAlloc *alloc;
    cgFree *free;
} PlatformMemoryApi;

typedef struct PlatformApi {
    VLog *vlog;
    PlatformMemoryApi memory;
} PlatformApi;

typedef struct PlatformState {
    PlatformApi api;
    void *data;
} PlatformState;

extern PlatformState *PLATFORM;

#define CG_LOADED(name) void name(PlatformState *state)
typedef CG_LOADED(cgLoaded);

#define CG_UPDATE(name) void name(f32 dt)
typedef CG_UPDATE(cgUpdate);

#endif

/// \file
///
/// Platform does:
///   * OpenGL Context Creation
///   * Hot reload game code
///
/// Platform provides:
///   * Logging
///   * File I/O
///   * Memory Management

#ifndef CG_PLATFORM_H
#define CG_PLATFORM_H

#include "core.h"

#define CG_ALLOC(name) void *name(size_t size)
typedef CG_ALLOC(cgAlloc);

#define CG_FREE(name) void name(void *p, size_t size)
typedef CG_FREE(cgFree);

typedef struct cgPlatformMemoryApi {
    cgAlloc *alloc;
    cgFree *free;
} cgPlatformMemoryApi;

typedef struct cgPlatformApi {
    cgVLog *vlog;
    cgPlatformMemoryApi memory;
} cgPlatformApi;

typedef struct cgPlatformState {
    cgPlatformApi api;
    void *data;
} cgPlatformState;

extern cgPlatformState *CG_PLATFORM_STATE;

#define CG_LOADED(name) void name(cgPlatformState *state)
typedef CG_LOADED(cgLoaded);

#define CG_UPDATE(name) void name(float dt)
typedef CG_UPDATE(cgUpdate);

#endif // CG_PLATFORM_H

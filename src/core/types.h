#ifndef CG_CORE_TYPES_H
#define CG_CORE_TYPES_H

#include <stdbool.h>
#include <stdint.h>

#ifdef CG_PLATFORM_WINDOWS
#define CG_EXPORT __declspec(dllexport)
#else
#define CG_EXPORT
#endif

#endif

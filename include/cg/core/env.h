#ifndef CG_CORE_ENV_H
#define CG_CORE_ENV_H

#ifdef _WIN32
    #define CG_PLATFORM_WINDOWS 1
#elif __APPLE__
    #include "TargetConditionals.h"
    #if TARGET_OS_IPHONE
        #define CG_PLATFORM_IOS 1

        #if TARGET_IPHONE_SIMULATOR
            #define CG_PLATFORM_IOS_SIM 1
        #endif
    #else
        #define CG_PLATFORM_MACOS 1
    #endif
#else
    #error Unsupported platform
#endif

#ifdef _MSC_VER
    #define CG_COMPILER_MSVC
#elif __GNUC__
    #define CG_COMPILER_GCC
#elif __clang__
    #define CG_COMPILER_CLANG
#else
    #error Unsupported compiler
#endif

#endif /* CG_CORE_ENV_H */

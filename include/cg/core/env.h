#ifndef CGCORE_ENV_H
#define CGCORE_ENV_H

#ifdef _WIN32
    #define CGPLATFORM_WINDOWS 1
#elif __APPLE__
    #include "TargetConditionals.h"
    #if TARGET_OS_IPHONE
        #define CGPLATFORM_IOS 1

        #if TARGET_IPHONE_SIMULATOR
            #define CGPLATFORM_IOS_SIM 1
        #endif
    #else
        #define CGPLATFORM_MACOS 1
    #endif
#else
    #error Unsupported platform
#endif

#ifdef _MSC_VER
    #define CGCOMPILER_MSVC
#elif __GNUC__
    #define CGCOMPILER_GCC
#elif __clang__
    #define CGCOMPILER_CLANG
#else
    #error Unsupported compiler
#endif

#endif // CGCORE_ENV_H

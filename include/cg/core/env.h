#ifndef CG_CORE_ENV_H
#define CG_CORE_ENV_H

#if defined(_WIN32)
    #define CG_PLATFORM_WINDOWS
#else
    #error Unsupported platform
#endif

#if defined(_MSC_VER)
    #define CG_COMPILER_MSVC
#elif defined(__GNUC__)
    #define CG_COMPILER_GCC
#elif defined(__clang__)
    #define CG_COMPILER_CLANG
#else
    #error Unsupported compiler
#endif

#endif /* CG_ENV_H */

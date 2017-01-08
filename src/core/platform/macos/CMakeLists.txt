add_library(core_platform
    utils.c
    log.c)

target_compile_options(core_platform PRIVATE "-fobjc-arc")

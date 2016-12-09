add_library(core_platform
    log.c
    utils.c)

target_compile_options(core_platform PRIVATE "-fobjc-arc")

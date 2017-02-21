add_library(CGCorePlatform
    utils.c
    log.c)

target_compile_options(CGCorePlatform PRIVATE "-fobjc-arc")

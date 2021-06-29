# LoggingMod
add_library(LoggingMod STATIC
            Logger.cpp)

target_include_directories(LoggingMod
                            PRIVATE ${EIHIRE_INCLUDE_DIRS})

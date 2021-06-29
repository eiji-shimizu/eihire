# ExceptionMod
add_library(ExceptionMod STATIC
            Exception.cpp)

target_include_directories(ExceptionMod
                            PRIVATE ${EIHIRE_INCLUDE_DIRS})

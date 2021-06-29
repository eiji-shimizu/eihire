add_library(UtilMod STATIC
            Dictionary.cpp
            JSON.cpp)

target_include_directories(UtilMod
                            PRIVATE ${EIHIRE_INCLUDE_DIRS})

add_library(UtilMod STATIC
            Dictionary.cpp
            Json.cpp)

target_include_directories(UtilMod
                            PRIVATE ${EIHIRE_INCLUDE_DIRS})

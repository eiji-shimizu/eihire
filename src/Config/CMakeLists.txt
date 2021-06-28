# ConfigMod
add_library(ConfigMod STATIC
            Configuration.cpp
            PropertiesMap.cpp)

target_include_directories(ConfigMod
                            PRIVATE ${EIHIRE_INCLUDE_DIRS})

# ConfigurationMod
add_library(ConfigurationMod STATIC
            Configuration.cpp
            PropertiesMap.cpp)

target_include_directories(ConfigurationMod
                            PRIVATE ${EIHIRE_INCLUDE_CONFIGURATION_DIRS})

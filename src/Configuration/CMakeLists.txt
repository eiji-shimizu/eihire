# ConfigurationMod
add_library(ConfigurationMod STATIC
            PropertiesMap.cpp)

target_include_directories(ConfigurationMod
                            PRIVATE ${EIHIRE_INCLUDE_CONFIGURATION_DIRS})

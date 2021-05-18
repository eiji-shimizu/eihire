# ConfigurationMod
add_library(ConfigurationMod STATIC
            Configuration.cpp
            PropertiesMap.cpp)

target_link_libraries(ConfigurationMod
                        PRIVATE ExceptionMod)

target_include_directories(ConfigurationMod
                            PRIVATE ${EIHIRE_INCLUDE_EXCEPTION_DIRS}
                            PRIVATE ${EIHIRE_INCLUDE_CONFIGURATION_DIRS})

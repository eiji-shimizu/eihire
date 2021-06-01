# ProgramMod
add_library(ProgramMod STATIC
            Program.cpp)

target_include_directories(ProgramMod
                            PRIVATE ${EIHIRE_INCLUDE_DIRS})

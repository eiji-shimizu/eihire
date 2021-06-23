# サブディレクトリを登録
add_subdirectory(Exception)
add_subdirectory(Config)
add_subdirectory(Logging)
add_subdirectory(Program)

# compile options
target_compile_options(ExceptionMod PUBLIC ${COMPILE_OPTIONS})
target_compile_options(ConfigMod PUBLIC ${COMPILE_OPTIONS})
target_compile_options(LoggingMod PUBLIC ${COMPILE_OPTIONS})
target_compile_options(ProgramMod PUBLIC ${COMPILE_OPTIONS})

# compile definitions
target_compile_definitions(ExceptionMod PUBLIC ${COMPILE_DEFINITIONS})
target_compile_definitions(ConfigMod PUBLIC ${COMPILE_DEFINITIONS})
target_compile_definitions(LoggingMod PUBLIC ${COMPILE_DEFINITIONS})
target_compile_definitions(ProgramMod PUBLIC ${COMPILE_DEFINITIONS})

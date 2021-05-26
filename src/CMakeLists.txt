# サブディレクトリを登録
add_subdirectory(Exception)
add_subdirectory(Configuration)

# compile options
target_compile_options(ExceptionMod PUBLIC ${COMPILE_OPTIONS})
target_compile_options(ConfigurationMod PUBLIC ${COMPILE_OPTIONS})
#target_compile_options(DisplayMod PUBLIC ${COMPILE_OPTIONS})
#target_compile_options(OthelloGameMod PUBLIC ${COMPILE_OPTIONS})
#target_compile_options(EihireTest PUBLIC ${COMPILE_OPTIONS})

# compile definitions
target_compile_definitions(ExceptionMod PUBLIC ${COMPILE_DEFINITIONS})
target_compile_definitions(ConfigurationMod PUBLIC ${COMPILE_DEFINITIONS})
#target_compile_definitions(DisplayMod PUBLIC ${COMPILE_DEFINITIONS})
#target_compile_definitions(OthelloGameMod PUBLIC ${COMPILE_DEFINITIONS})
#target_compile_definitions(EihireTest PUBLIC ${COMPILE_DEFINITIONS})

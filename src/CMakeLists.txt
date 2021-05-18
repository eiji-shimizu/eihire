# サブディレクトリを登録
add_subdirectory(Exception)
add_subdirectory(Configuration)

# TempMain
add_executable(EihireTest
                TempMain.cpp)

target_link_libraries(EihireTest
                        PRIVATE ConfigurationMod)

target_include_directories(EihireTest
                            PRIVATE ${EIHIRE_INCLUDE_CONFIGURATION_DIRS}
                            PRIVATE ${EIHIRE_INCLUDE_DIRS})

# compile options
set(COMPILE_OPTIONS /EHa /MD /utf-8)
target_compile_options(ExceptionMod PUBLIC ${COMPILE_OPTIONS})
target_compile_options(ConfigurationMod PUBLIC ${COMPILE_OPTIONS})
#target_compile_options(DisplayMod PUBLIC ${COMPILE_OPTIONS})
#target_compile_options(OthelloGameMod PUBLIC ${COMPILE_OPTIONS})
target_compile_options(EihireTest PUBLIC ${COMPILE_OPTIONS})

# compile definitions
# リリースビルド時は次の1行をコメントアウト,デバッグビルド時はコメントのまま
#set(COMPILE_DEFINITIONS NDEBUG)

target_compile_definitions(ExceptionMod PUBLIC ${COMPILE_DEFINITIONS})
target_compile_definitions(ConfigurationMod PUBLIC ${COMPILE_DEFINITIONS})
#target_compile_definitions(DisplayMod PUBLIC ${COMPILE_DEFINITIONS})
#target_compile_definitions(OthelloGameMod PUBLIC ${COMPILE_DEFINITIONS})
target_compile_definitions(EihireTest PUBLIC ${COMPILE_DEFINITIONS})

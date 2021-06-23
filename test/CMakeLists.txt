# EihireTest

set(EIHIRE_TEST_INCLUDE_DIRS ${PROJECT_SOURCE_DIR}/test/TestUtils)

# Google Testのライブラリを追加
set(GOOGLETEST_INCLUDE_DIRS C:/googletest/include)
set(GOOGLETEST_LIBRARY_DIRS C:/googletest/lib)
if(WIN32)
    # Win環境ではデフォルトでデバッグビルドされたので
    # そのまま全ての***d.libを加える
    set(ADD_LIBRARIES
        PRIVATE ${GOOGLETEST_LIBRARY_DIRS}/gmock_maind.lib
        PRIVATE ${GOOGLETEST_LIBRARY_DIRS}/gmockd.lib
        PRIVATE ${GOOGLETEST_LIBRARY_DIRS}/gtest_maind.lib
        PRIVATE ${GOOGLETEST_LIBRARY_DIRS}/gtestd.lib
    )
elseif(UNIX)
    # TODO
    set(CMAKE_CXX_FLAGS "-pthread")
endif(WIN32)

link_directories(GOOGLETEST_LIBRARY_DIRS)

add_executable(EihireTest Program/ProgramTest.cpp
                            Config/ConfigurationTest.cpp
                            Config/PropertiesMapTest.cpp
                            Exception/ExceptionTest.cpp
                            Logging/LoggerTest.cpp
                            TestUtils/TestUtils.cpp
                            )

target_link_libraries(EihireTest
                        PRIVATE ProgramMod
                        PRIVATE LoggingMod
                        PRIVATE ConfigMod
                        PRIVATE ExceptionMod
                        ${ADD_LIBRARIES}
                        )

target_include_directories(EihireTest
                            PRIVATE ${GOOGLETEST_INCLUDE_DIRS}
                            PRIVATE ${EIHIRE_TEST_INCLUDE_DIRS}
                            PRIVATE ${EIHIRE_INCLUDE_DIRS})

add_test(NAME EihireTest COMMAND EihireTest)

target_compile_options(EihireTest PUBLIC ${COMPILE_OPTIONS})

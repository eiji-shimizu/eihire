cmake_minimum_required(VERSION 3.19.6)
project(eihire CXX)

set(EIHIRE_INCLUDE_DIRS ${PROJECT_SOURCE_DIR}/include)
set(EIHIRE_INCLUDE_CONFIGURATION_DIRS ${PROJECT_SOURCE_DIR}/include/Configuration)
set(EIHIRE_INCLUDE_EXCEPTION_DIRS ${PROJECT_SOURCE_DIR}/include/Exception)
set(EIHIRE_INCLUDE_PLATFORM_DIRS ${PROJECT_SOURCE_DIR}/include/platform)

# Releaseビルド時 cmake -DCMAKE_BUILD_TYPE=Release ..
# テストビルド時 cmake -DCMAKE_BUILD_TYPE=Debug ..
if(${CMAKE_BUILD_TYPE} STREQUAL "Release")
    set(COMPILE_OPTIONS /EHa /MD /utf-8)
    set(COMPILE_DEFINITIONS NDEBUG)
else()
    enable_testing()
    set(COMPILE_OPTIONS /EHa /MTd /utf-8)
    add_subdirectory(test)
endif()

# サブディレクトリを登録
add_subdirectory(src)

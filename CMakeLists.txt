cmake_minimum_required(VERSION 3.19.6)
project(eihire CXX)

set(EIHIRE_INCLUDE_DIRS ${PROJECT_SOURCE_DIR}/include)
set(EIHIRE_INCLUDE_CONFIGURATION_DIRS ${PROJECT_SOURCE_DIR}/include/Configuration)
set(EIHIRE_INCLUDE_EXCEPTION_DIRS ${PROJECT_SOURCE_DIR}/include/Exception)
set(EIHIRE_INCLUDE_PLATFORM_DIRS ${PROJECT_SOURCE_DIR}/include/platform)

# サブディレクトリを登録
add_subdirectory(src)

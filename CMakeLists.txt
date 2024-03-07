cmake_minimum_required(VERSION 3.14)

project(Parallels)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_compile_options(-Wall -Wextra -pedantic -Werror)

if(CMAKE_BUILD_TYPE MATCHES "^Debug")
  add_compile_options(-g)
endif()

# Directories
set(BASE_DIR ${CMAKE_CURRENT_SOURCE_DIR})
set(SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src)
set(ANT_COLONY_DIR ${SOURCE_DIR}/ant_colony)
set(GAUSS_DIR ${SOURCE_DIR}/gauss)
set(WINOGRAD_DIR ${SOURCE_DIR}/winograd)
set(TEST_DIR ${BASE_DIR}/tests)

set(RELATIVE_HEADER_DIR ${SOURCE_DIR})
message(STATUS "RELATIVE_HEADER_DIR: ${RELATIVE_HEADER_DIR}")

# Sources
file(GLOB_RECURSE ALL_SOURCES ${SOURCE_DIR}/*.cc ${SOURCE_DIR}/*.h)
file(GLOB_RECURSE ANT_COLONY_MODEL ${ANT_COLONY_DIR}/model/*.cc)
file(GLOB_RECURSE ANT_COLONY_SOURCE ${ANT_COLONY_DIR}/*.cc)
file(GLOB_RECURSE GAUSS_SOURCE ${GAUSS_DIR}/*.cc)
file(GLOB_RECURSE GAUSS_MODEL ${GAUSS_DIR}/model/*.cc)
file(GLOB_RECURSE WINOGRAD_MODEL ${WINOGRAD_DIR}/model/*.cc)
file(GLOB_RECURSE WINOGRAD_SOURCE ${WINOGRAD_DIR}/*.cc)
file(GLOB_RECURSE TEST_SOURCES ${TEST_DIR}/*.cc)

add_executable(ant ${ANT_COLONY_SOURCE})
add_executable(winograd ${WINOGRAD_SOURCE})
add_executable(gauss ${GAUSS_SOURCE})

target_include_directories(ant PUBLIC ${RELATIVE_HEADER_DIR})
target_include_directories(gauss PUBLIC ${RELATIVE_HEADER_DIR})
target_include_directories(winograd PUBLIC ${RELATIVE_HEADER_DIR})

add_custom_target(format COMMAND clang-format --style=Google -i --verbose ${ALL_SOURCES})
add_custom_target(stylecheck COMMAND clang-format --style=Google -n --verbose ${ALL_SOURCES})
add_custom_target(cppcheck COMMAND cppcheck --language=c++ --enable=all --suppress=missingInclude --inconclusive ${ANT_COLONY_SOURCE} ${GAUSS_SOURCE} ${WINOGRAD_SOURCE})

enable_testing()
add_subdirectory(${TEST_DIR})
cmake_minimum_required(VERSION 3.14)
project(ParallelsTests)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)


include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
)

set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

enable_testing()
add_executable(${PROJECT_NAME} ${TEST_SOURCES} ${ANT_COLONY_MODEL} ${GAUSS_MODEL})
target_link_libraries(${PROJECT_NAME} GTest::gtest_main)
target_include_directories(${PROJECT_NAME} PUBLIC ${RELATIVE_HEADER_DIR})

include(GoogleTest)
gtest_discover_tests(${PROJECT_NAME})

# Report
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} --coverage")
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} --coverage")
set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} --coverage")
set(CMAKE_SHARED_LINKER_FLAGS "${CMAKE_SHARED_LINKER_FLAGS} --coverage")

add_executable(report ${TEST_SOURCES} ${ANT_COLONY_MODEL} ${GAUSS_MODEL})
target_link_libraries(report GTest::gtest_main)
target_include_directories(report PUBLIC ${RELATIVE_HEADER_DIR})


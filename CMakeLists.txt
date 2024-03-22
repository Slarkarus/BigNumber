cmake_minimum_required(VERSION 3.27)
project(untitled2)

set(CMAKE_CXX_STANDARD 20)

add_library(BigNumber STATIC "src/big_number.cpp")
target_include_directories(BigNumber PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/include/")

add_executable(main_tests "test/test.cpp")
target_link_libraries(main_tests BigNumber gtest_main)

add_executable(pi "test/pi.cpp")
target_link_libraries(pi BigNumber)

enable_testing()

include(FetchContent)
FetchContent_Declare(
        googletest
        URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
)
# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

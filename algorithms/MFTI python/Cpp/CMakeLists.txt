cmake_minimum_required(VERSION 3.10)
project(algorithms)
set(CMAKE_CXX_STANDARD 20)

find_package(absl REQUIRED)

add_executable(
    algorithms
    test.cpp
)

include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
)
FetchContent_MakeAvailable(googletest)

target_link_libraries(
    algorithms
    GTest::gtest_main
    absl::strings 
)

include(GoogleTest)
gtest_discover_tests(algorithms)

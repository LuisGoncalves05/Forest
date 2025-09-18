cmake_minimum_required(VERSION 3.14)
project(playground)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR})
set(CMAKE_CXX_FLAGS_DEBUG "-g -O0 -Wall -Wextra -fsanitize=address")

add_executable(playground playground.cpp)

include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
)
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

enable_testing()
include(GoogleTest)

# --- Unbalanced Binary Search Tree tests ---
add_executable(bstTests tests/bstTests.cpp)
target_link_libraries(bstTests GTest::gtest_main)
gtest_discover_tests(bstTests)


# --- AVL Tree tests ---
add_executable(avlTests tests/avlTests.cpp)
target_link_libraries(avlTests GTest::gtest_main)
gtest_discover_tests(avlTests)

# --- Red-Black Tree tests ---
add_executable(rbtTests tests/rbtTests.cpp)
target_link_libraries(rbtTests GTest::gtest_main)
gtest_discover_tests(rbtTests)

# --- Red-Black Tree tests ---
add_executable(splTests tests/splTests.cpp)
target_link_libraries(splTests GTest::gtest_main)
gtest_discover_tests(splTests)

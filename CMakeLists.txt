cmake_minimum_required(VERSION 3.14)

project(ticket)

option(TICKET_BUILD_TESTS "Build tests for Ticket" ON)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

if(TICKET_BUILD_TESTS)
include(FetchContent)

FetchContent_Declare(
  googletest
  GIT_REPOSITORY https://github.com/google/googletest.git
  GIT_TAG        v1.17.0  # Or use a specific commit hash
  DOWNLOAD_EXTRACT_TIMESTAMP TRUE
)

set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

add_executable(RunTests_ticket tests/Ticket_test.cpp)
target_link_libraries(RunTests_ticket GTest::gtest_main)
target_compile_features(RunTests_ticket PUBLIC cxx_std_20)


include(GoogleTest)
gtest_discover_tests(RunTests_ticket)
enable_testing()

endif()
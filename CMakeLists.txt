cmake_minimum_required(VERSION 3.20)

project(CCCBTemplate)

option(OWLAPI_UNIT_TESTS "Build unit tests (default OFF)" OFF)
option(OWLAPI_COVERAGE "Enable coverage reporting (default OFF)" OFF)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include(CMake/conan.cmake)
conan_cmake_run(REQUIRES
    boost/1.76.0
    BASIC_SETUP CMAKE_TARGETS NO_OUTPUT_DIRS
    BUILD missing
    OPTIONS
        boost:without_test=False)
conan_basic_setup(NO_OUTPUT_DIRS KEEP_RPATHS)

add_library(coverage_config INTERFACE)

if(OWLAPI_COVERAGE AND CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang")
    # Add required flags (GCC & LLVM/Clang)
    target_compile_options(coverage_config INTERFACE
        -O0        # no optimization
        -g         # generate debug info
        --coverage # sets all required flags
    )

    target_link_options(coverage_config INTERFACE --coverage)
endif(OWLAPI_COVERAGE AND CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang")

add_subdirectory(src)

if (OWLAPI_UNIT_TESTS)
    enable_testing()
    add_subdirectory(test)
endif()
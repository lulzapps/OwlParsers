cmake_minimum_required(VERSION 3.20)

project(owlapi LANGUAGES CXX)

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

include_directories(${CMAKE_SOURCE_DIR}/myhtml/include)
include_directories(${CMAKE_SOURCE_DIR}/include)
include_directories(${CMAKE_CURRENT_BINARY_DIR})

# https://github.com/lexborisov/myhtml
set(MyHTML_BUILD_STATIC ON)
set(MyHTML_BUILD_SHARED OFF)
set(MyHTML_INSTALL_HEADER OFF)
add_subdirectory(myhtml)
# set_target_properties(myhtml_static PROPERTIES IMPORTED_LOCATION myhtml/lib/myhtml_static.a)

add_subdirectory(src)

if (OWLAPI_UNIT_TESTS)
    enable_testing()
    add_subdirectory(test)
endif()

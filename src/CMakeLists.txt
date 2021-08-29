include_directories(${CMAKE_SOURCE_DIR}/include)
include_directories(${CMAKE_CURRENT_BINARY_DIR})

set(SOURCE_FILES
    MyClass.cpp
)

set (MOC_HEADERS
)

set(HEADER_FILES
    ${CMAKE_SOURCE_DIR}/include/owl/MyClass.h
)

add_library(MyLib STATIC
    ${SOURCE_FILES}
    ${HEADER_FILES}
)

target_link_libraries(MyLib
    coverage_config
)
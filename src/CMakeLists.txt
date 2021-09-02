set(SOURCE_FILES
    HtmlParser.cpp
)

set(HEADER_FILES
    ${CMAKE_SOURCE_DIR}/include/owl/HtmlParser.h
)

add_library(OwlLib STATIC
    ${SOURCE_FILES}
    ${HEADER_FILES}
)

target_link_libraries(OwlLib
    coverage_config
    myhtml_static
)
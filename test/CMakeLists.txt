function(create_test testname FILES)

    add_executable(test_${testname}
        main.cpp
        test_${testname}.cpp
        ${FILES}
    )

    target_link_libraries(test_${testname}
        PUBLIC
            OwlLib
            myhtml_static
            ${CONAN_LIBS_BOOST}
            coverage_config
    )

    add_test(NAME test_${testname}
        COMMAND ${CMAKE_CURRENT_BINARY_DIR}/test_${testname}
    )

endfunction(create_test)

set(SOURCE_FILES
    ${CMAKE_SOURCE_DIR}/include/owl/HtmlParser.h
    ${CMAKE_SOURCE_DIR}/src/HtmlParser.cpp
)

create_test("HtmlParser" "${SOURCE_FILES}")

include_directories(${CMAKE_SOURCE_DIR}/include)

function(create_test testname FILES)

    add_executable(test_${testname}
        main.cpp
        test_${testname}.cpp
        ${FILES}
    )

    target_link_libraries(test_${testname}
        PUBLIC
            ${CONAN_LIBS_BOOST}
            coverage_config
    )

    add_test(NAME test_${testname}
        COMMAND ${CMAKE_CURRENT_BINARY_DIR}/test_${testname}
    )

endfunction(create_test)

set(SOURCE_FILES
    ${CMAKE_SOURCE_DIR}/include/owl/MyClass.h
    ${CMAKE_SOURCE_DIR}/src/MyClass.cpp
)

create_test("MyClass" "${SOURCE_FILES}")

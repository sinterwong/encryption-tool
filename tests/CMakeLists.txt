cmake_minimum_required(VERSION 3.10)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/tests)

set(sources
    main.cc
    test_encrypt.cpp
)

add_executable(encryption_tool_tests ${sources})

target_include_directories(encryption_tool_tests PRIVATE
    ${PROJECT_INCLUDE_DIR}
    ${PROJECT_INCLUDE_DIR}/encrypt
)

target_link_libraries(encryption_tool_tests PRIVATE
    encrypt::encrypt
    cryptopp::cryptopp
    GTest::gtest
    GTest::gtest_main
)

include(GoogleTest)
gtest_discover_tests(encryption_tool_tests)

install(TARGETS encryption_tool_tests DESTINATION tests)

if(EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/data")
    install(DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/data" DESTINATION .)
endif()
